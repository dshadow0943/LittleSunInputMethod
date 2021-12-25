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
#ifndef SETTINGCONTENTCARD_H
#define SETTINGCONTENTCARD_H

#include <QWidget>
#include <QVBoxLayout>

class SettingContentCard : public QWidget
{
    Q_OBJECT
public:
    explicit SettingContentCard(QString& title, QWidget *parent = nullptr);

    void appendWidget(QWidget* widget);
    void setTopPos(int pos);
    int getTopPos();

signals:

public slots:

private:
    void initUi();

private:
    QString mTitle;
    int mTopPos {0};    //控件与上一层布局顶部的偏移量

    QVBoxLayout *mRow {nullptr};
};

#endif // SETTINGCONTENTCARD_H
