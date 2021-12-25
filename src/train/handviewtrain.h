#ifndef HANDVIEWTRAIN_H
#define HANDVIEWTRAIN_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QBoxLayout>
#include <QLabel>
#include "characterentity.h"

class HandViewTrain : public QLabel
{
    Q_OBJECT
public:
    explicit HandViewTrain(QWidget *parent = nullptr);

     //重写绘画事件
     void paintEvent(QPaintEvent *event);
     //鼠标离开事件
     void mouseReleaseEvent(QMouseEvent*);
     //鼠标移动事件
     void mouseMoveEvent(QMouseEvent*);
     //鼠标按下事件
     void mousePressEvent(QMouseEvent*);


 private:

     //离开手写界面多久后输入结束,单位毫秒
     int inputInterval = 500;

     //用来存储用户写字时按下的所有点
     int strokeId;
     CharacterEntity characterAll;
     CharacterEntity character;
     QVector<QVector<QPoint>> points;
     //用来存储笔画数，points中的集合个数
     int pointsSize = 0;
     //定时器，用户鼠标/手抬起后计时，如果在指定时间内没有按下，就当做用户输入完毕
     QTimer *mouseReleaseTimer;

 public: signals:
     void charToParent(CharacterEntity);

 public slots:
     //清空用户输入
     void clearPoints();
     void enterSolt();

};

#endif // HANDVIEWTRAIN_H
