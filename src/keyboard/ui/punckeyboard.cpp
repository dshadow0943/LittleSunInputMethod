#include "punckeyboard.h"
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
    this->parent = parent;
    initUi();
    initConnect();
}

void PuncKeyboard::initUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);

    mButs.push_back(ButtonItem::getNumButton("删除", Qt::Key_Backspace, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("确认", Qt::Key_Enter, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("中文", KeyButtonBase::KeyChinese, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("英文", KeyButtonBase::KeyEnglish, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("数学", KeyButtonBase::KeyMath, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("返回", KeyButtonBase::KeyBack, KeyButtonBase::Func, this));

    for (KeyButtonBase *but : mButs) {
        layout->addWidget(but,1);
    }

    punc = ScrollBarManage::getVSrcllBarView(this);
    ScrollBarContainer *customViw = new ScrollBarContainer(this);
    customViw->setWidget(punc, ScrollBarContainer::Vertical, 1);
    QStringList data = loadSymbols(":/symbol.txt");
    punc->setData(data);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(customViw, 6);
    QWidget *w = new QWidget;
    w->setLayout(layout);
    hLayout->addWidget(w, 1);
    layout->setSpacing(4);
    hLayout->setMargin(0);
    hLayout->setSpacing(1);
    this->setLayout(hLayout);
}

void PuncKeyboard::initConnect(){
    for (KeyButtonBase *but : mButs) {
        connect(but, &KeyButtonBase::sendClicked, this, &PuncKeyboard::onClicked);
    }
    connect(punc, &VScrollBarView::clicked, this, &PuncKeyboard::userSelectPunctuation);
}

void PuncKeyboard::userSelectPunctuation(const QString &text, int index)
{
    Q_UNUSED(index);
    parent->addCandidateCharacterText(text);
}

void PuncKeyboard::onClicked(KeyButtonBase* but)
{
    switch (but->getId()) {
    case Qt::Key_Backspace:
        parent->deleteSlot();
        break;
    case Qt::Key_Enter:
        parent->enterSlot();
        break;
    case KeyButtonBase::KeyChinese:
        break;
    case KeyButtonBase::KeyEnglish:
        break;
    case KeyButtonBase::KeyMath:
        break;
    case KeyButtonBase::KeyBack:
         parent->switchPreviousKey();
        break;
    }
}

QStringList PuncKeyboard::loadSymbols(const QString &file)
{
    QFile symbol_file(file);
    QStringList symbols;
    if (symbol_file.open(QIODevice::ReadOnly))
    {
        QString lineSymbols;
        while (!symbol_file.atEnd())
        {
            lineSymbols = QString::fromUtf8(symbol_file.readLine());
            lineSymbols = lineSymbols.trimmed();
            for (int i = 0; i < lineSymbols.size(); ++i)
            {
                symbols.append(lineSymbols.at(i));
            }
        }
        symbol_file.close();
    }

    return symbols;
}

