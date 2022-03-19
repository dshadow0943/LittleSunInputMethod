/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "settingcontentview.h"
#include <QPushButton>
#include <QScrollBar>
#include <QMouseEvent>
#include <QDebug>

SettingContentView::SettingContentView(QWidget *parent) : QWidget(parent)
{
    initUi();

    connect(mScrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &SettingContentView::onScrollValueChange);
}

void SettingContentView::initUi()
{
    mScrollArea = new QScrollArea(this);

    QWidget* pWgt = new QWidget;
    mRow = new QVBoxLayout(pWgt);
    mRow->setMargin(0);
    pWgt->setLayout(mRow);
    mScrollArea->setWidget(pWgt);
    mScrollArea->setFixedSize(mSize);
}

void SettingContentView::appendCard(SettingContentCard* cardWgt)
{
    cardWgt->setTopPos(mScrollArea->widget()->height());
    mCardList.push_back(cardWgt);
    mRow->addWidget(cardWgt);
    QWidget* pWgt = new QWidget;
    pWgt->setLayout(mRow);
    pWgt->setMaximumWidth(mSize.width()-5);
    mScrollArea->setWidget(pWgt);
//    pWgt->setAttribute(Qt::WA_TransparentForMouseEvents,true);
}

void SettingContentView::setSize(QSize size)
{
    mSize = size;
}

void SettingContentView::onScrollValueChange(int value)
{
    static int pValue = -1;

    if (value == mScrollArea->verticalScrollBar()->maximum()) {
        sendViewChange(mCardList.size()-1);
    } else {
        for (int i = 0; i < mCardList.size(); ++i) {
            if ((mCardList[i]->getTopPos() > pValue && mCardList[i]->getTopPos() <= value)
                    || (mCardList[i]->getTopPos() < pValue && mCardList[i]->getTopPos() >= value)) {
                sendViewChange(i);
                break;
            }
        }
    }
    pValue = value;
}

void SettingContentView::onItemChange(int index)
{
    mScrollArea->verticalScrollBar()->setValue(mCardList.at(index)->getTopPos());
}

void SettingContentView::mouseMoveEvent(QMouseEvent *e)
{
    if (mPressed) {
        QPoint currentPt = e->pos();
        int dist = mPressPos.y() - currentPt.y();
        mScrollArea->verticalScrollBar()->setValue(mScrollArea->verticalScrollBar()->value() + dist);
        mPressPos = currentPt;
    }
    QWidget::mouseMoveEvent(e);
}

void SettingContentView::mousePressEvent(QMouseEvent *e)
{
    mPressPos = e->pos();
    mPressed = true;
    QWidget::mousePressEvent(e);
}

void SettingContentView::mouseReleaseEvent(QMouseEvent *e)
{
    mPressed = false;
    QWidget::mouseReleaseEvent(e);
}
