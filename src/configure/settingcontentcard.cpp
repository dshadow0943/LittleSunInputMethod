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
#include "settingcontentcard.h"

#include <QLabel>
#include <QFont>

SettingContentCard::SettingContentCard(QString& title, QWidget *parent) : QWidget(parent)
{
    this->mTitle = title;

    initUi();
}

void SettingContentCard::initUi()
{
    mRow = new QVBoxLayout();
    QLabel *title = new QLabel(mTitle);
    QFont font("Microsoft YaHei", 14, 70);

    title->setFont(font);
    mRow->addWidget(title);
    this->setLayout(mRow);
}

void SettingContentCard::appendWidget(QWidget* widget)
{
    mRow->addWidget(widget);
    this->setLayout(mRow);
}

void SettingContentCard::setTopPos(int pos)
{
    this->mTopPos = pos;
}

int SettingContentCard::getTopPos()
{
    return this->mTopPos;
}
