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
#ifndef GLOBALSIGNALTRANSFER_H
#define GLOBALSIGNALTRANSFER_H

#include "buttonbase.h"
#include "radiobuttonbase.h"

#include <QObject>

class GlobalSignalTransfer : public QObject
{
    Q_OBJECT

public:
    static GlobalSignalTransfer* instance();

protected:
    explicit GlobalSignalTransfer(QObject *parent = nullptr);

signals:
    void sendKeyButtonClicked(ButtonBase* but);
    void sendRadioButtonClicked(RadioButtonBase* but);

public slots:
    void onKeyButtonClicked(ButtonBase* but);
    void onRadioButtonClicked(RadioButtonBase* but);
};

#endif // GLOBALSIGNALTRANSFER_H
