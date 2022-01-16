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
#include <QApplication>
#include <QPalette>

SettingManage* SettingManage::obj = nullptr;
SettingManage::SettingManage(QObject *parent) : QObject(parent)
{
    initConfig();
    initSkin();
    setThemePalette();
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
    QString path = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + APPLOCALPATH + "/config.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.beginGroup("Basic");

    mConfig.themeType = settings.value("themeType", SettingManage::SkinSkyBlue).toInt();
    mConfig.defaultKeyboard = settings.value("defaultKeyboard", SettingManage::DefaultKeyboardPinyin).toInt();
    mConfig.navigationWindowPos = settings.value("navigationWindowPos", QPoint(0, 0)).toPoint();
    mConfig.configWindowPos = settings.value("configWindowPos", QPoint(0, 0)).toPoint();
    mConfig.trainWindowPos = settings.value("trainWindowPos", QPoint(0, 0)).toPoint();
    mConfig.keyTabDisplay = settings.value("keyTabDisplay", true).toBool();
    mConfig.keyboardSizeScale = settings.value("keyboardSizeScale", -1).toDouble();

    settings.endGroup();

}

void SettingManage::saveConfig()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + APPLOCALPATH + "/config.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.beginGroup("Basic");

    settings.setValue("themeType", mConfig.themeType);
    settings.setValue("defaultKeyboard", mConfig.defaultKeyboard);
    settings.setValue("navigationWindowPos", mConfig.navigationWindowPos);
    settings.setValue("configWindowPos", mConfig.configWindowPos);
    settings.setValue("trainWindowPos", mConfig.trainWindowPos);
    settings.setValue("keyTabDisplay", mConfig.keyTabDisplay);
    settings.setValue("keyboardSizeScale", mConfig.keyboardSizeScale);

    settings.endGroup();
}

void SettingManage::initSkin()
{
    mSkinMap.insert(SkinLightWhite, getLightWhite());
    mSkinMap.insert(SKinKindGrey, getKindGrey());
    mSkinMap.insert(SkinSkyBlue, getSkyBlueSkin());
    mSkinMap.insert(SkinMagicBlack, getMagicBlack());
}


skin SettingManage::getLightWhite()
{
    skin_color theme = {QColor("#FFFFFF"), QColor("#FFFFFF"), QColor("#F5F5F5"), QColor("#000000")};
    skin_color key = {QColor("#FFFFFF"), QColor("#FFFFFF"), QColor("#FFFFFF"), QColor("#000000")};
    skin_color func = {QColor("#FFFFFF"), QColor("#FFFFFF"), QColor("#FFFFFF"), QColor("#000000")};
    skin_color tab = {QColor("#FFFFFF"), QColor("#F0F0F0"), QColor("#FFFFFF"), QColor("#000000")};
    return {theme, key, func, tab};
}

skin SettingManage::getKindGrey()
{
    skin_color theme = {QColor("#F6F6F6"), QColor("#F6F6F6"), QColor("#E4E4E4"), QColor("#57595B")};
    skin_color key = {QColor("#F6F6F6"), QColor("#F6F6F6"), QColor("#F6F6F6"), QColor("#57595B")};
    skin_color func = {QColor("#E4E4E4"), QColor("#E4E4E4"), QColor("#E4E4E4"), QColor("#57595B")};
    skin_color tab = {QColor("#F6F6F6"), QColor("#E4E4E4"), QColor("#F6F6F6"), QColor("#57595B")};
    return {theme, key, func, tab};
}

skin SettingManage::getSkyBlueSkin()
{
    skin_color theme = {QColor("#EAF7FF"), QColor("#DEF0FE"), QColor("#C0DEF6"), QColor("#386487")};
    skin_color key = {QColor("#DEF0FE"), QColor("#DEF0FE"), QColor("#DEF0FE"), QColor("#386487")};
    skin_color func = {QColor("#C0DEF6"), QColor("#C0DEF6"), QColor("#C0DEF6"), QColor("#386487")};
    skin_color tab = {QColor("#DEF0FE"), QColor("#C0DEF6"), QColor("#DEF0FE"), QColor("#386487")};
    return {theme, key, func, tab};
}

skin SettingManage::getMagicBlack()
{
    skin_color theme = {QColor("#363636"), QColor("#363636"), QColor("#242424"), QColor("#DCDCDC")};
    skin_color key = {QColor("#363636"), QColor("#363636"), QColor("#363636"), QColor("#DCDCDC")};
    skin_color func = {QColor("#242424"), QColor("#242424"), QColor("#242424"), QColor("#DCDCDC")};
    skin_color tab = {QColor("#363636"), QColor("#202020"), QColor("#363636"), QColor("#DCDCDC")};
    return {theme, key, func, tab};
}

void SettingManage::setThemePalette()
{
    skin_color tClolr = getSkinColor(Theme);
    skin_color bClolr = getSkinColor(Tab);
    qApp->setPalette(QPalette(tClolr.normal.name()));

    qApp->setStyleSheet(QString(".QPushButton,.QToolButton{ \
                                border-style:none;\
                                border:1px solid %1;\
                                color:%2;\
                                padding:5px;\
                                min-height:15px;\
                                border-radius:5px;\
                                background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %3,stop:1 %4);\
                                }\
                                .QPushButton:hover,.QToolButton:hover{\
                                background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %4,stop:1 %5);\
                                }\
                                .QPushButton:pressed,.QToolButton:pressed{\
                                background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %3,stop:1 %4);\
                                }\
                                ")
                        .arg(tClolr.hover.name())
                        .arg(tClolr.font.name())
                        .arg(bClolr.normal.name())
                        .arg(bClolr.hover.name())
                        .arg(bClolr.pressed.name()));
}

skin_color SettingManage::getSkinColor(SkinType type)
{
    int key = mConfig.themeType;

    if (mSkinMap.end() == mSkinMap.find(key)) {
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
    }
    return mSkinMap[key].theme;
}

void SettingManage::setNavigationWindowPos(QPoint point)
{
    mConfig.navigationWindowPos = point;
}

QPoint SettingManage::getNavigationWindowPos()
{
    return mConfig.navigationWindowPos;
}

void SettingManage::setConfigWindowPos(QPoint point)
{
    mConfig.configWindowPos = point;
}

QPoint SettingManage::getConfigWindowPos()
{
    return mConfig.configWindowPos;
}

void SettingManage::setTrainWindowPos(QPoint point)
{
    mConfig.trainWindowPos = point;
}

QPoint SettingManage::getTrainWindowPos()
{
    return mConfig.trainWindowPos;
}

void SettingManage::setThemeType(int type)
{
    mConfig.themeType = type;
    setThemePalette();
    emit sendThemeChange();
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

void SettingManage::setKeyTabDisplay(bool isDisplay)
{
    mConfig.keyTabDisplay = isDisplay;
    emit sendKetTabCheBoxClicked();
}

bool SettingManage::getKeyTabDisplay()
{
    return mConfig.keyTabDisplay;
}

void SettingManage::setKeyboardSizeScale(double scale)
{
    mConfig.keyboardSizeScale = scale;
    emit sendKeyboardScaleChange();
}

double  SettingManage::getKeyboardSizeScale()
{
    return mConfig.keyboardSizeScale;
}
