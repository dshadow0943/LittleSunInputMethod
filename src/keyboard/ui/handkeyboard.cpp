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

    mButs.push_back(ButtonItem::getNumButton("删除", Qt::Key_Backspace, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("确认", Qt::Key_Enter, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("数字", KeyButtonBase::KeyNum, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("符号", KeyButtonBase::keyPunc, KeyButtonBase::Func, this));
    mButs.push_back(ButtonItem::getNumButton("拼音", KeyButtonBase::keyPinyin, KeyButtonBase::Func, this));

    for (KeyButtonBase *but : mButs) {
        layout->addWidget(but,1);
        connect(but, &KeyButtonBase::sendClicked, this, &HandKeyboard::onClicked);
    }

    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(4);

    /*将布局设置给右侧工具栏部件*/
    ui->rightToolWidget->setLayout(layout);
}

void HandKeyboard::onClicked(KeyButtonBase* but)
{
    switch (but->getId()) {
    case Qt::Key_Backspace:
        parent->deleteSlot();
        break;
    case Qt::Key_Enter:
        parent->enterSlot();
        break;
    case KeyButtonBase::KeyNum:
        parent->switchPage(KEYBOARD_NUM);
        break;
    case KeyButtonBase::keyPunc:
        parent->switchPage(KEYBOARD_PUNC);
        break;
    case KeyButtonBase::keyPinyin:
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



