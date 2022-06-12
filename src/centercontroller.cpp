/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "centercontroller.h"
#include "ui_centercontroller.h"
#include "settingmanage.h"
#include "globalsignaltransfer.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>
#include <QApplication>
#include <QKeyEvent>
#include <QDBusConnectionInterface>
#include <QMessageBox>

CenterController::CenterController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterController)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);

    this->move(SettingManage::getInstance()->getNavigationWindowPos());
    connect(GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::sendWindowClosed,
            this, &CenterController::onWindowClosed);
    connect(GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::sendAppQuit,
            this, &CenterController::onQuit);

    //填充log
    QImage Image;
    Image.load(":/icon/littlesun.png");
    QPixmap pixmap = QPixmap::fromImage(Image);
    int with = ui->title->width();
    int height = ui->title->height();
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // 饱满填充
    ui->title->setPixmap(fitpixmap);

    initTray();
    initDbus();
}
//we
CenterController::~CenterController()
{
    delete SettingManage::getInstance();
    delete ui;

    if (nullptr != mHandkeyboatd) {
        delete mHandkeyboatd;
    }

    if (nullptr != mSettingWindown) {
        delete mSettingWindown;
    }

    if (nullptr != mSoftKeyboard) {
//        delete mSoftKeyboard;
        mSoftKeyboard->hide();
    }
}

void CenterController::initTray()
{
    //***托盘***
    mTray= new QSystemTrayIcon(this);//初始化托盘对象tray
    mTray->setIcon(QIcon(QPixmap(":/icon/littlesun.png")));//设定托盘图标
    mTray->setToolTip("小太阳键盘"); //提示文字
    mTray->show();//让托盘图标显示在系统托盘上

    QAction *keyboard = new QAction("键盘", this);
    QAction *tarin = new QAction("训练", this);
    QAction *site = new QAction("设置", this);
    QAction *quit = new QAction("退出", this);

    connect(keyboard, &QAction::triggered, this, &CenterController::on_btn_key_clicked);
    connect(tarin, &QAction::triggered, this, &CenterController::on_btn_hand_clicked);
    connect(site, &QAction::triggered, this, &CenterController::on_btn_site_clicked);
    connect(quit, &QAction::triggered, this, &CenterController::on_btn_close_clicked);

    mTrayMenu = new QMenu(this);
    mTrayMenu->setMaximumWidth(50);
    mTrayMenu->addAction(keyboard);
    mTrayMenu->addSeparator();
    mTrayMenu->addAction(tarin);
    mTrayMenu->addSeparator();
    mTrayMenu->addAction(site);
    mTrayMenu->addSeparator();
    mTrayMenu->addAction(quit);
    mTray->setContextMenu(mTrayMenu);
    connect(mTray, &QSystemTrayIcon::activated, this, &CenterController::onTrayClicked);
}

void CenterController::initDbus()
{
    //查看插件是否以注册
    QDBusMessage m = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                                "/littlesun",
                                "org.fcitx.Fcitx.LittleSun",
                                "GetStatus");
    //发送消息
    QDBusMessage r = QDBusConnection::sessionBus().call(m);

    if (r.arguments().isEmpty()) {
        return;
    }
    //查看当前输入法
    QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                                "/inputmethod",
                                "org.fcitx.Fcitx.InputMethod",
                                "GetCurrentIM");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    if (response.arguments().first().value<QString>() == "keyboard-littlesun") {
        return;
    }

    //切换输入法
    QDBusMessage setMessage = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                                "/inputmethod",
                                "org.fcitx.Fcitx.InputMethod",
                                "SetCurrentIM");
    setMessage << QString("keyboard-littlesun");
    //发送消息
    QDBusMessage setResponse = QDBusConnection::sessionBus().call(setMessage);

    r = QDBusConnection::sessionBus().call(m);

    if (!r.arguments().isEmpty()) {
        qInfo() << __FUNCTION__ << "没有检测到插件";
        QMessageBox::warning(nullptr, "警告", QString("检测到系统未安装或未正确安装小太阳输入法插件，因此应用使用将会受限"), QMessageBox::Yes);
    }
}

void CenterController::showSoftKeyboard()
{
    if (nullptr == mSoftKeyboard) {
        mSoftKeyboard = new SoftKeyboard(SettingManage::WindowKeyboard);
        connect(mSoftKeyboard, &SoftKeyboard::sendCandidateCharacter, this, &CenterController::onCandidateCharacter);
        connect(mSoftKeyboard, &SoftKeyboard::sendDeleteCharacter, this, &CenterController::onDeleteCharacter);
        connect(mSoftKeyboard, &SoftKeyboard::sendSiteClicked, this, &CenterController::on_btn_site_clicked);
    }
    this->show();
    mFlag |= (1 << 0);
    mSoftKeyboard->show();
}

