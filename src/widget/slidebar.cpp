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
