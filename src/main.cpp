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
#include "centercontroller.h"
#include "keyboardAdaptor.h"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusError>
#include <QApplication>
#include "globalapplication.h"

int main(int argc, char *argv[])
{
    GlobalApplication a(argc, argv);

    //建立到session bus的连接
    QDBusConnection connection = QDBusConnection::sessionBus();
    //在session bus上注册名为com.fcitx.littlesun.server的服务
    if(!connection.registerService("com.fcitx.littlesun.server"))
    {
        qDebug() << "error:" << connection.lastError().message();
        exit(-1);
    }
    CenterController w;
    //注册名为/keyboard的对象，把类Object所有槽函数和信号导出
    connection.registerObject("/keyboard", &w);
    ServerAdaptor server(&w);
    w.show();
    return a.exec();
}
