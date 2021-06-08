#ifndef VTRANSLATEVIEW_H
#define VTRANSLATEVIEW_H

#include "customcharview.h"

class VTranslateView : public CustomCharView
{
    Q_OBJECT

public:
    static VTranslateView *getVTranslateView();
    static VTranslateView *getPunctuation();
    void paintEvent(QPaintEvent *event);

private:
    explicit VTranslateView(QWidget *parent = nullptr);
    static VTranslateView *candidateInstace;
    static VTranslateView *puncInstance;

};
#define vTranslateView VTranslateView::getVTranslateView()
#define punctuations VTranslateView::getPunctuation()

#endif // VTRANSLATEVIEW_H
