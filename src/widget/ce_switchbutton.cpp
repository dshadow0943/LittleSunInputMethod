/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "ce_switchbutton.h"

CE_SwitchButton::CE_SwitchButton(QString str1, QString str2, int id, KeyType type, QWidget *parent) : KeyButtonBase(id, type, parent)
  , str1(str1)
  , str2(str2)
{
    switchText((mIsEnglish));
}

bool CE_SwitchButton::isEnglish()
{
    return this->mIsEnglish;
}

void CE_SwitchButton::onClicked()
{
    KeyButtonBase::onClicked();
    switchText(!mIsEnglish);

}

void CE_SwitchButton::switchText(bool isEnglish)
{
    mIsEnglish = isEnglish;
    if (mIsEnglish) {
        setText(str1);
    } else {
        setText(str2);
    }
    emit sendSwitchClicked(mIsEnglish);
}
