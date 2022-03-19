/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef ENGLISHBUTTON_H
#define ENGLISHBUTTON_H

#include "keybuttonbase.h"

class EnglishButton : public KeyButtonBase
{
    Q_OBJECT
public:
    explicit EnglishButton(QString str1, QString str2, int id = 0, KeyType type = Invalid, QWidget *parent = nullptr);

    //设置显示字母
    void setLetter(bool isCaps);

signals:

public slots:

    void onShiftClicked(bool isCaps);

private:

    QString str1, str2;  //需要显示的字符

};

#endif // ENGLISHBUTTON_H
