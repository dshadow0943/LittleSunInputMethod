#include "scrollbarcontainer.h"
#include "vscrollbarview.h"

#include <QScrollBar>
#include <QEvent>
#include <QMouseEvent>

ScrollBarContainer::ScrollBarContainer(QWidget *parent)
: QWidget(parent)
{
}

void ScrollBarContainer::setWidget(QWidget *centerWidget, DIRECTION dire, int mouseSensitivity)
{
    this->mCenterWidget = centerWidget;
    this->mCenterWidget->setParent(this);
    this->mCenterWidget->installEventFilter(this);
    mDirection = dire;
    mMouseSensitivity = mouseSensitivity;
}

void ScrollBarContainer::resizeEvent(QResizeEvent *event)
{
    if (mDirection == Horizontal)
    {
        this->mCenterWidget->setFixedHeight(this->height());
        this->mCenterWidget->setMinimumWidth(this->width());
    }
    else
    {
        this->mCenterWidget->setMinimumHeight(this->height());
        this->mCenterWidget->setFixedWidth(this->width());
    }

    QWidget::resizeEvent(event);
}
bool ScrollBarContainer::eventFilter(QObject *obj, QEvent *event)
{
    static bool pressed = false;
    static QPoint lastPos;
    if (mCenterWidget == obj)
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
            if (mDirection == Horizontal)
            {
                if (wheel_event->delta() < 0)
                {
                    if (mCenterWidget->pos().x() - 1 >= width() - mCenterWidget->width())
                    {
                        mCenterWidget->move(mCenterWidget->pos().x() - mMouseSensitivity * 2, mCenterWidget->pos().y());
                    }
                }
                else if (wheel_event->delta() > 0)
                {
                    if (mCenterWidget->pos().x() + 1 <= 0)
                    {
                        mCenterWidget->move(mCenterWidget->pos().x() + mMouseSensitivity * 2, mCenterWidget->pos().y());
                    }
                }
            }
            else
            {
                if (wheel_event->delta() < 0)
                {
                    if (mCenterWidget->pos().y() - 1 >= height() - mCenterWidget->height())
                    {
                        mCenterWidget->move(mCenterWidget->pos().x(), mCenterWidget->pos().y() - mMouseSensitivity * 2);
                    }
                }
                else if (wheel_event->delta() > 0)
                {
                    if (mCenterWidget->pos().y() + 1 <= 0)
                    {
                        mCenterWidget->move(mCenterWidget->pos().x(), mCenterWidget->pos().y() + mMouseSensitivity * 2);
                    }
                }
            }
        }
        else if (event->type() == QEvent::MouseMove && pressed)
        {
            QMouseEvent *mouse_event = (QMouseEvent *)event;
            if (mDirection == Horizontal)
            {
                if (lastPos.x() > mouse_event->globalPos().x())
                {
                    if (mCenterWidget->pos().x() - 1 >= width() - mCenterWidget->width())
                    {
                        mCenterWidget->move(mCenterWidget->pos().x() - mMouseSensitivity, mCenterWidget->pos().y());
                    }
                }
                else if (lastPos.x() < mouse_event->globalPos().x())
                {
                    if (mCenterWidget->pos().x() + 1 <= 0)
                    {
                        mCenterWidget->move(mCenterWidget->pos().x() + mMouseSensitivity, mCenterWidget->pos().y());
                    }
                }
            }
            else
            {
                if (lastPos.y() > mouse_event->globalPos().y())
                {
                    if (mCenterWidget->pos().y() - 1 >= height() - mCenterWidget->height())
                    {
                        mCenterWidget->move(mCenterWidget->pos().x(), mCenterWidget->pos().y() - mMouseSensitivity);
                    }
                }
                else if (lastPos.y() < mouse_event->globalPos().y())
                {
                    if (mCenterWidget->pos().y() + 1 <= 0)
                    {
                        mCenterWidget->move(mCenterWidget->pos().x(), mCenterWidget->pos().y() + mMouseSensitivity);
                    }
                }
            }
            lastPos = mouse_event->globalPos();
        }
    }

    return QWidget::eventFilter(obj, event);
}

int ScrollBarContainer::getMouseSensitivity() const
{
    return mMouseSensitivity;
}

void ScrollBarContainer::setMouseSensitivity(int value)
{
    mMouseSensitivity = value;
}
