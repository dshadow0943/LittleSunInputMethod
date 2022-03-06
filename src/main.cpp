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
#include "globalapplication.h"
#include "settingmanage.h"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusError>
#include <QApplication>

int main(int argc, char *argv[])
{
    GlobalApplication a(argc, argv);

#ifdef QT_NO_DEBUG
    if (!lSetting->getAppAutoStart() && !(argc == 2 && QString(argv[1]) == "-desktop")) {
        return 0;
    }
#endif

    //建立到session bus的连接
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.interface();
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

#ifdef QT_NO_DEBUG
    if ((argc == 2 && QString(argv[1]) == "-desktop")) {
        w.showView(true);
    }
#endif
    return a.exec();
}
