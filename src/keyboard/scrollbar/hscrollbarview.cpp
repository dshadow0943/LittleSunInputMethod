#include "hscrollbarview.h"
#include "scrollbarcontainer.h"
#include "customskin.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

/**
 * @brief HTranslateView::HScrollBarView
 * 横向候选框
 */
HScrollBarView::HScrollBarView(QWidget *parent) : ScrollBarBase(parent)
{

}

void HScrollBarView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(CUSTOMSKIN->candidateTextFont);

    QFontMetrics metrics(painter.font());
    int cur_x = 10;
    int text_w = 0;
    QString text;
    QRect text_rect;
    dataRects.clear();

    if(!pressRect.isEmpty())
    {
        painter.setPen(CUSTOMSKIN->candidateTextPressBKColor);
        painter.setBrush(CUSTOMSKIN->candidateTextPressBKColor);
        painter.drawRect(pressRect);
    }

    //绘制所有文字
    painter.setPen(CUSTOMSKIN->candidateTextPen);
    for(int i = 0; i < dataStrings.size(); i++)
    {
        //qDebug() << dataStrings.at(i);
        text = dataStrings.at(i);
        text_w = metrics.width(text)+15;
        if(unitMinWidth != -1)
        {
            text_w = qMax(unitMinWidth, text_w);

        }
        text_rect = QRect(cur_x, 0, text_w, height());
        painter.drawText(text_rect, text, QTextOption(Qt::AlignCenter));
        dataRects.append(text_rect);
        cur_x += text_w+15;
    }
    setFixedWidth(cur_x);

    ScrollBarBase::paintEvent(event);
}
