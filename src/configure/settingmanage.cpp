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
#include "globalconfig.h"

#include <QStandardPaths>
#include <QDebug>

SettingManage* SettingManage::obj = nullptr;
SettingManage::SettingManage(QObject *parent) : QObject(parent)
{
    initConfig();
    initSkin();
}

SettingManage::~SettingManage()
{
    saveConfig();
}

SettingManage* SettingManage::getInstance()
{
    if (nullptr == obj) {
        obj = new SettingManage();
    }

    return obj;
}

void SettingManage::initConfig()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + APPLOCALPATH + "/config.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.beginGroup("基础设置");

    mConfig.themeType = settings.value("themeType", 1).toInt();
    mConfig.defaultKeyboard = settings.value("defaultKeyboard", 1).toInt();
    mConfig.navigationWindowPos = settings.value("navigationWindowPos", QPoint(0, 0)).toPoint();

    settings.endGroup();

}

void SettingManage::saveConfig()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + APPLOCALPATH + "/config.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.beginGroup("基础设置");

    settings.setValue("themeType", mConfig.themeType);
    settings.setValue("defaultKeyboard", mConfig.defaultKeyboard);
    settings.setValue("navigationWindowPos", mConfig.navigationWindowPos);

    settings.endGroup();
}

void SettingManage::initSkin()
{
    skin_color theme = {QColor("#EAF7FF"), QColor("#EAF7FF"), QColor("#C0DEF6"), QColor("#000000")};
    skin_color key = {QColor("#EAF7FF"), QColor("#EAF7FF"), QColor("#EAF7FF"), QColor("#000000")};
    skin_color func = {QColor("#C0DEF6"), QColor("#C0DEF6"), QColor("#C0DEF6"), QColor("#000000")};
    skin_color tab = {QColor("#C0DEF6"), QColor("#C0DEF6"), QColor("#EAF7FF"), QColor("#000000")};
    skin_color font = {QColor("#000000"), QColor("#000000"), QColor("#000000"), QColor("#000000")};

    mSkinMap.insert(SkinLightWhite , {theme, key, func, tab, font});
    mSkinMap.insert(SkinSkyBlue , {theme, key, func, tab, font});
    mSkinMap.insert(SkinDarkBlack , {theme, key, func, tab, font});
}

skin_color SettingManage::getSkinColor(SkinType type)
{
    int key = mConfig.themeType;
    if (key < SettingManage::SkinBegin || key >= SettingManage::SkinEnd) {
        key = SettingManage::SkinSkyBlue;
    }

    switch (type) {
    case Theme:
        return mSkinMap[key].theme;
    case Key:
        return mSkinMap[key].key;
    case Func:
        return mSkinMap[key].func;
    case Tab:
        return mSkinMap[key].tab;
    case Font:
        return mSkinMap[key].font;
    }
}

void SettingManage::setThemeType(int type)
{
    mConfig.themeType = type;
}

int SettingManage::getThemeType()
{
    return mConfig.themeType;
}

void SettingManage::setDefaultKeyboard(int type)
{
    mConfig.defaultKeyboard = type;
}

int SettingManage::getDefaultKeyboard()
{
    return mConfig.defaultKeyboard;
}
