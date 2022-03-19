/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "numbutton.h"

NumButton::NumButton(QString num, int id, KeyType type, QWidget *parent) : KeyButtonBase(id, type, parent)
  , mNum(num)
{
    setText(num);
}
