#include "customwidget.h"
#include <QScrollBar>
#include <QEvent>
#include <QMouseEvent>

CustomWidget::CustomWidget(QWidget *parent)
: QWidget(parent)
{
}

void CustomWidget::init(QWidget *centerWidget, DIRECTION dire)
{
    this->centerWidget = centerWidget;
    this->centerWidget->setParent(this);
    this->centerWidget->installEventFilter(this);
    direction = dire;
    mouseSensitivity = 1;
}

void CustomWidget::resizeEvent(QResizeEvent *event)
{
    if (direction == HORIZONTAL1)
    {
        this->centerWidget->setFixedHeight(this->height());
        this->centerWidget->setMinimumWidth(this->width());
    }
    else
    {
        this->centerWidget->setMinimumHeight(this->height());
        this->centerWidget->setFixedWidth(this->width());
    }

    QWidget::resizeEvent(event);
}
bool CustomWidget::eventFilter(QObject *obj, QEvent *event)
{
    static bool pressed = false;
    static QPoint lastPos;
    if (centerWidget == obj)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouse_event = (QMouseEvent *)event;
            pressed = true;
            lastPos = mouse_event->globalPos();
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            pressed = false;
            lastPos = QPoint();
        }
        else if (event->type() == QEvent::Wheel)
        {
            QWheelEvent *wheel_event = (QWheelEvent *)event;
            if (direction == HORIZONTAL1)
            {
                if (wheel_event->delta() < 0)
                {
                    if (centerWidget->pos().x() - 1 >= width() - centerWidget->width())
                    {
                        centerWidget->move(centerWidget->pos().x() - mouseSensitivity * 2, centerWidget->pos().y());
                    }
                }
                else if (wheel_event->delta() > 0)
                {
                    if (centerWidget->pos().x() + 1 <= 0)
                    {
                        centerWidget->move(centerWidget->pos().x() + mouseSensitivity * 2, centerWidget->pos().y());
                    }
                }
            }
            else
            {
                if (wheel_event->delta() < 0)
                {
                    if (centerWidget->pos().y() - 1 >= height() - centerWidget->height())
                    {
                        centerWidget->move(centerWidget->pos().x(), centerWidget->pos().y() - mouseSensitivity * 2);
                    }
                }
                else if (wheel_event->delta() > 0)
                {
                    if (centerWidget->pos().y() + 1 <= 0)
                    {
                        centerWidget->move(centerWidget->pos().x(), centerWidget->pos().y() + mouseSensitivity * 2);
                    }
                }
            }
        }
        else if (event->type() == QEvent::MouseMove && pressed)
        {
            QMouseEvent *mouse_event = (QMouseEvent *)event;
            if (direction == HORIZONTAL1)
            {
                if (lastPos.x() > mouse_event->globalPos().x())
                {
                    if (centerWidget->pos().x() - 1 >= width() - centerWidget->width())
                    {
                        centerWidget->move(centerWidget->pos().x() - mouseSensitivity, centerWidget->pos().y());
                    }
                }
                else if (lastPos.x() < mouse_event->globalPos().x())
                {
                    if (centerWidget->pos().x() + 1 <= 0)
                    {
                        centerWidget->move(centerWidget->pos().x() + mouseSensitivity, centerWidget->pos().y());
                    }
                }
            }
            else
            {
                if (lastPos.y() > mouse_event->globalPos().y())
                {
                    if (centerWidget->pos().y() - 1 >= height() - centerWidget->height())
                    {
                        centerWidget->move(centerWidget->pos().x(), centerWidget->pos().y() - mouseSensitivity);
                    }
                }
                else if (lastPos.y() < mouse_event->globalPos().y())
                {
                    if (centerWidget->pos().y() + 1 <= 0)
                    {
                        centerWidget->move(centerWidget->pos().x(), centerWidget->pos().y() + mouseSensitivity);
                    }
                }
            }
            lastPos = mouse_event->globalPos();
        }
    }

    return QWidget::eventFilter(obj, event);
}

int CustomWidget::getMouseSensitivity() const
{
    return mouseSensitivity;
}

void CustomWidget::setMouseSensitivity(int value)
{
    mouseSensitivity = value;
}
