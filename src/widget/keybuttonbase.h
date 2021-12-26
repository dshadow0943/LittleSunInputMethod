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
#ifndef BUTTONBASE_H
#define BUTTONBASE_H

#include "buttoninterface.h"

#include <QObject>
#include <QPushButton>
#include <QPaintEvent>

class KeyButtonBase : public QPushButton, public ButtonInterface
{
    Q_OBJECT
public:

    enum KeyType {
        Invalid = 0,
        PinyinLetter,  //拼音键盘字母按键
        PinyinNum,     //拼音键盘数字按键
        PinyinPunc,    //拼音键盘符号
        Num,           //数字键盘数字按键
        Func,          //功能按键
        Punc,          //符号按键
        Tab,
    };

    enum KeyId {
        KeyNum,  //数字
        keyPinyin,  //拼音
        keyHand, //手写
        keyPunc, //符号
        KeySwitch, //中英文切换键
        KeyChinese,
        KeyEnglish,
        KeyMath,
        KeyBack,
    };

    explicit KeyButtonBase(int id = 0, KeyType type = Invalid, QWidget *parent = nullptr);

signals:
    void sendClicked(KeyButtonBase* but);

protected slots:
    void onClicked();

protected:

};

#endif // BUTTONBASE_H