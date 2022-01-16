#include "scrollbarbase.h"
#include "globalsignaltransfer.h"
#include <QEvent>
#include <QMouseEvent>

ScrollBarBase::ScrollBarBase(QWidget *parent) : QWidget(parent)
{
    connect(this, &ScrollBarBase::clicked, GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::onScrollBarclicked);
}
int ScrollBarBase::getUnitMinWidth() const
{
    return unitMinWidth;
}

void ScrollBarBase::setUnitMinWidth(int value)
{
    unitMinWidth = value;
}
int ScrollBarBase::getUnitMinHeight() const
{
    return unitMinHeight;
}

void ScrollBarBase::setUnitMinHeight(int value)
{
    unitMinHeight = value;
}

int ScrollBarBase::getUnitFontSize()
{
    return unitFontSize;
}

void ScrollBarBase::setUnitFontSize(int size)
{
    if (size < 10) {
        size = 8;
    }
    unitFontSize = size;
    setUnitMinWidth(size/2);
}

void ScrollBarBase::setData(QStringList& data)
{
    this->dataStrings = data;
    update();
}

void ScrollBarBase::clearData()
{
    dataStrings.clear();
    update();
}

bool ScrollBarBase::selectPhrase(int index)
{
    if (dataStrings.size() > index) {
        emit clicked(dataStrings.at(index), index);
        return true;
    }
    return false;
}

void ScrollBarBase::onDataChange(QStringList data)
{
    this->dataStrings = data;
    update();
}

bool ScrollBarBase::event(QEvent *e)
{
    static bool pressed = false;
    static QPoint pressedPoint;
    if(e->type() == QEvent::MouseButtonPress)
    {
        pressed = true;
        pressRect = QRect();
        QMouseEvent *mouse_event = static_cast<QMouseEvent *>(e);
        pressedPoint = mouse_event->globalPos();
        int index = findcontansMouseRect(mouse_event->pos(), pressRect);
        if(index != -1)
        {
            emit stringPressed(dataStrings.at(index),
                               mapToGlobal(QPoint(pressRect.x(), pressRect.y())));
            update(pressRect);
        }
        return true;
    }
    else if(e->type() == QEvent::MouseButtonRelease)
    {
        if(pressed)
        {
            if(!pressRect.isEmpty())
            {
                int index = dataRects.indexOf(pressRect);
                emit clicked(dataStrings.at(index), index);
            }
            update(pressRect);
            emit stringPressed("", QPoint());
        }
        pressed = false;
        pressRect = QRect();
        return true;
    }
    //鼠标左键按下的同时移动，如果移动到了另外的符号框内，就将对应的符号进行同样的操作
    else if(pressed && e->type() == QEvent::MouseMove)
    {
        if(pressed)
        {
            QRect cur_rect;
            QMouseEvent *mouse_event = static_cast<QMouseEvent *>(e);
            int index = findcontansMouseRect(mouse_event->pos(), cur_rect);
            if(index == -1)
            {
                emit(stringPressed("", QPoint()));
                pressed = false;
                update(pressRect);
                pressRect = QRect();

            }
        }
        return true;
    }
    return QWidget::event(e);
}

int ScrollBarBase::findcontansMouseRect(const QPoint &mousePos, QRect &rect)
{
    for (int i = 0; i < dataRects.size(); i++)
    {
        if (dataRects.at(i).contains(mousePos))
        {
            rect = dataRects.at(i);
            return i;
        }
    }

    return -1;
}
