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
#include "keyboardsidebar.h"

#include <QVBoxLayout>

KeyboardSidebar::KeyboardSidebar(QWidget *parent) : QWidget(parent)
{
    initUi();
    initConnection();
}

void KeyboardSidebar::initUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    mNumKey = new QPushButton("数字");
    mEnKey = new QPushButton("拼音");
    mHandKey = new QPushButton("手写");
    mPuncKey = new QPushButton("符号");

    layout->addWidget(mNumKey);
    layout->addWidget(mEnKey);
    layout->addWidget(mHandKey);
    layout->addWidget(mPuncKey);
    this->setLayout(layout);
}

void KeyboardSidebar::initConnection()
{
    mButList.push_back(mNumKey);
    mButList.push_back(mEnKey);
    mButList.push_back(mHandKey);
    mButList.push_back(mPuncKey);

    connect(mNumKey, &QPushButton::clicked, this, [=](){
        setCurrentIndex(0);
    });
    connect(mEnKey, &QPushButton::clicked, this, [=](){
        setCurrentIndex(1);
    });
    connect(mHandKey, &QPushButton::clicked, this, [=](){
        setCurrentIndex(2);
    });
    connect(mPuncKey, &QPushButton::clicked, this, [=](){
        setCurrentIndex(3);
    });
}

void KeyboardSidebar::setCurrentIndex(int index)
{
    mCurrentIndex = index;
    emit sendCurrentIndex(index);

    for (int i = 0; i < 4; i++) {
        mButList[i]->setStyleSheet("background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #EAF7FF,stop:1 #EAF7FF);");
    }
    if (index < 4){
        mButList[index]->setStyleSheet("background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #C0DEF6,stop:1 #C0DEF6);");
    }
}
