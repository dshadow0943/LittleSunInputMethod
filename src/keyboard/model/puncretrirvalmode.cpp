/*
* Copyright (C) 2019 ~ 2019 UnionTech Software Technology Co.,Ltd.
*
* Author:     leilong <leilong@uniontech.com>
*
* Maintainer: leilong <leilong@uniontech.com>
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
#include "puncretrirvalmode.h"
#include <QDebug>

PuncRetrirvalMode::PuncRetrirvalMode() : QObject()
{
}

QStringList PuncRetrirvalMode::getPunc(DBOperation::PuncType type)
{
    QStringList datas;
    datas = XYDB->findPunc(type).split(" ");
    return datas;
}

void PuncRetrirvalMode::updatePunc(QString data, DBOperation::PuncType type)
{
    QStringList datas;
    XYDB->updatePunc(data, datas, type);
//    qInfo() << datas;
}
