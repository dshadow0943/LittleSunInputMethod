/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef RADIOBUTTONBASE_H
#define RADIOBUTTONBASE_H

#include "buttoninterface.h"

#include <QWidget>
#include <QRadioButton>

class RadioButtonBase : public QRadioButton, public ButtonInterface
{
    Q_OBJECT
public:

    explicit RadioButtonBase(QString text = "", int id = 0, int type = 0, QWidget *parent = nullptr);

signals:
    void sendClicked(RadioButtonBase* but);

public slots:
    void onClicked();

};

#endif // RADIOBUTTONBASE_H
