/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "radiobuttonbase.h"
#include "globalsignaltransfer.h"

RadioButtonBase::RadioButtonBase(QString text, int id, int type, QWidget *parent) : QRadioButton(text, parent)
  , ButtonInterface (id, type)
{
    connect(this, &QRadioButton::clicked, this, &RadioButtonBase::onClicked);
    connect(this, &RadioButtonBase::sendClicked,
            GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::onRadioButtonClicked);

    setMinimumSize(100, 20);
}

void RadioButtonBase::onClicked()
{
    emit sendClicked(this);
}
