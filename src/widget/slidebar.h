/*
*
* Author:     leilong <dshadow@foxmail.com>
*
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
