/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "buttonitem.h"

ButtonItem::ButtonItem(QObject *parent) : QObject(parent)
{

}

EnglishButton* ButtonItem::getEnglishButton(QString str1, QString str2, int id, KeyButtonBase::KeyType type, QWidget *parent)
{
    EnglishButton *but = new EnglishButton(str1, str2, id, type, parent);
    if (KeyButtonBase::PinyinLetter == type) {
        connect(getShiftButton(), &ShiftButton::sendShiftClicked, but, &EnglishButton::onShiftClicked);
    }

    if (KeyButtonBase::PinyinPunc == type) {
        connect(getSwitchButton(), &CE_SwitchButton::sendSwitchClicked, but, &EnglishButton::onShiftClicked);
    }
    return but;
}

NumButton* ButtonItem::getNumButton(QString num, int id, KeyButtonBase::KeyType type, QWidget *parent)
{
    NumButton *but = new NumButton(num, id, type, parent);
    return but;
}

ShiftButton* ButtonItem::getShiftButton()
{
    static ShiftButton but;
    connect(getSwitchButton(), &CE_SwitchButton::sendSwitchClicked, &but, &ShiftButton::onEnglishInput);
    return &but;
}

CE_SwitchButton* ButtonItem::getSwitchButton()
{
    static CE_SwitchButton but;
    return &but;
}
