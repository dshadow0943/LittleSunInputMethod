#ifndef VTRANSLATEVIEW_H
#define VTRANSLATEVIEW_H

#include "scrollbarbase.h"

class VScrollBarView : public ScrollBarBase
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *event);

    explicit VScrollBarView(QWidget *parent = nullptr);
};

#endif // VTRANSLATEVIEW_H