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
#ifndef CE_SWITCHBUTTON_H
#define CE_SWITCHBUTTON_H

#include "keybuttonbase.h"

/**
 * @brief The CE_SwitchButton class
 * 拼音键盘中英文切换按键
 */
class CE_SwitchButton : public KeyButtonBase
{
    Q_OBJECT
public:
    explicit CE_SwitchButton(QString str1 = "En", QString str2 = "中", int id = KeySwitch, KeyType type = Func, QWidget *parent = nullptr);

    void switchText(bool isEnglish);
    bool isEnglish();

signals:
    void sendSwitchClicked(bool isEnflish);

private:
    void onClicked() override;

private:
    QString str1, str2;  //需要显示的字符

    bool mIsEnglish = true;
};

#endif // CE_SWITCHBUTTON_H
