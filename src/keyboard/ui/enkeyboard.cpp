#include "enkeyboard.h"
#include <QMessageBox>
#include <QApplication>

/**
 * @brief EnKeyboard::EnKeyboard
 * @param parent
 * 拼音键盘
 */
EnKeyboard::EnKeyboard(SoftKeyboard *parent) : QWidget(parent)
{
    this->parent = parent;
    //初始化键盘
    initPinyinDictionary();
    initView();
    initConnect();
}

void EnKeyboard::initPinyinDictionary()
{
    bool ret = XYInputSearchInterface::getInstance()->initInputBase(qApp->applicationDirPath()
                                                                    + "/chineseBase/chinese.db");
    if(!ret)
    {
#ifdef Q_OS_LINUX
        ret = XYInputSearchInterface::getInstance()->initInputBase(qApp->applicationDirPath()
                                                                   + "/../../chineseBase/chinese.db");

        if (!ret) {
            ret = XYInputSearchInterface::getInstance()->initInputBase(qApp->applicationDirPath()
                                                                       + "/usr/local/littlesun/chineseBase/chinese.db");
        }

#endif

#ifdef Q_OS_WIN
        ret = XYInputSearchInterface::getInstance()->initInputBase(qApp->applicationDirPath()
                                                                   + "/../../LittleSunInputMethod/chineseBase/chinese.db");
#endif

    }

    //如果最终还是加载失败，警告
    if (!ret) {
        QMessageBox::warning(nullptr, "warning", "Load lexicon failed!", QMessageBox::Ok);

    }
}

