#ifndef HTRANSLATEVIEW_H
#define HTRANSLATEVIEW_H

#include <QWidget>
#include "customcharview.h"

class HTranslateView : public CustomCharView
{
    Q_OBJECT
public:

    static HTranslateView *getHTranslateView();


protected:
    void paintEvent(QPaintEvent *event);

private:
    explicit HTranslateView(QWidget *parent = 0);
    static HTranslateView *instance;
};
#define hTranslateView HTranslateView::getHTranslateView()
#endif // HTRANSLATEVIEW_H
