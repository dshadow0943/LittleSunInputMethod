#include "centercontroller.h"
#include "ui_centercontroller.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>
#include <QApplication>
#include <QKeyEvent>

CenterController::CenterController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterController)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::WindowDoesNotAcceptFocus);
    softKeyboard = new SoftKeyboard();
//    handkeyboatd = new HandKeyboardTrain();
    connect(softKeyboard, &SoftKeyboard::sendCandidateCharacter, this, &CenterController::candidateCharacterSlots);
    connect(softKeyboard, &SoftKeyboard::sendDeleteCharacter, this, &CenterController::deleteCharacterSlots);
    //填充log
    QImage Image;
    Image.load(":/icon/littlesun.png");
    QPixmap pixmap = QPixmap::fromImage(Image);
    int with = ui->title->width();
    int height = ui->title->height();
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // 饱满填充
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 按比例缩放
    ui->title->setPixmap(fitpixmap);

//    setStyleSheet("background:#EAF7FF;");
}

CenterController::~CenterController()
{
    delete ui;
}

void CenterController::on_btn_key_clicked()
{
    softKeyboard->show();
}

void CenterController::on_btn_hand_clicked()
{
    if (handkeyboatd == nullptr){
        handkeyboatd = new HandKeyboardTrain();
    }
    handkeyboatd->show();
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
void CenterController::candidateCharacterSlots(QString character)
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
void CenterController::deleteCharacterSlots()
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

int CenterController::showView()
{

    this->show();
    softKeyboard->show();
    return 0;
}

int CenterController::hideView()
{
    this->hide();
    softKeyboard->hide();
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
    event->ignore();
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
    }
    event->ignore();
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
    event->ignore();
}

void CenterController::on_btn_site_clicked()
{

}
