#include "handkeyboard.h"
#include "ui_handkeyboard.h"
#include "handview.h"

#include <QColorDialog>
#include <QFontDialog>

/**
 * @brief HandKeyboard::HandKeyboard
 * @param parent
 * 手写键盘
 */
HandKeyboard::HandKeyboard(SoftKeyboard *parent) :
    QWidget(parent),
    ui(new Ui::HandKeyboard)
{
    ui->setupUi(this);

    this->parent = parent;
    //设置右侧工具栏
    setRightToolWidget();
    connect(ui->handWritingWidget, &HandView::charToParent, this, &HandKeyboard::recognizeChinese);
}

void HandKeyboard::setRightToolWidget()
{
    QVBoxLayout *layout = new QVBoxLayout;

    mButs.push_back(ButtonItem::getNumButton("删除", Qt::Key_Backspace, ButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("确认", Qt::Key_Enter, ButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("数字", ButtonBase::KeyNum, ButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("符号", ButtonBase::keyPunc, ButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("拼音", ButtonBase::keyPinyin, ButtonBase::Func, this));

    for (ButtonBase *but : mButs) {
        layout->addWidget(but,1);
        connect(but, &ButtonBase::sendClicked, this, &HandKeyboard::onClicked);
    }

    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(1);

    /*将布局设置给右侧工具栏部件*/
    ui->rightToolWidget->setLayout(layout);
}

void HandKeyboard::onClicked(ButtonBase* but)
{
    switch (but->getId()) {
    case Qt::Key_Backspace:
        parent->deleteSlot();
        break;
    case Qt::Key_Enter:
        parent->enterSlot();
        break;
    case ButtonBase::KeyNum:
        parent->switchPage(KEYBOARD_NUM);
        break;
    case ButtonBase::keyPunc:
        parent->switchPage(KEYBOARD_PUNC);
        break;
    case ButtonBase::keyPinyin:
         parent->switchPage(KEYBOARD_EN);
        break;
    }
}

void HandKeyboard::recognizeChinese(CharacterEntity& character)
{
    if (parent == nullptr){
        qDebug() << "null";
        return;
    }
    parent->getTextByHand(character);
}

HandKeyboard::~HandKeyboard()
{
    delete parent;
    delete ui;
}



