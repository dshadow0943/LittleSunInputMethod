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
#ifndef SHIFTBUTTON_H
#define SHIFTBUTTON_H

#include <buttonbase.h>

class ShiftButton : public ButtonBase
{
    Q_OBJECT
public:
    explicit ShiftButton(QString text = "shift", int id = Qt::Key_Shift, ButtonBase::KeyType type = ButtonBase::Func, QWidget *parent = nullptr);

signals:
    void sendShiftClicked(bool mIsCaps);

public slots:
    void onClicked();
    void onEnglishInput(bool isEnglish);

private:
    bool mIsCaps = true;
    bool mIsCapsLook = false;
};

#endif // SHIFTBUTTON_H
