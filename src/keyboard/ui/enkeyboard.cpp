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
//    caseChanged(CustomPushButton::shift);
}

void EnKeyboard::setParent(SoftKeyboard *parent){
    this->parent = parent;
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

    mButLines.push_back(ButtonItem::getNumButton("0", Qt::Key_0, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("1", Qt::Key_1, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("2", Qt::Key_2, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("3", Qt::Key_3, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("4", Qt::Key_4, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("5", Qt::Key_5, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("6", Qt::Key_6, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("7", Qt::Key_7, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("8", Qt::Key_8, ButtonBase::PinyinNum, this));
    mButLines.push_back(ButtonItem::getNumButton("9", Qt::Key_9, ButtonBase::PinyinNum, this));

    for(int i = 0; i < 10; ++i) {
        gridLayout->addWidget(mButLines[i],0,i*2,1,2);
    }

    mButLines.push_back(ButtonItem::getEnglishButton("Q", "q", Qt::Key_Q, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("W", "w", Qt::Key_W, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("E", "e", Qt::Key_E, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("R", "r", Qt::Key_R, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("T", "t", Qt::Key_T, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("Y", "y", Qt::Key_Y, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("U", "u", Qt::Key_U, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("I", "i", Qt::Key_I, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("O", "o", Qt::Key_O, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("P", "p", Qt::Key_P, ButtonBase::PinyinLetter, this));

    for(int i = 0; i < 10; i++){
        //将按钮添加到布局中
        gridLayout->addWidget(mButLines[i+10],1,i*2,1,2);
    }

    mButLines.push_back(ButtonItem::getEnglishButton("A", "a", Qt::Key_A, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("S", "s", Qt::Key_S, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("D", "d", Qt::Key_D, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("F", "f", Qt::Key_F, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("G", "g", Qt::Key_G, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("H", "h", Qt::Key_H, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("J", "j", Qt::Key_J, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("K", "k", Qt::Key_K, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("L", "l", Qt::Key_L, ButtonBase::PinyinLetter, this));

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
    mButLines.push_back(ButtonItem::getEnglishButton("Z", "z", Qt::Key_S, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("X", "x", Qt::Key_D, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("C", "c", Qt::Key_F, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("V", "v", Qt::Key_G, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("B", "b", Qt::Key_H, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("N", "n", Qt::Key_J, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton("M", "m", Qt::Key_K, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getNumButton("删除",Qt::Key_Backspace, ButtonBase::Func, this));
    mButLines.push_back(ButtonItem::getNumButton("确认",Qt::Key_Enter, ButtonBase::Func, this));

    //初始化字母按键第三行
    for(int i = 0; i < 10; i++){
        gridLayout->addWidget(mButLines[i+29], 4, i*2, 1, 2);
    }

    mButLines.push_back(ButtonItem::getNumButton("123", ButtonBase::KeyNum, ButtonBase::Func, this));
    mButLines.push_back(ButtonItem::getNumButton("符号", ButtonBase::keyPunc, ButtonBase::Func, this));
    mButLines.push_back(ButtonItem::getEnglishButton(",", "，", Qt::Key_F, ButtonBase::PinyinPunc, this));
    mButLines.push_back(ButtonItem::getNumButton(" ", Qt::Key_G, ButtonBase::PinyinLetter, this));
    mButLines.push_back(ButtonItem::getEnglishButton(".", "。", Qt::Key_H, ButtonBase::PinyinPunc, this));
    mButLines.push_back(ButtonItem::getSwitchButton());
    mButLines.push_back(ButtonItem::getNumButton("手写", ButtonBase::keyHand, ButtonBase::Func, this));

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
    initConnect();
}

void EnKeyboard::initConnect(){

    for (ButtonBase *but : mButLines) {
        connect(but, &ButtonBase::sendClicked, this, &EnKeyboard::onClicked);
    }
}

void EnKeyboard::onClicked(ButtonBase* but)
{
    if (ButtonItem::getSwitchButton()->getIsEnglish()) {
        if (but->getType() == ButtonBase::PinyinLetter
                || but->getType() == ButtonBase::PinyinNum
                || but->getType() == ButtonBase::PinyinPunc) {
            emit sendCandidateCharacterText(but->text());
            return;
        }

    } else {
        if (but->getType() == ButtonBase::PinyinLetter) {
            return;
        }
    }

    switch (but->getId()) {
    case Qt::Key_Backspace:
        break;
    case Qt::Key_Enter:
        break;
    case ButtonBase::KeyNum:
        break;
    case ButtonBase::keyPunc:
        break;
    case ButtonBase::keyPinyin:
        break;
    }
}
