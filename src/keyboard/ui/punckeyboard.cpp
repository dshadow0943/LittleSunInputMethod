#include "punckeyboard.h"
#include "keyboardsidebar.h"
#include "thesaurusretrieval.h"
#include <QColorDialog>
#include <QFontDialog>
#include <QScrollArea>
#include <QFile>
#include <QHBoxLayout>
#include <QScrollArea>

/**
 * @brief PuncKeyboard::PuncKeyboard
 * @param parent
 * 符号键盘
 */
PuncKeyboard::PuncKeyboard(SoftKeyboard *parent) : QWidget(parent)
{
    initUi();
}

void PuncKeyboard::initUi()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(4);

    layout->addWidget(ButtonItem::getNumButton("返回", KeyButtonBase::KeyBack, KeyButtonBase::Func, this), 1);
    layout->addWidget(ButtonItem::getNumButton("←", Qt::Key_Backspace, KeyButtonBase::Func, this), 1);
    mTabSider = new KeyboardSidebar({"常用", "中文", "英文", "数学"}, this);
    connect(mTabSider, &KeyboardSidebar::sendCurrentIndex, this, &PuncKeyboard::onTabClicked);
    layout->addWidget(mTabSider, 4);

    mPunc = ScrollBarManage::getVSrcllBarView(ScrollBarBase::Punc, this);
    ScrollBarContainer *customViw = new ScrollBarContainer(this);
    customViw->setWidget(mPunc, ScrollBarContainer::Vertical, 2);
    connect(mPunc, &VScrollBarView::clicked, this, &PuncKeyboard::onPuncClick);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(customViw, 6);
    QWidget *w = new QWidget;
    w->setLayout(layout);
    hLayout->addWidget(w, 1);
    hLayout->setMargin(0);
    hLayout->setSpacing(1);
    this->setLayout(hLayout);
}

void PuncKeyboard::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    mTabSider->setCurrentIndex(0);
}

void PuncKeyboard::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    mTabSider->setFontSize(height()/6/3);
}

void PuncKeyboard::onTabClicked(int index)
{
    DBOperation::PuncType type = DBOperation::User;
    switch (index) {
    case 0:
        type = DBOperation::User;
        break;
    case 1:
        type = DBOperation::Chinese;
        break;
    case 2:
        type = DBOperation::English;
        break;
    case 3:
        type = DBOperation::Math;
        break;
    }

    mPunc->move(0, 0);

    ThesaurusRetrieval::getInstance()->asynExec<QStringList>([=](QStringList data){
        this->setPuncData(data);
    })->getPunc(type);
}

void PuncKeyboard::setPuncData(QStringList data)
{
    if (nullptr == mPunc) {
        return;
    }

    mPunc->setData(data);
}

void PuncKeyboard::onPuncClick(QString text, int index)
{
    Q_UNUSED(index);
    ThesaurusRetrieval::getInstance()->updatePunc(text, DBOperation::User);
}

