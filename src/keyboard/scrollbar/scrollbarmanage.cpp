/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "scrollbarmanage.h"

ScrollBarManage::ScrollBarManage() : QObject ()
{

}

ScrollBarManage* ScrollBarManage::getInstace()
{
    static ScrollBarManage bar;
    return &bar;
}

void ScrollBarManage::setCanditeData(QStringList& data)
{
    getHCanditateView()->setData(data);
    getVCanditateView()->setData(data);
}

VScrollBarView* ScrollBarManage::getVCanditateView()
{
    static VScrollBarView view(ScrollBarBase::Cand);
    return &view;
}

HScrollBarView* ScrollBarManage::getHCanditateView()
{
    static HScrollBarView view(ScrollBarBase::Cand);
    return &view;
}

VScrollBarView* ScrollBarManage::getVSrcllBarView(ScrollBarBase::ViewType type, QWidget *parent)
{
    return new VScrollBarView(type, parent);
}

HScrollBarView* ScrollBarManage::getHSrcllBarView(ScrollBarBase::ViewType type, QWidget *parent)
{
    return new HScrollBarView(type, parent);
}
