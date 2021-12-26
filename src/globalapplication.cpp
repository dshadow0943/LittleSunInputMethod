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
