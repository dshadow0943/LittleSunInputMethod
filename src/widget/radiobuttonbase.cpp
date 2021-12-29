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
#include "radiobuttonbase.h"
#include "globalsignaltransfer.h"

RadioButtonBase::RadioButtonBase(QString text, int id, int type, QWidget *parent) : QRadioButton(text, parent)
  , ButtonInterface (id, type)
{
    connect(this, &QRadioButton::clicked, this, &RadioButtonBase::onClicked);
    connect(this, &RadioButtonBase::sendClicked,
            GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::onRadioButtonClicked);

    setFixedSize(QSize(100, 20));
}

void RadioButtonBase::onClicked()
{
    emit sendClicked(this);
}
