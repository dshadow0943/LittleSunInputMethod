/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "englishbutton.h"

EnglishButton::EnglishButton(QString str1, QString str2, int id, KeyType type, QWidget *parent) : KeyButtonBase(id, type, parent)
  , str1(str1)
  , str2(str2)
{
    setLetter(false);
}

/**
 * @brief EnglishButton::setLetter
 * 设置显示字母
 * @param isCaps true: 显示大写字母， false: 显示小写字母
 */
void EnglishButton::setLetter(bool isCaps)
{
    if (isCaps) {
        setText(str1);
    } else {
        setText(str2);
    }
}

void EnglishButton::onShiftClicked(bool isCaps)
{
    setLetter(isCaps);
}
