#ifndef ENKEYBOARD_H
#define ENKEYBOARD_H

#include "softkeyboard.h"
#include "buttonitem.h"
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
    explicit EnKeyboard(SoftKeyboard *parent);

signals:
    void keyBoardToHide();
    void toNumKeyBoard();
    void toHandWidget();
    void toPunKeyBoard();
    void send_commit(const QString&);
    void sendCandidateCharacterText(QString character);  //非中文输入时的添加字符到输入框 / 中文输入时将选中的候选框的文字添加到候选框
    void userSelectChinese(const QString&, int);    //拼音输入时点击候选词的处理方法

public slots:
    void onClicked(ButtonBase* but);

private:

    QList<ButtonBase*> mButLines; //按键集合

    SoftKeyboard* parent;

private:
    void initPinyinDictionary();
    void initConnect();
    void initView();   //初始化布局

};

#endif // ENKEYBOARD_H
