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
#include "settingmanage.h"

SettingManage::SettingManage(QObject *parent) : QObject(parent)
{
    initSkin();
}

SettingManage* SettingManage::getInstance()
{
    static SettingManage setting;
    return &setting;
}

void SettingManage::initSkin()
{
    skin_color theme = {QColor("#EAF7FF"), QColor("#EAF7FF"), QColor("#C0DEF6")};
    skin_color key = {QColor("#EAF7FF"), QColor("#EAF7FF"), QColor("#EAF7FF")};
    skin_color func = {QColor("#C0DEF6"), QColor("#C0DEF6"), QColor("#C0DEF6")};
    skin_color tab = {QColor("#C0DEF6"), QColor("#C0DEF6"), QColor("#EAF7FF")};
    skin_color font = {QColor("#000000"), QColor("#000000"), QColor("#000000")};

    mSkins.push_back({theme, key, func, tab, font});
}

skin_color SettingManage::getSkinColor(SkinType type)
{
    switch (type) {
    case Theme:
        return mSkins[mConfig.themeType].theme;
    case Key:
        return mSkins[mConfig.themeType].key;
    case Func:
        return mSkins[mConfig.themeType].func;
    case Tab:
        return mSkins[mConfig.themeType].tab;
    case Font:
        return mSkins[mConfig.themeType].font;
    }
}
