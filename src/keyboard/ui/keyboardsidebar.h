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
#ifndef KEYBOARDSIDEBAR_H
#define KEYBOARDSIDEBAR_H

#include <QWidget>
#include <QPushButton>

class KeyboardSidebar : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardSidebar(QWidget *parent = nullptr);

    void setCurrentIndex(int index);

signals:
    void sendCurrentIndex(int index);

public slots:

private:
    void initUi();
    void initConnection();

private:
    QList<QPushButton*> mButList;
    QPushButton *mNumKey;   //数据键盘Tab
    QPushButton *mEnKey;    //拼音键盘Tab
    QPushButton *mHandKey;  //手写键盘Tab
    QPushButton *mPuncKey;  //符号键盘Tab

    int mCurrentIndex = 0;

};

#endif // KEYBOARDSIDEBAR_H
