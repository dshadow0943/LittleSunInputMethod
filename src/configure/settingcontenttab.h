/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef SETTINGCONTENTTAB_H
#define SETTINGCONTENTTAB_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>

class SettingContentTab : public QWidget
{
    Q_OBJECT
public:
    explicit SettingContentTab(QWidget *parent = nullptr);
    void appendTab(QString& tab);

signals:
    void sendClicked(int index);

public slots:
    void onTabClicked(QModelIndex index);
    void onViewChange(int index);
    void onThemeChange();

private:
    void init();

private:
    QListView *mSettingTabs;
    QStandardItemModel *mItemModel;
};

#endif // SETTINGCONTENTTAB_H
