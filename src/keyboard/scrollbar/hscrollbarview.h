#ifndef HTRANSLATEVIEW_H
#define HTRANSLATEVIEW_H

#include <QWidget>
#include "scrollbarbase.h"

class HScrollBarView : public ScrollBarBase
{
    Q_OBJECT
public:
    explicit HScrollBarView(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};
#endif // HTRANSLATEVIEW_H
