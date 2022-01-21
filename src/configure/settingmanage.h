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
#ifndef SETTINGMANAGE_H
#define SETTINGMANAGE_H

#include <QObject>
#include <QSettings>
#include <QPoint>
#include <QSize>
#include <QColor>
#include <QList>

struct skin_color {
    QColor normal;
    QColor hover;
    QColor pressed;
    QColor font;
};

struct skin {
    skin_color theme;
    skin_color key;
    skin_color func;
    skin_color tab;
};

struct config {
    QPoint keyboardWindowPos;   //键盘界面位置
    QPoint navigationWindowPos; //导航栏界面位置
    QPoint configWindowPos;     //设置界面位置
    QPoint trainWindowPos;      //训练界面位置

    QSize keyBoardWindowSize;   //键盘大小

    bool keyTabDisplay = true;
    bool navigationResident = false;
    bool smartKeyboard = false;
    int defaultKeyboard = 0;  //初始键盘类型
    int themeType = 0;     //主题类型
    double keyboardSizeScale = -1;
};

enum SkinType {
    Theme = 0,
    Key,
    Func,
    Tab,
};

class SettingManage : public QObject
{
    Q_OBJECT
public:
    explicit SettingManage(QObject *parent = nullptr);
    ~SettingManage();

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
        SKinKindGrey,
        SkinSkyBlue,
        SkinMagicBlack,
        SkinDarkBlack,
        SkinEnd,
        CheckKeyTab,
        CheckSmartKeyboard,
        CheckNavigationResident,
        KeySizeSlider,

        WindowKeyboard,
        WindowConfig,
        WindowTrain,
    };

    static SettingManage* getInstance();
    skin_color getSkinColor(SkinType type);

    void setNavigationWindowPos(QPoint);
    QPoint getNavigationWindowPos();
    void setConfigWindowPos(QPoint);
    QPoint getConfigWindowPos();
    void setTrainWindowPos(QPoint);
    QPoint getTrainWindowPos();

    void setThemeType(int type);
    int getThemeType();
    void setDefaultKeyboard(int type);
    int getDefaultKeyboard();
    void setKeyTabDisplay(bool);
    bool getKeyTabDisplay();
    void setNavigationResident(bool);
    bool getNavigationResident();
    void setSmartKeyboard(bool);
    bool getSmartKeyboard();
    void setKeyboardSizeScale(double scale);
    double  getKeyboardSizeScale();

    void setThemePalette();
    void saveConfig();

signals:
    void sendThemeChange();
    void sendKetTabCheBoxClicked();
    void sendKeyboardScaleChange();

public slots:

private:
    void initSkin();
    void initConfig();

    skin getLightWhite();
    skin getKindGrey();
    skin getSkyBlueSkin();
    skin getMagicBlack();

private:
    static SettingManage* obj;

    QMap<int, skin> mSkinMap;
    config mConfig;
};

#endif // SETTINGMANAGE_H
