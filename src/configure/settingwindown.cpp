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
#include "settingwindown.h"
#include "radiobuttonbase.h"
#include "globalsignaltransfer.h"
#include "settingmanage.h"
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QButtonGroup>

SettingWindown::SettingWindown(QWidget *parent) : QWidget(parent)
{
    initUi();

    connect(mContentTab, &SettingContentTab::sendClicked,
            mContentView, &SettingContentView::onItemChange);
    connect(mContentView, &SettingContentView::sendViewChange,
            mContentTab, &SettingContentTab::onViewChange);

    connect(GlobalSignalTransfer::instance(), &GlobalSignalTransfer::sendRadioButtonClicked,
            this, &SettingWindown::onRadioButtonClicked);
}

void SettingWindown::initUi()
{
    setFixedSize(QSize(600, 300));
    mContentView = new SettingContentView(this);
    mContentTab = new SettingContentTab(this);

    mContentView->resize(500, 300);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(mContentTab, 1);
    layout->addWidget(mContentView, 5);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);

    addBasicCard();
}

void SettingWindown::addBasicCard()
{
    QString title = "基础设置";
    SettingContentCard *card = new SettingContentCard(title);
    int bId;

    QLabel *defaultKeyboard = new QLabel("默认键盘");
    card->appendWidget(defaultKeyboard);

    QWidget *keyWgt = new QWidget();
    QHBoxLayout *keyLayout = new QHBoxLayout();
    RadioButtonBase *numKeyBoard = new RadioButtonBase("数字键盘", SettingManage::DefaultKeyboardNum, SettingManage::DefaultKeyboard);
    RadioButtonBase *pinyinKeyBoard = new RadioButtonBase("拼音键盘", SettingManage::DefaultKeyboardPinyin, SettingManage::DefaultKeyboard);
    RadioButtonBase *handKeyBoard = new RadioButtonBase("手写键盘", SettingManage::DefaultKeyboardHand, SettingManage::DefaultKeyboard);
    keyLayout->addWidget(numKeyBoard);
    keyLayout->addWidget(pinyinKeyBoard);
    keyLayout->addWidget(handKeyBoard);

    QButtonGroup *keyGroup = new QButtonGroup();
    keyGroup->addButton(numKeyBoard, numKeyBoard->getId());
    keyGroup->addButton(pinyinKeyBoard, pinyinKeyBoard->getId());
    keyGroup->addButton(handKeyBoard, handKeyBoard->getId());

    bId = SettingManage::getInstance()->getDefaultKeyboard() + SettingManage::DefaultKeyboardBegin;
    if (bId < SettingManage::DefaultKeyboardBegin || bId >= SettingManage::DefaultKeyboardEnd) {
        bId = SettingManage::DefaultKeyboardPinyin;
    }
    keyGroup->button(bId)->setChecked(true);
    keyWgt->setLayout(keyLayout);
    card->appendWidget(keyWgt);

    QLabel *skinLabel = new QLabel("皮肤设置");
    card->appendWidget(skinLabel);

    QWidget *skinWgt = new QWidget();
    QHBoxLayout *skinLayout = new QHBoxLayout();
    RadioButtonBase *lightWhite = new RadioButtonBase("浅白色", SettingManage::SkinLightWhite, SettingManage::Skin);
    RadioButtonBase *skyBlue = new RadioButtonBase("天空蓝", SettingManage::SkinSkyBlue, SettingManage::Skin);
    RadioButtonBase *darkBlack = new RadioButtonBase("深黑色", SettingManage::SkinDarkBlack, SettingManage::Skin);
    skinLayout->addWidget(lightWhite);
    skinLayout->addWidget(skyBlue);
    skinLayout->addWidget(darkBlack);

    QButtonGroup *skinGroup = new QButtonGroup();
    skinGroup->addButton(lightWhite, lightWhite->getId());
    skinGroup->addButton(skyBlue, skyBlue->getId());
    skinGroup->addButton(darkBlack, darkBlack->getId());

    bId = SettingManage::getInstance()->getThemeType();
    if (bId < SettingManage::SkinBegin || bId >= SettingManage::SkinEnd) {
        bId = SettingManage::SkinSkyBlue;
    }
    skinGroup->button(bId)->setChecked(true);
    skinWgt->setLayout(skinLayout);
    card->appendWidget(skinWgt);

    mContentTab->appendTab(title);
    mContentView->appendCard(card);
}

void SettingWindown::addSkinCard()
{
}

void SettingWindown::onRadioButtonClicked(RadioButtonBase* but)
{
    qInfo() << __FUNCTION__ << but->getId();

    switch (but->getType()) {
    case SettingManage::DefaultKeyboard:
        SettingManage::getInstance()->setDefaultKeyboard(but->getId()-SettingManage::DefaultKeyboardBegin);
        break;
    case SettingManage::Skin:
        SettingManage::getInstance()->setThemeType(but->getId());
        break;
    }
}