void EnKeyboard::initView()
{
    //创建栅格布局
    QGridLayout *gridLayout = new QGridLayout;

    //设置控件之间的间距
    gridLayout->setSpacing(1);
    //设置栅格布局控件与窗体之间的间距
    gridLayout->setContentsMargins(0,0,0,0);
    this->setLayout(gridLayout);

    mButLines.push_back(ButtonItem::getNumButton("0", Qt::Key_0, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("1", Qt::Key_1, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("2", Qt::Key_2, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("3", Qt::Key_3, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("4", Qt::Key_4, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("5", Qt::Key_5, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("6", Qt::Key_6, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("7", Qt::Key_7, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("8", Qt::Key_8, KeyButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("9", Qt::Key_9, KeyButtonBase::PinyinNum, this));

    for(int i = 0; i < 10; ++i) {
        gridLayout->addWidget(mButLines[i],0,i*2,1,2);
    }

    mButLines.push_back(ButtonItem::getEnglishButton("Q", "q", Qt::Key_Q, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("W", "w", Qt::Key_W, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("E", "e", Qt::Key_E, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("R", "r", Qt::Key_R, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("T", "t", Qt::Key_T, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("Y", "y", Qt::Key_Y, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("U", "u", Qt::Key_U, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("I", "i", Qt::Key_I, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("O", "o", Qt::Key_O, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("P", "p", Qt::Key_P, KeyButtonBase::PinyinLetter, this));

    for(int i = 0; i < 10; i++){
        //将按钮添加到布局中
        gridLayout->addWidget(mButLines[i+10],1,i*2,1,2);
    }

    mButLines.push_back(ButtonItem::getEnglishButton("A", "a", Qt::Key_A, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("S", "s", Qt::Key_S, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("D", "d", Qt::Key_D, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("F", "f", Qt::Key_F, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("G", "g", Qt::Key_G, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("H", "h", Qt::Key_H, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("J", "j", Qt::Key_J, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("K", "k", Qt::Key_K, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("L", "l", Qt::Key_L, KeyButtonBase::PinyinLetter, this));

    //初始化字母按键第二行
    for(int i = 0; i < 9; i++){
        //将按钮添加到布局中
        gridLayout->addWidget(mButLines[i+20],2,1+i*2,1,2);
        //设置控件之间的间距
        gridLayout->setSpacing(1);
        //设置栅格布局控件与窗体之间的间距
        gridLayout->setContentsMargins(0,0,0,0);
        this->setLayout(gridLayout);
    }

    mButLines.push_back(ButtonItem::getShiftButton());
    mButLines.push_back(ButtonItem::getEnglishButton("Z", "z", Qt::Key_S, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("X", "x", Qt::Key_D, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("C", "c", Qt::Key_F, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("V", "v", Qt::Key_G, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("B", "b", Qt::Key_H, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("N", "n", Qt::Key_J, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("M", "m", Qt::Key_K, KeyButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getNumButton("删除",Qt::Key_Backspace, KeyButtonBase::Func, this));
    mButLines.push_back(ButtonItem::getNumButton("确认",Qt::Key_Enter, KeyButtonBase::Func, this));

    //初始化字母按键第三行
    for(int i = 0; i < 10; i++){
        gridLayout->addWidget(mButLines[i+29], 4, i*2, 1, 2);
    }

    mButLines.push_back(ButtonItem::getNumButton("123", KeyButtonBase::KeyNum, KeyButtonBase::Func, this));
    mButLines.push_back(ButtonItem::getNumButton("符号", KeyButtonBase::keyPunc, KeyButtonBase::Func, this));
    mButLines.push_back(ButtonItem::getEnglishButton(",", "，", Qt::Key_Comma, KeyButtonBase::PinyinPunc, this));
    mButLines.push_back(ButtonItem::getNumButton(" ", Qt::Key_Space, KeyButtonBase::Func, this));
    mButLines.push_back(ButtonItem::getEnglishButton(".", "。", Qt::Key_Camera, KeyButtonBase::PinyinPunc, this));
    mButLines.push_back(ButtonItem::getSwitchButton());
    mButLines.push_back(ButtonItem::getNumButton("手写", KeyButtonBase::keyHand, KeyButtonBase::Func, this));

    //初始化第五行
    int row = 0;
    for(int i = 0; i < 7; i++){
        //将按钮添加到布局中
        if (i == 0 || i == 6){
            gridLayout->addWidget(mButLines[i+39],5,row,1,3);
            row += 3;
        }
        if (i == 1 || i == 2 || i == 4 || i == 5){
            gridLayout->addWidget(mButLines[i+39],5,row,1,2);
            row += 2;
        }
        if (i == 3){
            gridLayout->addWidget(mButLines[i+39],5,row,1,6);
            row += 6;
        }
    }
}

void EnKeyboard::initConnect(){
    for (KeyButtonBase *but : mButLines) {
        connect(but, &KeyButtonBase::sendClicked, this, &EnKeyboard::onClicked);
    }
}

void EnKeyboard::onClicked(KeyButtonBase* but)
{
    if (ButtonItem::getSwitchButton()->getIsEnglish()) {
        if (but->getType() == KeyButtonBase::PinyinLetter
                || but->getType() == KeyButtonBase::PinyinNum
                || but->getType() == KeyButtonBase::PinyinPunc) {
            emit sendCandidateCharacterText(but->text());
            return;
        }

    } else {
        if (but->getType() == KeyButtonBase::PinyinLetter) {
            parent->addCandidateLetter(but->text());
            return;
        }
        if (but->getType() == KeyButtonBase::PinyinPunc) {
            emit sendCandidateCharacterText(but->text());
        }
    }

    switch (but->getId()) {
    case Qt::Key_Backspace:
        parent->deleteSlot();
        break;
    case Qt::Key_Enter:
        parent->enterSlot();
        break;
    case Qt::Key_Space:
        parent->spaceSlot();
        break;
    case KeyButtonBase::KeyNum:
        parent->switchPage(KEYBOARD_NUM);
        break;
    case KeyButtonBase::keyPunc:
        parent->switchPage(KEYBOARD_PUNC);
        break;
    case KeyButtonBase::keyHand:
         parent->switchPage(KEYBOARD_HAND);
        break;
    }
}
