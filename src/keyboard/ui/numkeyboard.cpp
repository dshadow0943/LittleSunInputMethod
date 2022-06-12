#include "numkeyboard.h"

/**
 * @brief NumKeyboard::NumKeyboard
 * @param parent
 * 数字键盘
 */
NumKeyboard::NumKeyboard(SoftKeyboard *parent) : QWidget(parent)
{
    initKeyValue();
    initKeyboard();
}

/**
 * @brief num_keyboard::initKeyValue
 * 初始化按键
 */
void NumKeyboard::initKeyValue()
{

    mButLine.push_back(ButtonItem::getNumButton("+", KeyButtonBase::KeyInvalid, KeyButtonBase::Punc, this));
    mButLine.push_back(ButtonItem::getNumButton("1", Qt::Key_1, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("2", Qt::Key_2, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("3", Qt::Key_3, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("←", Qt::Key_Backspace, KeyButtonBase::Func, this));

    mButLine.push_back(ButtonItem::getNumButton("-", KeyButtonBase::KeyInvalid, KeyButtonBase::Punc, this));
    mButLine.push_back(ButtonItem::getNumButton("4", Qt::Key_4, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("5", Qt::Key_5, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("6", Qt::Key_6, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("0", Qt::Key_0, KeyButtonBase::Num, this));

    mButLine.push_back(ButtonItem::getNumButton("*", KeyButtonBase::KeyInvalid, KeyButtonBase::Punc, this));
    mButLine.push_back(ButtonItem::getNumButton("7", Qt::Key_7, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("8", Qt::Key_8, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("9", Qt::Key_9, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("@", Qt::Key_At, KeyButtonBase::Num, this));

    mButLine.push_back(ButtonItem::getNumButton("/", KeyButtonBase::KeyInvalid, KeyButtonBase::Punc, this));
    mButLine.push_back(ButtonItem::getNumButton("?符", KeyButtonBase::keyPunc, KeyButtonBase::Func, this));
    mButLine.push_back(ButtonItem::getNumButton(" ", Qt::Key_Space, KeyButtonBase::Num, this));
    mButLine.push_back(ButtonItem::getNumButton("abc", KeyButtonBase::keyPinyin, KeyButtonBase::Func, this));
    mButLine.push_back(ButtonItem::getNumButton("写", KeyButtonBase::keyHand, KeyButtonBase::Func, this));
}

/**
 * @brief num_keyboard::initKeyboard
 * 初始化键盘
 */
void NumKeyboard::initKeyboard()
{
    QGridLayout *gridLayout = new QGridLayout(this);
    //设置控件之间的间距
    gridLayout->setSpacing(3);
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
