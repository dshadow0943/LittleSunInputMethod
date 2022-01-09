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
#include "buttonitem.h"

ButtonItem::ButtonItem(QObject *parent) : QObject(parent)
{

}

EnglishButton* ButtonItem::getEnglishButton(QString str1, QString str2, int id, KeyButtonBase::KeyType type, QWidget *parent)
{
    EnglishButton *but = new EnglishButton(str1, str2, id, type, parent);
    but->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    if (KeyButtonBase::PinyinLetter == type) {
        connect(getShiftButton(), &ShiftButton::sendShiftClicked, but, &EnglishButton::onShiftClicked);
    }

    if (KeyButtonBase::PinyinPunc == type) {
        connect(getSwitchButton(), &CE_SwitchButton::sendSwitchClicked, but, &EnglishButton::onShiftClicked);
    }

    return but;
}

NumButton* ButtonItem::getNumButton(QString num, int id, KeyButtonBase::KeyType type, QWidget *parent)
{
    NumButton *but = new NumButton(num, id, type, parent);
    but->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    return but;
}

ShiftButton* ButtonItem::getShiftButton()
{
    static ShiftButton but;
    but.setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    connect(getSwitchButton(), &CE_SwitchButton::sendSwitchClicked, &but, &ShiftButton::onEnglishInput);
    return &but;
}

CE_SwitchButton* ButtonItem::getSwitchButton()
{
    static CE_SwitchButton but;
    but.setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    return &but;
}
