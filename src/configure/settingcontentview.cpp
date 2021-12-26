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
#include "settingcontentview.h"
#include <QPushButton>
#include <QScrollBar>
#include <QDebug>

SettingContentView::SettingContentView(QWidget *parent) : QWidget(parent)
{
    initUi();

    connect(mScrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &SettingContentView::onScrollValueChange);
}

void SettingContentView::initUi()
{
    mScrollArea = new QScrollArea(this);
    QWidget* pWgt = new QWidget;
    mRow = new QVBoxLayout(pWgt);
    pWgt->setLayout(mRow);
    mScrollArea->setWidget(pWgt);
    mScrollArea->setFixedSize(QSize(500, 300));
}

void SettingContentView::appendCard(SettingContentCard* cardWgt)
{
    cardWgt->setTopPos(mScrollArea->widget()->height());
    mCardList.push_back(cardWgt);
    mRow->addWidget(cardWgt);
    QWidget* pWgt = new QWidget;
    pWgt->setLayout(mRow);
    mScrollArea->setWidget(pWgt);
}

void SettingContentView::onScrollValueChange(int value)
{
    static int pValue = -1;
    for (int i = 0; i < mCardList.size(); ++i) {
        if ((mCardList[i]->getTopPos() > pValue && mCardList[i]->getTopPos() <= value)
                || (mCardList[i]->getTopPos() < pValue && mCardList[i]->getTopPos() >= value)) {
            sendViewChange(i);
        }
    }
}

void SettingContentView::onItemChange(int index)
{
    mScrollArea->verticalScrollBar()->setValue(mCardList.at(index)->getTopPos());
}
