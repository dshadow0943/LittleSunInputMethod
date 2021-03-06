/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef BUTTONBASE_H
#define BUTTONBASE_H

#include "buttoninterface.h"
#include "settingmanage.h"
#include <QObject>
#include <QPushButton>
#include <QPaintEvent>

class KeyButtonBase : public QPushButton, public ButtonInterface
{
    Q_OBJECT
public:

    enum KeyType {
        Invalid = 0,
        PinyinLetter,  //拼音键盘字母按键
        PinyinNum,     //拼音键盘数字按键
        PinyinPunc,    //拼音键盘符号
        Num,           //数字键盘数字按键
        Func,          //功能按键
        Punc,          //符号按键
        Tab,
    };

    enum KeyId {
        KeyInvalid = 0,
        KeyNum,  //数字
        keyPinyin,  //拼音
        keyHand, //手写
        keyPunc, //符号
        KeySwitch, //中英文切换键
        KeyChinese, //中文
        KeyEnglish, //英文
        KeyMath, //数学
        KeyBack, //返回
    };

    explicit KeyButtonBase(int id = 0, KeyType type = Invalid, QWidget *parent = nullptr);
    void setText(const QString &str);
    QString getText();

signals:
    void sendClicked(KeyButtonBase* but);

protected slots:
    void onThemeChange();

protected:
    virtual void setKeyStyleSheet();
    virtual void onClicked();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void timerEvent( QTimerEvent *event) override;

protected:
    QString mText;
    bool mPressed = false;
    int mCount = 0;
    int mTimerId = -1;
    skin_color colors;
};
#endif // BUTTONBASE_H
