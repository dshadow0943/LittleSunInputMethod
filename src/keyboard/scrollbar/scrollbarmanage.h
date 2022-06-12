/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef SCROLLBARMANAGE_H
#define SCROLLBARMANAGE_H

#include <vscrollbarview.h>
#include <hscrollbarview.h>

class ScrollBarManage : QObject
{
    Q_OBJECT
public:
    explicit ScrollBarManage();

    static ScrollBarManage* getInstace();
    static VScrollBarView* getVCanditateView();
    static HScrollBarView* getHCanditateView();
    static VScrollBarView* getVSrcllBarView(ScrollBarBase::ViewType type = ScrollBarBase::Invavid, QWidget *parent = nullptr);
    static HScrollBarView* getHSrcllBarView(ScrollBarBase::ViewType type = ScrollBarBase::Invavid, QWidget *parent = nullptr);

    void setCanditeData(QStringList& data);

signals:

public slots:

private:


};

#endif // SCROLLBARMANAGE_H
