#include "centercontroller.h"
#include "ui_centercontroller.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>
#include <QApplication>
#include <QKeyEvent>

// must keep X11 haeder under QT header
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

CenterController::CenterController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterController)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::WindowDoesNotAcceptFocus);
    qDebug() << "启动: " << qApp->applicationDirPath();
    softKeyboard = new SoftKeyboard();
    handkeyboatd = new HandKeyboardTrain();
    connect(softKeyboard, &SoftKeyboard::sendCandidateCharacter, this, &CenterController::candidateCharacterSlots);
    connect(softKeyboard, &SoftKeyboard::sendDeleteCharacter, this, &CenterController::deleteCharacterSlots);
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
    handkeyboatd->show();
}

void CenterController::on_btn_close_clicked()
{
    qApp->quit();
}

void CenterController::on_pushButton_clicked()
{
    this->window()->showMinimized();
}

/**
 * @brief CenterController::candidateCharacterSlots
 * @param character
 * 想客戶端發送字符信號
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
 * 模擬backspace鍵發送到系統
 */
void CenterController::deleteCharacterSlots()
{

    Display* disp = XOpenDisplay(nullptr);

    if(disp == nullptr) {
        return;
    }

    KeyCode key = XKeysymToKeycode(disp, XK_BackSpace);

    XTestFakeKeyEvent(disp, key, true, CurrentTime);
    XTestFakeKeyEvent(disp, key, false, CurrentTime);

    XFlush(disp);

    XCloseDisplay(disp);

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
