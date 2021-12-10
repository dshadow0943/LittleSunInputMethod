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
#include "buttonbase.h"
#include <QPainter>

ButtonBase::ButtonBase(int id, KeyType type, QWidget *parent) : QPushButton(parent)
  , mId(id)
  , mType(type)
{

    QString button_style= "QPushButton{background-color:#EAF7FF; color: black;"
                          "border-radius: 10px;  border: 1px groove gray; border-style: outset;} "
                          "QPushButton:hover{background-color:#EAF7FF; color: black;} "
                          "QPushButton:pressed{background-color:#EAF7FF; border-style: inset; }";

    setStyleSheet(button_style);

    connect(this, &QPushButton::clicked, this, &ButtonBase::onClicked);
}

int ButtonBase::getId()
{
    return this->mId;
}

ButtonBase::KeyType ButtonBase::getType()
{
    return this->mType;
}

void ButtonBase::onClicked()
{
    emit sendClicked(this);
}

/**
 * @brief ButtonBase::paintEvent
 * 按钮同意绘制成圆角
 * @param event
 */
void ButtonBase::paintEvent(QPaintEvent *event)
{
//    int radius = 10;
//    QPainter painter(this);                                                     // 圆角大小
//    painter.setRenderHint(QPainter::Antialiasing);                              // 抗锯齿
//    painter.setPen(Qt::NoPen);
//    painter.drawRoundedRect(0, 0, this->width(), this->height(), radius, radius);

    QPushButton::paintEvent(event);
}
