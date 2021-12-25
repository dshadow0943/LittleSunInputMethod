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
#ifndef RADIOBUTTONBASE_H
#define RADIOBUTTONBASE_H

#include <QWidget>
#include <QRadioButton>

class RadioButtonBase : public QRadioButton
{
    Q_OBJECT
public:

    enum RadioType {
        DefaultKeyboard = 1,
        Skin,
    };

    enum RadioId {
        Invalid = 0,
        DefaultKeyboardBegin,
        DefaultKeyboardNum = DefaultKeyboardBegin,
        DefaultKeyboardPinyin,
        DefaultKeyboardHand,
        DefaultKeyboardEnd,
        SkinBegin,
        SkinLightWhite = SkinBegin,
        SkinSkyBlue,
        SkinDarkBlack,
        SkinEnd,
    };

    explicit RadioButtonBase(QString text = "", int id = 0, int type = 0, QWidget *parent = nullptr);

    int getId();
    int getType();

signals:
    void sendClicked(RadioButtonBase* but);

public slots:
    void onClicked();

protected:
    const int mId;
    const int mType;
};

#endif // RADIOBUTTONBASE_H
