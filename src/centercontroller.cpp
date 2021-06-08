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
    softKeyboard = new SoftKeyboard();
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

}

void CenterController::on_btn_close_clicked()
{
    qApp->quit();
}

void CenterController::on_pushButton_clicked()
{
    this->hide();
}

/**
 * @brief CenterController::candidateCharacterSlots
 * @param character
 * 想客戶端發送字符信號
 */
void CenterController::candidateCharacterSlots(QString character)
{
    qDebug() << "controller: add";
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

    qDebug() << "controller: delete";
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

void CenterController::on_btn_dbus_clicked()
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                            "/libpinyin",
                            "org.fcitx.Fcitx.LibPinyin",
                            "ClearDict");
    message << int(1);
     //发送消息
     QDBusMessage response = QDBusConnection::sessionBus().call(message);
}
