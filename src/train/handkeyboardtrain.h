/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef HANDKEYBOARDTRAIN_H
#define HANDKEYBOARDTRAIN_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include "characterentity.h"
#include "handviewtrain.h"
#include "thesaurusretrieval.h"
#include "windowbase.h"

class HandKeyboardTrain : public WindowBase
{
    Q_OBJECT
public:
    explicit HandKeyboardTrain(int id = 0, QWidget *parent = nullptr);

private:
    void setRightToolWidget();

    //右侧工具栏__相关
    //删除按钮
    QToolButton *btnDel;
    //确认按钮
    QToolButton *btnSure;
    //保存按钮
    QToolButton *btnSave;

    QToolButton *btnReset;

    HandViewTrain *keyboard;
    //右侧工具栏布局
    QVBoxLayout *layout;

    QList<CharacterEntity> characters;

private:

    ThesaurusRetrieval *mThesaurusManage;

    void enterPoint(CharacterEntity);

signals:
    void toEN_keyBoard();

public slots:
    void recognizeChinese(CharacterEntity);
    void saveSolt();
    void resetSolt();

};

#endif // HANDKEYBOARDTRAIN_H