void CenterController::on_btn_key_clicked()
{
    showSoftKeyboard();
}

void CenterController::on_btn_hand_clicked()
{
    if (mHandkeyboatd == nullptr){
        mHandkeyboatd = new HandKeyboardTrain(SettingManage::WindowTrain);
    }
    mFlag |= (1 << 2);
    mHandkeyboatd->show();
}

void CenterController::on_btn_site_clicked()
{
    if (!mSettingWindown) {
        mSettingWindown = new SettingWindown(SettingManage::WindowConfig);
    }
    mFlag |= (1 << 1);
    mSettingWindown->show();
}

void CenterController::on_btn_close_clicked()
{
    qApp->quit();
}

/**
 * @brief CenterController::candidateCharacterSlots
 * @param character
 * 向插件发送字符
 */
void CenterController::onCandidateCharacter(QString character)
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                            "/littlesun",
                            "org.fcitx.Fcitx.LittleSun",
                            "CommitString");
    //发送消息
    message << QString(character);
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    emit sendCandidateCharacter((character));
}

/**
 * @brief CenterController::deleteCharacterSlots
 * 发送退格信号
 */
void CenterController::onDeleteCharacter()
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                            "/littlesun",
                            "org.fcitx.Fcitx.LittleSun",
                            "DeleteChar");
     //发送消息
     QDBusMessage response = QDBusConnection::sessionBus().call(message);
}

int CenterController::initView()
{
    return 0;
}

int CenterController::showView(bool force)
{
    if (force || SettingManage::getInstance()->getSmartKeyboard()) {
        showSoftKeyboard();
    }
    return 0;
}

int CenterController::hideView()
{
    onQuit();
    return 0;
}

/**
 * @brief SoftKeyboard::mousePressEvent
 * @param event
 * 捕捉鼠标按下事件
 * 重写鼠标按下键，获取鼠标左键按下时的全局位置，将窗口的可移动标志设置为true
 */
void CenterController::mousePressEvent(QMouseEvent *event) {
    cursorGlobalPos = event->globalPos();  //获取鼠标按下时的全局位置
    if (event->button() == Qt::LeftButton)//左键按下
    {
        isMousePress = true;
    }
    return QWidget::mousePressEvent(event);
}

/**
 * @brief SoftKeyboard::mouseMoveEventglobalPos()
 * @param event
 * 重写鼠标移动事件，使窗口跟着鼠标移动
 */
void CenterController::mouseMoveEvent(QMouseEvent *event) {

    if (event->buttons() & Qt::LeftButton && isMousePress) {
        window()->move(window()->pos() +  event->globalPos() - cursorGlobalPos);
        cursorGlobalPos = event->globalPos();
        SettingManage::getInstance()->setNavigationWindowPos(cursorGlobalPos);
    }
    return QWidget::mousePressEvent(event);
}

/**
 * @brief SoftKeyboard::mouseReleaseEvent
 * @param event
 * 重写鼠标抬起（释放）事件，将窗口的可移动标志设置为false
 */
void CenterController::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)//左键释放
    {
        isMousePress = false;
    }
    return QWidget::mousePressEvent(event);
}

void CenterController::onWindowClosed(int id)
{
    switch (id) {
    case SettingManage::WindowKeyboard:
        this->hide();
        mFlag &= (((1 << 3) - 1) ^ (1 << 0));
        break;
    case SettingManage::WindowConfig:
        SettingManage::getInstance()->setConfigWindowPos(mSettingWindown->pos());
        mFlag &= (((1 << 3) - 1) ^ (1 << 1));
        break;
    case SettingManage::WindowTrain:
        SettingManage::getInstance()->setTrainWindowPos(mHandkeyboatd->pos());
        mFlag &= (((1 << 3) - 1) ^ (1 << 2));
        break;
    }
}

void CenterController::onQuit()
{
    if (mFlag&1 && SettingManage::getInstance()->getSmartKeyboard()) {
        mSoftKeyboard->close();
    }

    if (SettingManage::getInstance()->getNavigationResident()) {
        return;
    }

    if (0 == mFlag) {
        qApp->quit();
    }
}

void CenterController::onTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
        {
        case QSystemTrayIcon::Trigger://单击托盘图标
            on_btn_key_clicked();
            break;
        case QSystemTrayIcon::DoubleClick://双击托盘图标
            break;
        default:
            break;
        }
}
