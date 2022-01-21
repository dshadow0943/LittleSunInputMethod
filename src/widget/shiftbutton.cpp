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
#include <QPainter>

ShiftButton::ShiftButton(QString text, int id, KeyButtonBase::KeyType type, QWidget *parent) : KeyButtonBase (id, type, parent)
{
    setText(text);
}

void ShiftButton::onClicked()
{
    KeyButtonBase::onClicked();
    if (mIsCapsLook) {
        return;
    }
    mIsCaps = !mIsCaps;
    emit sendShiftClicked(mIsCaps);
    update();
}

void ShiftButton::onEnglishInput(bool isEnglish)
{
    if (isEnglish  == mIsCaps) {
        onClicked();
    }
    mIsCapsLook = !isEnglish;
}

void ShiftButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    if(mText.isEmpty()) {
        return;
    }
    QTextOption o;
    o.setWrapMode(QTextOption::WrapAnywhere);
    o.setAlignment(Qt::AlignCenter);

    QPainter painter(this);
    QFont font = painter.font();

    int size = width() < height()? width() : height();
    size /= 3;
    if (mIsCaps) {
        size += 4;
        QPen pen = painter.pen();
        pen.setColor(Qt::red);
        painter.setPen(pen);
    }
    font.setPixelSize(size);
    painter.setFont(font);
    painter.drawText(this->rect(), mText, o);
}
