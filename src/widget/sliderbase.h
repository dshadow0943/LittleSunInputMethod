/*
*
* Author:     leilong <dshadow@foxmail.com>
*
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
