/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef SETTINGCONTENTCARD_H
#define SETTINGCONTENTCARD_H

#include <QWidget>
#include <QVBoxLayout>

class SettingContentCard : public QWidget
{
    Q_OBJECT
public:
    explicit SettingContentCard(QString& title, QWidget *parent = nullptr);

    void appendWidget(QWidget* widget);
    void appendLayout(QLayout* layout);
    void setTopPos(int pos);
    int getTopPos();

signals:

public slots:

private:
    void initUi();

private:
    QString mTitle;
    int mTopPos {0};    //控件与上一层布局顶部的偏移量

    QVBoxLayout *mRow {nullptr};
};

#endif // SETTINGCONTENTCARD_H
