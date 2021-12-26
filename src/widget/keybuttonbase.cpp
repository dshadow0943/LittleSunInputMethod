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
#include "keybuttonbase.h"
#include "settingmanage.h"
#include <QPainter>

KeyButtonBase::KeyButtonBase(int id, KeyType type, QWidget *parent)
  : QPushButton(parent)
  , ButtonInterface (id, type)
{
    skin_color font = SettingManage::getInstance()->getSkinColor(SkinType::Font);
    skin_color colors;
    switch (type) {
    case KeyButtonBase::Func:
        colors = SettingManage::getInstance()->getSkinColor(SkinType::Func);
        break;
    case KeyButtonBase::Tab:
        colors = SettingManage::getInstance()->getSkinColor(SkinType::Tab);
        break;
    default:
        colors = SettingManage::getInstance()->getSkinColor(SkinType::Key);
    }

    QString button_style= QString("KeyButtonBase{color:%1; background-color:%2;"
                                  "border-radius: 10px;  border: 1px groove gray; border-style: outset;} "
                                  "KeyButtonBase:hover{background-color:%3;} "
                                  "KeyButtonBase:pressed{background-color:%4; border-style: inset; }")
            .arg(font.normal.name())
            .arg(colors.normal.name())
            .arg(colors.hover.name())
            .arg(colors.pressed.name());

    setStyleSheet(button_style);

    QPushButton::connect(this, &QPushButton::clicked, this, &KeyButtonBase::onClicked);
}

void KeyButtonBase::onClicked()
{
    emit sendClicked(this);
}