/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "keyboardsidebar.h"
#include "buttonitem.h"
#include "settingmanage.h"
#include <QVBoxLayout>
#include <QButtonGroup>

KeyboardSidebar::KeyboardSidebar(QStringList tabs, QWidget *parent) : QWidget(parent)
{
    this->mTabs = tabs;
    initUi();
}

void KeyboardSidebar::initUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    mButList.clear();

    QButtonGroup *group = new QButtonGroup(this);
    connect(group, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));

    for (int i = 0; i < mTabs.size(); ++i) {
        QPushButton *but = new QPushButton(mTabs[i]);
        mButList.push_back(but);
        but->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        group->addButton(but, i);
        layout->addWidget(but, 1);
    }
    this->setLayout(layout);
}

void KeyboardSidebar::onButtonClicked(int id)
{
    setCurrentIndex(id);
}

void KeyboardSidebar::setFontSize(int size)
{
    for (QPushButton *but : mButList) {
        QFont font = but->font();
        font.setPixelSize(size);
        but->setFont(font);
    }
}

void KeyboardSidebar::setCurrentIndex(int index)
{
    skin_color colors = SettingManage::getInstance()->getSkinColor(SkinType::Tab);
    QString button_style= QString("QPushButton{ \
                                      border-style:none;\
                                      border:1px solid %4;\
                                      color:%1;\
                                      padding:0px;\
                                      min-height:15px;\
                                      border-radius:5px;\
                                      background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %2,stop:0.4 %3,stop:0.6 %3,stop:1 %2);\
                                      }\
                                      QPushButton:hover{\
                                      background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %2,stop:0.4 %3,stop:0.6 %3,stop:1 %2);\
                                      }\
                                      QPushButton:pressed{\
                                      background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %2,stop:0.5 %3,stop:1 %2);\
                                      }\
                                      ")
            .arg(colors.font.name())
            .arg(colors.normal.name())
            .arg(colors.hover.name())
            .arg(colors.hover.name());

    for (QPushButton *but : mButList)
    {
        but->setStyleSheet(button_style);
    }

    if (index < mButList.size()){
        QString button_style = QString("QPushButton{ \
                                          border-style:none;\
                                          border:1px solid %4;\
                                          color:%1;\
                                          padding:0px;\
                                          min-height:15px;\
                                          border-radius:5px;\
                                          background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %2,stop:0.5 %3,stop:1 %2);\
                                          }\
                                          QPushButton:hover{\
                                          background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %2,stop:0.5 %3,stop:1 %2);\
                                          }\
                                          QPushButton:pressed{\
                                          background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %2,stop:0.5 %3,stop:1 %2);\
                                          }\
                                          ")
        .arg(colors.font.name())
        .arg(colors.normal.name())
        .arg(colors.pressed.name())
        .arg(colors.hover.name());

        mButList[index]->setStyleSheet(button_style);
   }

   if (index != mCurrentIndex) {
       emit sendCurrentIndex(index);
   }

   mCurrentIndex = index;
}

void KeyboardSidebar::setCurrentIndex()
{
    setCurrentIndex(mCurrentIndex);
}
