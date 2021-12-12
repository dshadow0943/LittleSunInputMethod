#ifndef MYWIDGET_H
#define MYWIDGET_H


#include "softkeyboard.h"
#include "custompushbutton.h"
#include "characteritem.h"
#include "buttonitem.h"

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>

namespace Ui {
class HandKeyboard;
}

class HandKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit HandKeyboard(SoftKeyboard *parent);
    ~HandKeyboard();

signals:
    void toEN_keyBoard();

public slots:
    void recognizeChinese(CharacterEntity&);
    void onClicked(ButtonBase* but);

private:
    Ui::HandKeyboard *ui;

    SoftKeyboard *parent;
    //右侧工具栏__相关

    QList<ButtonBase*> mButs;
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


private:
        void setRightToolWidget();

};

#endif // MYWIDGET_H
