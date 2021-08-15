#include "vtranslateview.h"
#include "customwidget.h"
#include "customskin.h"
#include <QPainter>
#include <QPaintEvent>

/**
 * @brief VTranslateView::candidateInstace
 * 纵向候选框
 */
VTranslateView *VTranslateView::candidateInstace = nullptr;
VTranslateView *VTranslateView::puncInstance = nullptr;
VTranslateView::VTranslateView(QWidget *parent) : CustomCharView(parent)
{

}

VTranslateView *VTranslateView::getVTranslateView()
{
    if(candidateInstace == nullptr){
        candidateInstace = new VTranslateView;
    }
    return candidateInstace;
}
VTranslateView *VTranslateView::getPunctuation()
{
    if(puncInstance == nullptr){
        puncInstance= new VTranslateView;
    }
    return puncInstance;
}

void VTranslateView::paintEvent(QPaintEvent *event)
{
    //qDebug() << "绘画事件触发";
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(CUSTOMSKIN->candidateTextFont);

    QFontMetrics metrics(painter.font());
    int cur_x = 5;
    int text_w = 0;
    int text_h = qMax(metrics.height(), unitMinHeight);
    QString text;
    QRect text_rect;
    dataRects.clear();
    // 先绘制按下的矩形
    if (!pressRect.isEmpty())
    {
        painter.setPen(CUSTOMSKIN->candidateTextPressBKColor);
        painter.setBrush(CUSTOMSKIN->candidateTextPressBKColor);
        painter.drawRect(pressRect);
    }

    // 绘制所有的文字
    painter.setPen(CUSTOMSKIN->candidateTextPen);
    int cur_y = 0;
    for (int i = 0; i < dataStrings.size(); i++)
    {
        text = dataStrings.at(i);
        text_w = metrics.width(text) + 15;
        if (unitMinWidth != -1)
        {
            text_w = qMax(unitMinWidth, text_w);
        }

        if (cur_x + text_w > width())
        {
            cur_y += text_h + 5;
            cur_x = 5;
        }
        text_rect = QRect(cur_x, cur_y, text_w, text_h);
        painter.drawText(text_rect, text, QTextOption(Qt::AlignCenter));
        dataRects.append(text_rect);

        cur_x += text_w + 13;
    }

    setFixedHeight(cur_y + text_h + 5);

    CustomCharView::paintEvent(event);
}
