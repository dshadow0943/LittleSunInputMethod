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
