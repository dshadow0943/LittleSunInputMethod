#ifndef NUMKEYBOARD_H
#define NUMKEYBOARD_H

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

private:
    QList<NumButton*> mButLine; //按键集合

private:

    //初始化数字键盘按钮
    void initKeyValue();
    //初始化数字键盘布局
    void initKeyboard();

signals:

public slots:

};

#endif // NUMKEYBOARD_H
