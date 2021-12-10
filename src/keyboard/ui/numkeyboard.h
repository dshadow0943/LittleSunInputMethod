#ifndef NUMKEYBOARD_H
#define NUMKEYBOARD_H

#include "custompushbutton.h"
#include "buttonitem.h"

#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QToolButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <softkeyboard.h>

class NumKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit NumKeyboard(SoftKeyboard *parent = nullptr);
    void setParent(SoftKeyboard *parent);

private:

    SoftKeyboard *parent;


    //第一行
    QList<NumButton*> mButLine;
    //第二行
    QList<NumButton*> mButLine2;
    //第三行
    QList<NumButton*> mButLine3;
    //第四行
    QList<NumButton*> mButLine4;

    //第一行
    QList<CustomPushButton*> BtnsLine1;
    //第二行
    QList<CustomPushButton*> BtnsLine2;
    //第三行
    QList<CustomPushButton*> BtnsLine3;
    //第四行
    QList<CustomPushButton*> BtnsLine4;

private:
    //链接所有按钮的槽函数
    void createConnect();
    //初始化数字键盘布局
    void initKeyboard();
    //初始化数字键盘按钮
    void initKeyValue();

signals:

public slots:
    void onClicked(ButtonBase* but);
};

#endif // NUMKEYBOARD_H
