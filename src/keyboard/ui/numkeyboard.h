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
    QList<NumButton*> mButLine; //按键集合

private:

    //初始化数字键盘按钮
    void initKeyValue();
    //初始化数字键盘布局
    void initKeyboard();
    //链接所有按钮的槽函数
    void initConnect();

signals:

public slots:
    void onClicked(ButtonBase* but);
};

#endif // NUMKEYBOARD_H
