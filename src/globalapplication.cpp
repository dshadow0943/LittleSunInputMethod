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
    m.start();
    return QApplication::notify(obj,e);
}
