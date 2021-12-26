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
#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include "englishbutton.h"
#include "numbutton.h"
#include "shiftbutton.h"
#include "ce_switchbutton.h"

#include <QObject>
#include <QList>


class ButtonItem : public QObject
{
    Q_OBJECT
public:
    explicit ButtonItem(QObject *parent = nullptr);

    static EnglishButton* getEnglishButton(QString str1, QString str2, int id = 0, KeyButtonBase::KeyType type = KeyButtonBase::Invalid, QWidget *parent = nullptr);
    static NumButton* getNumButton(QString num, int id = 0, KeyButtonBase::KeyType type = KeyButtonBase::Invalid, QWidget *parent = nullptr);
    static ShiftButton* getShiftButton();
    static CE_SwitchButton* getSwitchButton();

signals:

public slots:

private:
    QList<KeyButtonBase*> mButList;

};

#endif // BUTTONITEM_H
