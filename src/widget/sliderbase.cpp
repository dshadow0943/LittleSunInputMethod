/*
*
* Author:     leilong <dshadow@foxmail.com>
*
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
