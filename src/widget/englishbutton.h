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
#ifndef ENGLISHBUTTON_H
#define ENGLISHBUTTON_H

#include "keybuttonbase.h"

class EnglishButton : public KeyButtonBase
{
    Q_OBJECT
public:
    explicit EnglishButton(QString str1, QString str2, int id = 0, KeyType type = Invalid, QWidget *parent = nullptr);

    //设置显示字母
    void setLetter(bool isCaps);

signals:

public slots:

    void onShiftClicked(bool isCaps);

private:

    QString str1, str2;  //需要显示的字符

};

#endif // ENGLISHBUTTON_H
