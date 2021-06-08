#ifndef ENKEYBOARD_H
#define ENKEYBOARD_H

#include "softkeyboard.h"
#include "custompushbutton.h"
#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QToolButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QEvent>
#include <QLabel>

class EnKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit EnKeyboard(SoftKeyboard *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void keyBoardToHide();
    void toNumKeyBoard();
    void toHandWidget();
    void toPunKeyBoard();
    void send_commit(const QString&);

public slots:
    void keyClicked(int general, int key);

private:

    QList<CustomPushButton *> allShiftChangeKeys; //语言切换时所有需要变化的按钮

    //数字集合
    QList<int> Btns123_value = {0,1,2,3,4,5,6,7,8,9};
    QList<CustomPushButton*> Btns123;
    //第一行字母集合
    //字母第一行
    QList<char> BtnsABC1_value_a = {'q','w','e','r','t','y','u','i','o','p'};
    QList<char> BtnsABC1_value_A = {'Q','W','E','R','T','Y','U','I','O','P'};
    QList<CustomPushButton*> BtnsABC1;
    //字母第二行
    QList<char> BtnsABC2_value_a = {'a','s','d','f','g','h','j','k','l'};
    QList<char> BtnsABC2_value_A = {'A','S','D','F','G','H','J','K','L'};
    QList<CustomPushButton*> BtnsABC2;
    //字母第三行,同时包括最左边的'大小写转换键' 以及最右边的'删除'键
    QList<QString> BtnsABC3_value_a = {"↑","z","x","c","v","b","n","m","删除"};
    QList<QString> BtnsABC3_value_A = {"↑","Z","X","C","V","B","N","M","删除"};
    QList<CustomPushButton*> BtnsABC3;
    //第五行 {'符号','123','，','空格','.','中/英','手写'}
    QList<QString> BtnsTool_value_ZH = {"符","123",",","空格",".","英","手写"};
    QList<QString> BtnsTool_value_EN = {"符","123",",","space",".","中","手写"};
    QList<CustomPushButton*> BtnsTool;

    SoftKeyboard* parent;

private:

    void caseChanged(bool);
    void initPinyinDictionary();
    //获取用户点击的按钮的值
    void getValue(QString value);
    void createConnect();
    void initView();   //初始化布局

};

#endif // ENKEYBOARD_H
