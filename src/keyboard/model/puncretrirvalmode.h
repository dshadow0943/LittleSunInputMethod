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
#ifndef PUNCRETRIRVALMODE_H
#define PUNCRETRIRVALMODE_H

#include "dboperation.h"
#include <QObject>

class PuncKeyboard;
class PuncRetrirvalMode : public QObject
{
    Q_OBJECT
public:
    PuncRetrirvalMode();

    QStringList getPunc(DBOperation::PuncType);
    void updatePunc(QString data, DBOperation::PuncType type);

signals:

public slots:


};

#endif // PUNCRETRIRVALMODE_H
