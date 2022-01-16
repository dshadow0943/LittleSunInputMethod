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
#ifndef SLIDERBASE_H
#define SLIDERBASE_H

#include "buttoninterface.h"
#include "slidebar.h"
#include <QWidget>
#include <QSlider>
#include <QLabel>

class SliderBase : public QWidget, public ButtonInterface
{
    Q_OBJECT
public:
    explicit SliderBase(int id = 0, int type = 0, QWidget *parent = nullptr);

    void setValue(int value);
    int getValue();
    void setMinAndMaxNum(int minNum, int maxNum);

signals:
    void sendValuechange(SliderBase* but);

public slots:
    void onSliderMoved(int value);
    void onPlusClicked();
    void onSubClicked();

private:
    void initView();

private:
    SlideBar *mSlider = nullptr;
    QLabel *mValueLabel = nullptr;

    int mValue = 0;
};

#endif // SLIDERBASE_H
