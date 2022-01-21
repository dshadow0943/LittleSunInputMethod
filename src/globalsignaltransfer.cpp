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
#include "globalsignaltransfer.h"

GlobalSignalTransfer::GlobalSignalTransfer(QObject *parent) : QObject(parent)
{

}

GlobalSignalTransfer* GlobalSignalTransfer::getInstance()
{
    static GlobalSignalTransfer obj;
    return &obj;
}

void GlobalSignalTransfer::onKeyButtonClicked(KeyButtonBase* but)
{
    emit sendKeyButtonClicked(but);
}

void GlobalSignalTransfer::onRadioButtonClicked(RadioButtonBase* but)
{
    emit sendRadioButtonClicked(but);
}

void GlobalSignalTransfer::onWindowClosed(int id)
{
    emit sendWindowClosed(id);
}

void GlobalSignalTransfer::onScrollBarclicked(QString text, int index)
{
    emit sendScrollBarClosed(text, index);
}

void GlobalSignalTransfer::onCheckBoxClicked(CheckBoxBase *but)
{
    emit sendCheckBoxClicked(but);
}

void GlobalSignalTransfer::onSliderValueChange(SliderBase *but)
{
    emit sendSliderValueChange(but);
}

void GlobalSignalTransfer::onAppQuit()
{
    emit sendAppQuit();
}
