#ifndef VTRANSLATEVIEW_H
#define VTRANSLATEVIEW_H

#include "scrollbarbase.h"
#include <QDebug>

class VScrollBarView : public ScrollBarBase
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *event);

    explicit VScrollBarView(ViewType type = Invavid, QWidget *parent = nullptr);
};

#endif // VTRANSLATEVIEW_H
