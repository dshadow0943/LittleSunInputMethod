/*
* Copyright (C) 2019 ~ 2019 UnionTech Software Technology Co.,Ltd.
*
* Author:     leilong <dshadow@foxmail.com>
*
* Maintainer: leilong <dshadow@foxmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
