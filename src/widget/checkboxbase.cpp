/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "checkboxbase.h"
#include "globalsignaltransfer.h"

CheckBoxBase::CheckBoxBase(QString text, int id, int type, QWidget *parent) : QCheckBox(text, parent)
  , ButtonInterface (id, type)
{
    setMinimumSize(100, 20);
    connect(this, &QCheckBox::clicked, this, &CheckBoxBase::onClicked);
    connect(this, &CheckBoxBase::sendClicked,
            GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::onCheckBoxClicked);
}

void CheckBoxBase::onClicked()
{
    emit sendClicked(this);
}
