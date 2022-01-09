#ifndef ENKEYBOARD_H
#define ENKEYBOARD_H

#include "softkeyboard.h"
#include "buttonitem.h"
#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QToolButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QEvent>
#include <QLabel>

class EnKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit EnKeyboard(SoftKeyboard *parent);

signals:

public slots:

private:
    QList<KeyButtonBase*> mButLines; //按键集合

private:
    void initView();   //初始化布局

};

#endif // ENKEYBOARD_H
