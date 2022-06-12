/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef SETTINGCONTENTVIEW_H
#define SETTINGCONTENTVIEW_H

#include "settingcontentcard.h"

#include <QWidget>
#include <QScrollArea>

class SettingContentView : public QWidget
{
    Q_OBJECT
public:
    explicit SettingContentView(QWidget *parent = nullptr);

    void appendCard(SettingContentCard* card);
    void setSize(QSize);

signals:
    void sendViewChange(int index);

public slots:
    void onScrollValueChange(int value);
    void onItemChange(int index);

protected:
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    void initUi();

private:
    QScrollArea * mScrollArea {nullptr};
    QVBoxLayout *mRow {nullptr};
    QList<SettingContentCard*> mCardList;
    QSize mSize = QSize(500, 300);

    bool mPressed = false;
    QPoint mPressPos;
};

#endif // SETTINGCONTENTVIEW_H
