/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef NUMBUTTON_H
#define NUMBUTTON_H

#include "keybuttonbase.h"

class NumButton : public KeyButtonBase
{
    Q_OBJECT
public:
    explicit NumButton(QString num, int id = 0, KeyType type = Invalid, QWidget *parent = nullptr);

signals:

public slots:

private:

    QString mNum;
};

#endif // NUMBUTTON_H
