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
#include "settingcontenttab.h"

#include <QDebug>

SettingContentTab::SettingContentTab(QWidget *parent) : QWidget(parent)
{
    init();

    connect(mSettingTabs, &QListView::clicked, this, &SettingContentTab::onTabClicked);
}

void SettingContentTab::init()
{
    mSettingTabs = new QListView(this);
    mItemModel = new QStandardItemModel(this);
    mSettingTabs->setModel(mItemModel);
    mSettingTabs->setFixedSize(100,300);
    mSettingTabs->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    QPalette palette(mSettingTabs->palette());
    palette.setColor(QPalette::Base, "#C0DCF2");
    mSettingTabs->setPalette(palette);
    mSettingTabs->setAutoFillBackground(false);

    setStyleSheet("QListView::item{"
                  "height:40px;"
                  "background-color: #C0DCF2;"
                  "border-radius: 0px;"
                  "border: 0px;"
                  "}"
                  "QListView::item:selected{"
                  "color: #000000;"
                  "background-color: #EAF7FF;"
                  "}");
}

void SettingContentTab::appendTab(QString& tab)
{
    QStandardItem *item = new QStandardItem(tab);
    item->setTextAlignment(Qt::AlignCenter);
    mItemModel->appendRow(item);
    if (mItemModel->columnCount() == 1) {
        onViewChange(0);
    }
}

void SettingContentTab::onTabClicked(QModelIndex index)
{
    emit sendClicked(index.row());
}

void SettingContentTab::onViewChange(int index)
{
    QModelIndex qIndex = mItemModel->index(index,0);
    mSettingTabs->setCurrentIndex(qIndex);
}
