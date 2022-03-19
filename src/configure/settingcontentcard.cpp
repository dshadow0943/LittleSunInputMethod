/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "settingcontentcard.h"

#include <QLabel>
#include <QFont>

SettingContentCard::SettingContentCard(QString& title, QWidget *parent) : QWidget(parent)
{
    this->mTitle = title;

    initUi();
}

void SettingContentCard::initUi()
{
    mRow = new QVBoxLayout();
    QLabel *title = new QLabel(mTitle);
    QFont font("Microsoft YaHei", 14, 70);

    title->setFont(font);
    mRow->addWidget(title);
    this->setLayout(mRow);
}

void SettingContentCard::appendWidget(QWidget* widget)
{
    mRow->addWidget(widget);
    this->setLayout(mRow);
}

void SettingContentCard::appendLayout(QLayout* layout)
{
    QWidget *w = new QWidget();
    w->setLayout(layout);
    mRow->addWidget(w);
    this->setLayout(mRow);
}

void SettingContentCard::setTopPos(int pos)
{
    this->mTopPos = pos;
}

int SettingContentCard::getTopPos()
{
    return this->mTopPos;
}
