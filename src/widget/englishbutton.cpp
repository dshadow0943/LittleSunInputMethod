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
#include "englishbutton.h"

EnglishButton::EnglishButton(QString str1, QString str2, int id, KeyType type, QWidget *parent) : KeyButtonBase(id, type, parent)
  , str1(str1)
  , str2(str2)
{
    setLetter(false);
}

/**
 * @brief EnglishButton::setLetter
 * 设置显示字母
 * @param isCaps true: 显示大写字母， false: 显示小写字母
 */
void EnglishButton::setLetter(bool isCaps)
{
    if (isCaps) {
        setText(str1);
    } else {
        setText(str2);
    }
}

void EnglishButton::onShiftClicked(bool isCaps)
{
    setLetter(isCaps);
}
