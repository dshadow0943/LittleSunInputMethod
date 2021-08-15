#ifndef PUNCKEYBOARD_H
#define PUNCKEYBOARD_H

#include "softkeyboard.h"
#include "vtranslateview.h"
#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QToolButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QEvent>
#include <QLatin1Char>
#include <QStringList>
#include "custompushbutton.h"
#include "customwidget.h"

class PuncKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit PuncKeyboard(SoftKeyboard *parent = nullptr);
    void setParent(SoftKeyboard *parent);

public slots:
    void userSelectPunctuation(const QString &text, int index);

private:
//    Ui::PunctuationsView *ui;
    SoftKeyboard *parent;
    CustomWidget            *customViw;  //字符拖拽控件
//    VTranslateView *punc;

    QStringList loadSymbols(const QString &file);

    void initPunctuation();
    void initKeyPunctuation();
    void initKeyboard();
    void setRightToolWidget();
    void changePage();

    int page = 1;
    QGridLayout *gridLayout;
    QToolButton* renderButton(QString);
    //获取用户点击的按钮的值
    void getValue(QString value);

    //右侧工具栏__相关
    //删除按钮
    CustomPushButton *btnDel;
    //确认按钮
    CustomPushButton *btnSure;
    //abc按钮
    CustomPushButton *btnabc;
    //123按钮
    CustomPushButton *btn123;
    //字符按钮
    CustomPushButton *btnLast;
    //键盘按钮
    CustomPushButton *btnBack;
    //右侧工具栏布局
    QVBoxLayout *layout;

};

#endif // PUNCKEYBOARD_H
