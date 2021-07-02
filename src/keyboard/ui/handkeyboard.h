#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <softkeyboard.h>

#include "custompushbutton.h"
#include "characteritem.h"

namespace Ui {
class HandKeyboard;
}

class HandKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit HandKeyboard(SoftKeyboard *parent = nullptr);
    ~HandKeyboard();

    void setParent(SoftKeyboard *parent);

signals:
    void toEN_keyBoard();

public slots:
    void recognizeChinese(CharacterEntity&);
    void KeyClicked(int unicode, int key);

private:
    Ui::HandKeyboard *ui;

    SoftKeyboard *parent;
    //右侧工具栏__相关
    //删除按钮
    CustomPushButton *btnDel;
    //确认按钮
    CustomPushButton *btnSure;
    //abc/123按钮
    CustomPushButton *btnabc;
    //字符按钮
    CustomPushButton *btnChar;
    //键盘按钮
    CustomPushButton *btnKeyBoard;
    //右侧工具栏布局
    QVBoxLayout *layout;

private:
        void setRightToolWidget();

};

#endif // MYWIDGET_H
