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
#include "sliderbase.h"
#include "globalsignaltransfer.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

SliderBase::SliderBase(int id, int type, QWidget *parent) : QWidget(parent)
  , ButtonInterface (id, type)
{
    initView();
    setFixedSize(400, 100);

    connect(mSlider, &QSlider::valueChanged, this, &SliderBase::onSliderMoved);
    connect(this, &SliderBase::sendValuechange, GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::onSliderValueChange);
}

void SliderBase::initView()
{
    mSlider = new SlideBar(Qt::Horizontal, this);
    setMinAndMaxNum(3, 40);
//    mSlider->setTickPosition(QSlider::TicksAbove);
    mValueLabel = new QLabel(this);
    mValueLabel->setAlignment(Qt::AlignCenter);

    QPushButton *sub = new QPushButton("-");
    QPushButton *plus = new QPushButton("+");
    plus->setFixedSize(30, 30);
    sub->setFixedSize(30, 30);
    connect(plus, &QPushButton::clicked, this, &SliderBase::onPlusClicked);
    connect(sub, &QPushButton::clicked, this, &SliderBase::onSubClicked);

    QWidget *w = new QWidget(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(sub);
    hLayout->addWidget(mValueLabel);
    hLayout->addWidget(plus);
    w->setLayout(hLayout);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(w);
    vLayout->addWidget(mSlider);
    this->setLayout(vLayout);
}

void SliderBase::setValue(int value)
{
    if (value > mSlider->maximum() || value < mSlider->minimum() || value == mValue) {
        return;
    }

    mValue = value;
    mSlider->setValue(mValue);
    mValueLabel->setText(QString("%1").arg(mValue));
    emit sendValuechange(this);
}

int SliderBase::getValue()
{
    return this->mValue;
}

void SliderBase::setMinAndMaxNum(int minNum, int maxNum)
{
    mSlider->setMaximum(maxNum);
    mSlider->setMinimum(minNum);
}

void SliderBase::onSliderMoved(int value)
{
    setValue(value);
}

void SliderBase::onPlusClicked()
{
    setValue(mValue+1);
}

void SliderBase::onSubClicked()
{
    setValue(mValue-1);
}
