#ifndef CUTOMPUSHBUTTON_H
#define CUTOMPUSHBUTTON_H

#include <QLabel>
#include <QPainter>

class CustomPushButton : public QLabel
{
    Q_OBJECT
public:
    explicit CustomPushButton(const QString &text, int generalKey, QWidget *parent = nullptr);
    explicit CustomPushButton(const QString &text, int generalKey, int type, QWidget *parent = nullptr);
    static QString EnText();
    static QString ChText();

protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);


private:
    int generalKey;
    //保存英文界面的所有按键
    static QList<CustomPushButton *> allBtns;
    //保存数字界面的所有按键
    static QList<CustomPushButton *> allNumBtns;
    //保存手写界面的所有按键
    static QList<CustomPushButton *> allHandBtns;

signals:
    void clicked(int unicode, int key);
    void clicked1();
    void shiftChanged(bool);

public slots:

private:
    //是否可选择
    bool checkable;
    //是否已选择
    bool checked;
    bool pressed;

    static bool shift;
    static bool chinese;
    static bool abc123; //手写界面 类型是否是字符&数字
    static int board; //键盘类型，默认为字母键盘

    friend class SoftKeyboard;
    friend class HandKeyboard;
    friend class EnKeyboard;
    friend class NumKeyboard;

};

#endif // CUTOMPUSHBUTTON_H
