/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "mousethread.h"
#include "globalsignaltransfer.h"
#include "settingmanage.h"
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>
#include <QApplication>

MouseThread::MouseThread()
{
}

/**
 * @brief MouseThread::run
 * 监测当前输入法是否是可用状态，不可用将状态终止进程
 */
void MouseThread::run()
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                                "/inputmethod",
                                "org.fcitx.Fcitx.InputMethod",
                                "GetCurrentState");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    if (!response.arguments().first().value<bool>()) {
        QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                                    "/inputmethod",
                                    "org.fcitx.Fcitx.InputMethod",
                                    "GetCurrentIM");
        //发送消息
        QDBusMessage response = QDBusConnection::sessionBus().call(message);
        if (response.arguments().first().value<QString>() == "keyboard-littlesun") {
            GlobalSignalTransfer::getInstance()->onAppQuit();
        }
    }
}
