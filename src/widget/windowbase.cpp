/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "windowbase.h"
#include "globalsignaltransfer.h"
#include <QCloseEvent>

WindowBase::WindowBase(int id, QWidget *parent) : QWidget(parent)
  , mId(id)
{
    connect(this, &WindowBase::sendWindowClosed, GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::onWindowClosed);
}

void WindowBase::closeEvent(QCloseEvent *event)
{
    event->ignore();
    closeWindow();
}

void WindowBase::closeWindow()
{
    this->hide();
    emit sendWindowClosed(mId);
}
