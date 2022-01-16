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
#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include <QWidget>
#include <QSlider>

class SlideBar : public QSlider
{
    Q_OBJECT
public:
    explicit SlideBar(QWidget *parent = nullptr);
    explicit SlideBar(Qt::Orientation orientation, QWidget *parent = nullptr);

signals:

public slots:

protected:
    void wheelEvent(QWheelEvent * e);

private:
    void initView();
};

#endif // SLIDEBAR_H
