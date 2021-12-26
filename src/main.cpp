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

    qApp->setPalette(QPalette(QColor("#EAF7FF")));
    qApp->setStyleSheet(".QPushButton,.QToolButton{ \
                            border-style:none;\
                            border:1px solid #C0DCF2;\
                            color:#386487;\
                            padding:5px;\
                            min-height:15px;\
                            border-radius:5px;\
                            background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #DEF0FE,stop:1 #C0DEF6);\
                            }\
                            .QPushButton:hover,.QToolButton:hover{\
                            background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F2F9FF,stop:1 #DAEFFF);\
                            }\
                            .QPushButton:pressed,.QToolButton:pressed{\
                            background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #DEF0FE,stop:1 #C0DEF6);\
                            }\
                            .QListView{\
                            Background-cp;pr:#EAF7FF;//背景色\
                            Alternate-background-color:#DEF0FE;//行与行之间交替的颜色setAlternatingRowColors(true);\
                            Show-decoration-selected:1;设置是否选中时，整行都高亮显示\
                            }\
                            .QListView::item:alternate{\
                            Background:#000000;\
                            }\
                            .QListView::item:selected{\
                            Border:2px solid #000000;\
                            }\
                            ");
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
