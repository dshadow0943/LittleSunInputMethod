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
#include "shiftbutton.h"

ShiftButton::ShiftButton(QString text, int id, ButtonBase::KeyType type, QWidget *parent) : ButtonBase (id, type, parent)
{
    setText(text);
    connect(this, &QPushButton::clicked, this, &ShiftButton::onClicked);
}

void ShiftButton::onClicked()
{
    if (mIsCapsLook) {
        return;
    }
    mIsCaps = !mIsCaps;
    emit sendShiftClicked(mIsCaps);
}

void ShiftButton::onEnglishInput(bool isEnglish)
{
    if (isEnglish  == mIsCaps) {
        onClicked();
    }
    mIsCapsLook = !isEnglish;
}