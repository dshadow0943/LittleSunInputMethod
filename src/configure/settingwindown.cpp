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
#include "checkboxbase.h"
#include "globalsignaltransfer.h"
#include "settingmanage.h"
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QButtonGroup>

SettingWindown::SettingWindown(int id, QWidget *parent) : WindowBase (id, parent)
{
    initUi();

    QPoint point = SettingManage::getInstance()->getConfigWindowPos();
    move(point.x(), point.y());

    connect(mContentTab, &SettingContentTab::sendClicked,
            mContentView, &SettingContentView::onItemChange);
    connect(mContentView, &SettingContentView::sendViewChange,
            mContentTab, &SettingContentTab::onViewChange);

    connect(GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::sendRadioButtonClicked,
            this, &SettingWindown::onRadioButtonClicked);
    connect(GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::sendCheckBoxClicked,
            this, &SettingWindown::onCheBoxClicked);
}

SettingWindown::~SettingWindown()
{
    SettingManage::getInstance()->setConfigWindowPos(pos());
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
    addKeyboardCard();

    addHelpCard();
}

void SettingWindown::addBasicCard()
{
    QString title = "基础设置";
    SettingContentCard *card = new SettingContentCard(title);
    int bId;
    QAbstractButton* but = nullptr;

    /*********************系统主题*************************/

    QLabel *skinLabel = new QLabel("系统主题");
    card->appendWidget(skinLabel);

    QWidget *skinWgt = new QWidget();
    QHBoxLayout *skinLayout = new QHBoxLayout();
    RadioButtonBase *lightWhite = new RadioButtonBase("纯净白", SettingManage::SkinLightWhite, SettingManage::Skin);
    RadioButtonBase *kindGrey = new RadioButtonBase("和蔼灰", SettingManage::SKinKindGrey, SettingManage::Skin);
    RadioButtonBase *skyBlue = new RadioButtonBase("天空蓝", SettingManage::SkinSkyBlue, SettingManage::Skin);
    RadioButtonBase *darkBlack = new RadioButtonBase("魔幻黑", SettingManage::SkinMagicBlack, SettingManage::Skin);
    skinLayout->addWidget(lightWhite);
    skinLayout->addWidget(kindGrey);
    skinLayout->addWidget(skyBlue);
    skinLayout->addWidget(darkBlack);

    QButtonGroup *skinGroup = new QButtonGroup();
    skinGroup->addButton(lightWhite, lightWhite->getId());
    skinGroup->addButton(kindGrey, kindGrey->getId());
    skinGroup->addButton(skyBlue, skyBlue->getId());
    skinGroup->addButton(darkBlack, darkBlack->getId());

    bId = SettingManage::getInstance()->getThemeType();
    but = skinGroup->button(bId);
    if (nullptr == but) {
        but = skyBlue;
    }
    but->setChecked(true);
    skinWgt->setLayout(skinLayout);
    card->appendWidget(skinWgt);

    /*********************默认键盘*************************/

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
    but = keyGroup->button(bId);
    if (nullptr == but) {
        but = pinyinKeyBoard;
    }
    but->setChecked(true);
    keyWgt->setLayout(keyLayout);
    card->appendWidget(keyWgt);


    /*********************end*************************/

    mContentTab->appendTab(title);
    mContentView->appendCard(card);
}

void SettingWindown::addKeyboardCard()
{
    QString title = "键盘调节";
    SettingContentCard *card = new SettingContentCard(title);

    /*********************键盘侧边栏*************************/
    CheckBoxBase* keyBut = new CheckBoxBase("显示键盘侧边栏", SettingManage::KeyTab);
    keyBut->setChecked(SettingManage::getInstance()->getKeyTabDisplay());
    card->appendWidget(keyBut);

    mContentTab->appendTab(title);
    mContentView->appendCard(card);
}

void SettingWindown::addHelpCard()
{
    QString title = "帮助";
    SettingContentCard *card = new SettingContentCard(title);

    QLabel *lable = new QLabel("感谢使用小太阳输入法\nThanks for using the littlesun input method\n\n"
                               "如在使用过程中遇到问题或者建议请发送邮件至\nIf you encounter problems or suggestions during use,\nplease send an email to"
                               "\n\ndshadow@foxmail.com");
    lable->setAlignment(Qt::AlignCenter);
    lable->setFixedSize(500, 240);
    card->appendWidget(lable);

    mContentTab->appendTab(title);
    mContentView->appendCard(card);
}

void SettingWindown::addSkinCard()
{
}

void SettingWindown::onRadioButtonClicked(RadioButtonBase* but)
{
    switch (but->getType()) {
    case SettingManage::DefaultKeyboard:
        SettingManage::getInstance()->setDefaultKeyboard(but->getId()-SettingManage::DefaultKeyboardBegin);
        break;
    case SettingManage::Skin:
        SettingManage::getInstance()->setThemeType(but->getId());
        break;
    }
}

void SettingWindown::onCheBoxClicked(CheckBoxBase* but)
{
    switch (but->getId()) {
    case SettingManage::KeyTab:
        SettingManage::getInstance()->setKeyTabDisplay(but->isChecked());
        break;
    }
}
