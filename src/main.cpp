#include "centercontroller.h"
#include "keyboardAdaptor.h"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusError>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //加载样式表
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
//        qApp->setPalette(QPalette(QColor(paletteColor)));
//        qApp->setStyleSheet(qss);
        file.close();
    }

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
