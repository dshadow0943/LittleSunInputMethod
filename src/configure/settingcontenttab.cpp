/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "settingcontenttab.h"
#include "settingmanage.h"

#include <QDebug>

SettingContentTab::SettingContentTab(QWidget *parent) : QWidget(parent)
{
    init();
    onThemeChange();
    connect(mSettingTabs, &QListView::clicked, this, &SettingContentTab::onTabClicked);
    connect(SettingManage::getInstance(), &SettingManage::sendThemeChange, this, &SettingContentTab::onThemeChange);
}

void SettingContentTab::init()
{
    mSettingTabs = new QListView(this);
    mItemModel = new QStandardItemModel(this);
    mSettingTabs->setModel(mItemModel);
    mSettingTabs->setFixedSize(100,300);
    mSettingTabs->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    mSettingTabs->setAutoFillBackground(false);
}

void SettingContentTab::appendTab(QString& tab)
{
    QStandardItem *item = new QStandardItem(tab);
    item->setTextAlignment(Qt::AlignCenter);
    mItemModel->appendRow(item);
    if (mItemModel->columnCount() == 1) {
        onViewChange(0);
    }
}

void SettingContentTab::onTabClicked(QModelIndex index)
{
    emit sendClicked(index.row());
}

void SettingContentTab::onViewChange(int index)
{
    QModelIndex qIndex = mItemModel->index(index,0);
    mSettingTabs->setCurrentIndex(qIndex);
}

void SettingContentTab::onThemeChange()
{
    skin_color s = SettingManage::getInstance()->getSkinColor(SkinType::Theme);

    setStyleSheet(QString("QListView{background-color: %1;}"
                          "QListView::item{"
                          "height:40px;"
                          "background-color: %1;"
                          "border-radius: 0px;"
                          "border: 0px;"
                          "}"
                          "QListView::item:selected{"
                          "color: %2;"
                          "background-color: %3;"
                          "}")
                  .arg(s.pressed.name())
                  .arg(s.font.name())
                  .arg(s.normal.name()));
}
