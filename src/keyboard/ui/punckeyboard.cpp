#include "punckeyboard.h"
#include "keyboardsidebar.h"
#include "thesaurusretrieval.h"
#include <QColorDialog>
#include <QFontDialog>
#include <QGridLayout>
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
    KeyboardSidebar *tabSider = new KeyboardSidebar({"常用", "中文", "英文", "数学"}, this);
    connect(tabSider, &KeyboardSidebar::sendCurrentIndex, this, &PuncKeyboard::onTabClicked);
    layout->addWidget(tabSider, 4);

    mPunc = ScrollBarManage::getVSrcllBarView(this);
    ScrollBarContainer *customViw = new ScrollBarContainer(this);
    customViw->setWidget(mPunc, ScrollBarContainer::Vertical, 2);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(customViw, 6);
    QWidget *w = new QWidget;
    w->setLayout(layout);
    hLayout->addWidget(w, 1);
    hLayout->setMargin(0);
    hLayout->setSpacing(1);
    this->setLayout(hLayout);
    tabSider->setCurrentIndex(0);
}

void PuncKeyboard::onTabClicked(int index)
{
    switch (index) {
    case 0:
        setPuncData(ThesaurusRetrieval::getInstance()->getPunc(DBOperation::User));
        break;
    case 1:
        setPuncData(ThesaurusRetrieval::getInstance()->getPunc(DBOperation::Chinese));
        break;
    case 2:
        setPuncData(ThesaurusRetrieval::getInstance()->getPunc(DBOperation::English));
        break;
    case 3:
        setPuncData(ThesaurusRetrieval::getInstance()->getPunc(DBOperation::Math));
        break;
    }
}

void PuncKeyboard::setPuncData(QStringList data)
{
    if (nullptr == mPunc) {
        return;
    }
    mPunc->setData(data);
}

