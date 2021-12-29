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
#include "handviewtrain.h"
#include "handwritemodel.h"

HandViewTrain::HandViewTrain(QWidget *parent) : QLabel(parent)
{
    setWindowFlag(Qt::WindowFlags::enum_type::WindowDoesNotAcceptFocus);
    strokeId = 0;
      /*鼠标离开定时器*/
      mouseReleaseTimer = new QTimer();
      /*清空输入框并开始处理用户输入*/
      connect(mouseReleaseTimer, &QTimer::timeout, this, [=]()->void{

          characterAll = character;
          HandWriteModel::getTurnPoints(&character);
          update();

          /*停止计时器*/
          mouseReleaseTimer->stop();
      });
}

//重写绘画事件
void HandViewTrain::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(points.empty()){
        return;
    }
    //创建画家
    QPainter painter(this);
    //设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    //创建画笔
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    for(int i = 0; i < character.strokes.size(); i++){
        StrokeEntity stroke = character.strokes.at(i);
        for(int j = 0; j < stroke.points.size()-1; j++){
            //每两点间画线，避免捕捉事件不及时导致写字过程中出现空白
            painter.drawLine(stroke.points[j].x, stroke.points[j].y, stroke.points[j+1].x, stroke.points[j+1].y);
        }
    }
}
//鼠标离开事件
void HandViewTrain::mouseReleaseEvent(QMouseEvent* e)
{
    //如果用户离开屏幕0.5秒没有书写，就当做用户本次输入完毕
    if(e->button() == Qt::LeftButton){
        //鼠标离开，开启定时器，如果定时器已开启，刷新定时器
        if(!mouseReleaseTimer->isActive())
            mouseReleaseTimer->start(inputInterval);
        else{
            mouseReleaseTimer->stop();
            mouseReleaseTimer->start(inputInterval);
        }
    }
    return QWidget::mouseReleaseEvent(e);
}
//鼠标移动事件
void HandViewTrain::mouseMoveEvent(QMouseEvent* e)
{
    //在移动过程中捕捉到每一个点，储存起来
    if(e->buttons() & Qt::LeftButton){
        PointEntity point(e->x(), e->y());
        character.addPoint(strokeId, e->x(), e->y());
        points[pointsSize-1].push_back(QPoint(e->x(), e->y()));
        update();
    }
    return QWidget::mouseMoveEvent(e);
}
//鼠标按下事件
void HandViewTrain::mousePressEvent(QMouseEvent* e)
{

    if (strokeId == 0){
        character.clear();
    }
    //按下时判断鼠标离开定时器是否在计时，如果正在计时就将其关闭
    if(mouseReleaseTimer->isActive()){
        mouseReleaseTimer->stop();
    }
    //鼠标每一次按下都创建一个新的集合并保存
    if(e->button()  == Qt::LeftButton){
        points.push_back(QVector<QPoint>());
        strokeId++;
        pointsSize++;
        return;
    }
    return QWidget::mousePressEvent(e);
}

void HandViewTrain::enterSolt()
{
    if (strokeId != 0){
        charToParent(characterAll);
    }
}

//清空用户输入
void HandViewTrain::clearPoints()
{
    update();

    strokeId = 0;
    this->pointsSize = 0;
    this->points.clear();
}

