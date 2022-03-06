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
#include "iconbutton.h"
#include <QSvgRenderer>
#include <QPainter>

IconButton::IconButton(QString path, QWidget *parent) : QLabel(parent)
  , mIconPath(path)
{
    if (mIconPath.endsWith("svg")) {
        mType = Svg;
    } else {
        mType = Other;
    }
    setAlignment(Qt::AlignCenter);
}

void IconButton::setIconPath(QString path)
{
    mIconPath = path;
    this->setPixmap(loadPixmap());
}

QPixmap IconButton::loadPixmap()
{
    int h = int(size().height()*0.8);
    QPixmap pixmap(h, h);
    switch (mType) {
    case Svg:{
        QSvgRenderer *svgRender = new QSvgRenderer(mIconPath);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        svgRender->render(&painter);
    }
        break;
    case Other:
    {
        QImage Image;
        QPixmap fitpixmap(mIconPath);
        pixmap = fitpixmap.scaled(size().width(), size().height(), Qt::KeepAspectRatio);
    }
        break;
    }

    return pixmap;
}

void IconButton::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    this->setPixmap(loadPixmap());
}
