/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "globalapplication.h"
#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>

GlobalApplication::GlobalApplication(int& argc,char **argv):
    QApplication(argc,argv)
{

}
bool GlobalApplication::notify(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MetaCall) {
        m.start();
    }

    return QApplication::notify(obj,e);
}
