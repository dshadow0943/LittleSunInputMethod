/*
*
* Author:     leilong <dshadow@foxmail.com>
*
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
