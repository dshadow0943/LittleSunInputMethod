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
#ifndef SETTINGWINDOWN_H
#define SETTINGWINDOWN_H

#include "settingcontenttab.h"
#include "settingcontentview.h"

#include <QWidget>

class RadioButtonBase;
class SettingWindown : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWindown(QWidget *parent = nullptr);

signals:

public slots:
    void onRadioButtonClicked(RadioButtonBase* but);

private:
    void initUi();
    void addBasicCard();
    void addSkinCard();

private:
    SettingContentView *mContentView {nullptr};
    SettingContentTab *mContentTab {nullptr};
};

#endif // SETTINGWINDOWN_H