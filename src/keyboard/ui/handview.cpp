#include "handkeyboard.h"
#include "handview.h"

/**
 * @brief HandView::HandView
 * @param parent
 * 手写绘画界面
 */

HandView::HandView(QWidget *parent) : QWidget(parent)
{
    strokeId = 0;
    /*鼠标离开定时器*/
    mouseReleaseTimer = new QTimer();
    /*清空输入框并开始处理用户输入*/
    connect(mouseReleaseTimer, &QTimer::timeout, this, [=]()->void{

        clearPoints();
        update();

        /*停止计时器*/
        mouseReleaseTimer->stop();
    });
}

void HandView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
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
void HandView::mouseReleaseEvent(QMouseEvent* e)
{
//    qDebug() << "鼠标离开事件";
    //如果用户离开屏幕0.5秒没有书写，就当做用户本次输入完毕
    if(e->button() == Qt::LeftButton){
        //鼠标离开，开启定时器，如果定时器已开启，刷新定时器
        if(!mouseReleaseTimer->isActive())
            mouseReleaseTimer->start(inputInterval);
        else{
            mouseReleaseTimer->stop();
            mouseReleaseTimer->start(inputInterval);
        }
        //发送数据
        emit sendPonit(character);
    }
    return QWidget::mouseReleaseEvent(e);
}
//鼠标移动事件
void HandView::mouseMoveEvent(QMouseEvent* e)
{
    //在移动过程中捕捉到每一个点，储存起来
    if(e->buttons() & Qt::LeftButton){
        PointEntity point(e->x(), e->y());
        character.addPoint(strokeId, e->x(), e->y());
        update();
    }
    return QWidget::mouseMoveEvent(e);
}
//鼠标按下事件
void HandView::mousePressEvent(QMouseEvent* e)
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
        strokeId++;
        return;
    }
    return QWidget::mousePressEvent(e);
}

//清空用户输入
void HandView::clearPoints()
{
    character.clear();
    strokeId = 0;
}
