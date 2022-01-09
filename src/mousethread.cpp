/*
* Copyright (C) 2019 ~ 2019 UnionTech Software Technology Co.,Ltd.
*
* Author:     leilong <dshadow@foxmail.com>
*
* Maintainer: leilong <dshadow@foxmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "mousethread.h"
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
    static int count  = 0;
    qInfo() << __FUNCTION__ << count++;
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
//            qApp->quit();
        }
    }

//    while (!isInterruptionRequested()) {

//    }
}
