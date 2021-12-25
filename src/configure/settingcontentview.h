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
#ifndef SETTINGCONTENTVIEW_H
#define SETTINGCONTENTVIEW_H

#include "settingcontentcard.h"

#include <QWidget>
#include <QScrollArea>

class SettingContentView : public QWidget
{
    Q_OBJECT
public:
    explicit SettingContentView(QWidget *parent = nullptr);

    void appendCard(SettingContentCard* card);

signals:
    void sendViewChange(int index);

public slots:
    void onScrollValueChange(int value);
    void onItemChange(int index);

private:
    void initUi();

private:

    QScrollArea * mScrollArea {nullptr};
    QVBoxLayout *mRow {nullptr};

    QList<SettingContentCard*> mCardList;
};

#endif // SETTINGCONTENTVIEW_H
