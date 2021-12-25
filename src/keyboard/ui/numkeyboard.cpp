#include "numkeyboard.h"

/**
 * @brief NumKeyboard::NumKeyboard
 * @param parent
 * 数字键盘
 */
NumKeyboard::NumKeyboard(SoftKeyboard *parent) : QWidget(parent)
{
    this->parent = parent;

    initKeyValue();
    initKeyboard();
}

/**
 * @brief num_keyboard::initKeyValue
 * 初始化按键
 */
void NumKeyboard::initKeyValue()
{

    mButLine.push_back(ButtonItem::getNumButton("-", 0, ButtonBase::Punc, this));
    mButLine.push_back(ButtonItem::getNumButton("1", Qt::Key_1, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("2", Qt::Key_2, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("3", Qt::Key_3, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("删除", Qt::Key_Backspace, ButtonBase::Func, this));

    mButLine.push_back(ButtonItem::getNumButton("+", 0, ButtonBase::Punc, this));
    mButLine.push_back(ButtonItem::getNumButton("4", Qt::Key_4, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("5", Qt::Key_5, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("6", Qt::Key_6, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("0", Qt::Key_0, ButtonBase::Num, this));

    mButLine.push_back(ButtonItem::getNumButton("*", 0, ButtonBase::Punc, this));
    mButLine.push_back(ButtonItem::getNumButton("7", Qt::Key_7, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("8", Qt::Key_8, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("9", Qt::Key_9, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("@", Qt::Key_At, ButtonBase::Num, this));

    mButLine.push_back(ButtonItem::getNumButton("/", 0, ButtonBase::Punc, this));
    mButLine.push_back(ButtonItem::getNumButton("符号", ButtonBase::keyPunc, ButtonBase::Func, this));
    mButLine.push_back(ButtonItem::getNumButton(" ", Qt::Key_Space, ButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("拼音", ButtonBase::keyPinyin, ButtonBase::Func, this));
    mButLine.push_back(ButtonItem::getNumButton("手写", ButtonBase::keyHand, ButtonBase::Func, this));

    initConnect();
}

/**
 * @brief num_keyboard::initKeyboard
 * 初始化键盘
 */
void NumKeyboard::initKeyboard()
{
    QGridLayout *gridLayout = new QGridLayout(this);
    //设置控件之间的间距
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(0,0,0,0);
    this->setLayout(gridLayout);

    int count = 0;
    for(int i = 0; i < mButLine.size(); ++i) {
        int col = i%5;
        if (col == 0) {
            count = 0;
        }
        if (col == 0 || col == 4) {
            gridLayout->addWidget(mButLine[i], i/5, count, 1, 2);
            count += 2;
        } else {
            gridLayout->addWidget(mButLine[i], i/5, count, 1, 3);
            count+=3;
        }
    }
}

void NumKeyboard::initConnect()
{
    for (NumButton *but : mButLine) {
        connect(but, &NumButton::sendClicked, this, &NumKeyboard::onClicked);
    }
}

void NumKeyboard::onClicked(ButtonBase* but)
{
    if (but->getId() == Qt::Key_At) {
        parent->addCandidateCharacterText(QString("@"));
        return;
    }

    if (but->getType() == ButtonBase::Num || but->getType() == ButtonBase::Punc) {
        parent->addCandidateCharacterText(but->text());
        return;
    }

    switch (but->getId()) {
    case Qt::Key_Space:
        parent->spaceSlot();
        break;
    case Qt::Key_Backspace:
        parent->deleteSlot();
        break;
    case ButtonBase::keyPunc:
        parent->switchPage(3);
        break;
    case ButtonBase::keyPinyin:
        parent->switchPage(1);
        break;
    case ButtonBase::keyHand:
        parent->switchPage(2);
        break;
    }
}
