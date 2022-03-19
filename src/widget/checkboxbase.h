/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef CHECKBOXBASE_H
#define CHECKBOXBASE_H

#include "buttoninterface.h"

#include <QCheckBox>


class CheckBoxBase : public QCheckBox , public ButtonInterface
{
    Q_OBJECT
public:
    explicit CheckBoxBase(QString text = "", int id = 0, int type = 0, QWidget *parent = nullptr);

signals:
    void sendClicked(CheckBoxBase* but);

public slots:
    void onClicked();
};

#endif // CHECKBOXBASE_H
