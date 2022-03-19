/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef CE_SWITCHBUTTON_H
#define CE_SWITCHBUTTON_H

#include "keybuttonbase.h"

/**
 * @brief The CE_SwitchButton class
 * 拼音键盘中英文切换按键
 */
class CE_SwitchButton : public KeyButtonBase
{
    Q_OBJECT
public:
    explicit CE_SwitchButton(QString str1 = "En", QString str2 = "中", int id = KeySwitch, KeyType type = Func, QWidget *parent = nullptr);

    void switchText(bool isEnglish);
    bool isEnglish();

signals:
    void sendSwitchClicked(bool isEnflish);

private:
    void onClicked() override;

private:
    QString str1, str2;  //需要显示的字符

    bool mIsEnglish = true;
};

#endif // CE_SWITCHBUTTON_H
