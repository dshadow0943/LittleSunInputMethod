/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "slidebar.h"

SlideBar::SlideBar(QWidget *parent) : QSlider(parent)
{
    initView();
}

SlideBar::SlideBar(Qt::Orientation orientation, QWidget *parent) : QSlider(orientation, parent)
{
    initView();
}

void SlideBar::initView()
{
//    setStyleSheet("QSlider::groove:horizontal {"
//             "height: 6px;"
//             "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(124, 124, 124), stop: 1.0 rgb(72, 71, 71));"
//     "}"
//     "QSlider::handle:horizontal {"
//             "width: 1px;"
//             "background: rgb(0, 160, 230);"
//             "margin: -6px 0px -6px 0px;"
//             "border-radius: 9px;"
//     "}");
}

void SlideBar::wheelEvent(QWheelEvent * e)
{
    QWidget::wheelEvent(e);
}
