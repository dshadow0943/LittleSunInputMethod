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
    caseChanged(CustomPushButton::shift);
}

void EnKeyboard::setParent(SoftKeyboard *parent){
    this->parent = parent;

    connect(BtnsTool[6], &CustomPushButton::clicked1, this, [=]()->void{
        parent->switchPage(KEYBOARD_HAND);
    });
    connect(BtnsTool[1], &CustomPushButton::clicked1, this, [=]()->void{
        parent->switchPage(KEYBOARD_NUM);
    });
    connect(BtnsTool[0], &CustomPushButton::clicked1, this, [=]()->void{
        parent->switchPage(KEYBOARD_PUNC);
    });

    connect(this, &EnKeyboard::sendCandidateCharacterText, parent, &SoftKeyboard::addCandidateCharacterText);
    connect(this, &EnKeyboard::a2zkeyClicked, parent, &SoftKeyboard::a2zkeyClicked);
    connect(this, &EnKeyboard::userSelectChinese, parent, &SoftKeyboard::userSelectChinese);
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

    Btns123.push_back(new CustomPushButton(QString::number(0), Qt::Key_0, this));
    Btns123.push_back(new CustomPushButton(QString::number(1), Qt::Key_1, this));
    Btns123.push_back(new CustomPushButton(QString::number(2), Qt::Key_2, this));
    Btns123.push_back(new CustomPushButton(QString::number(3), Qt::Key_3, this));
    Btns123.push_back(new CustomPushButton(QString::number(4), Qt::Key_4, this));
    Btns123.push_back(new CustomPushButton(QString::number(5), Qt::Key_5, this));
    Btns123.push_back(new CustomPushButton(QString::number(6), Qt::Key_6, this));
    Btns123.push_back(new CustomPushButton(QString::number(7), Qt::Key_7, this));
    Btns123.push_back(new CustomPushButton(QString::number(8), Qt::Key_8, this));
    Btns123.push_back(new CustomPushButton(QString::number(9), Qt::Key_9, this));
    //初始化数字按键集合
    for(int i = 0; i < 10; i++){
        //设置按钮属性
        Btns123[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        //将按钮添加到布局中
        gridLayout->addWidget(Btns123[i],0,i*2,1,2);
    }

    BtnsABC1.push_back(new CustomPushButton("Q", Qt::Key_Q, this));
    BtnsABC1.push_back(new CustomPushButton("W", Qt::Key_W, this));
    BtnsABC1.push_back(new CustomPushButton("E", Qt::Key_E, this));
    BtnsABC1.push_back(new CustomPushButton("R", Qt::Key_R, this));
    BtnsABC1.push_back(new CustomPushButton("T", Qt::Key_T, this));
    BtnsABC1.push_back(new CustomPushButton("Y", Qt::Key_Y, this));
    BtnsABC1.push_back(new CustomPushButton("U", Qt::Key_U, this));
    BtnsABC1.push_back(new CustomPushButton("I", Qt::Key_I, this));
    BtnsABC1.push_back(new CustomPushButton("O", Qt::Key_O, this));
    BtnsABC1.push_back(new CustomPushButton("P", Qt::Key_P, this));

    //初始化字母按键第一行
    for(int i = 0; i < 10; i++){
        //设置按钮属性
        BtnsABC1[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        //将按钮添加到布局中
        gridLayout->addWidget(BtnsABC1[i],1,i*2,1,2);
    }

    BtnsABC2.push_back(new CustomPushButton("A", Qt::Key_A, this));
    BtnsABC2.push_back(new CustomPushButton("S", Qt::Key_S, this));
    BtnsABC2.push_back(new CustomPushButton("D", Qt::Key_D, this));
    BtnsABC2.push_back(new CustomPushButton("F", Qt::Key_F, this));
    BtnsABC2.push_back(new CustomPushButton("G", Qt::Key_G, this));
    BtnsABC2.push_back(new CustomPushButton("H", Qt::Key_H, this));
    BtnsABC2.push_back(new CustomPushButton("J", Qt::Key_J, this));
    BtnsABC2.push_back(new CustomPushButton("K", Qt::Key_K, this));
    BtnsABC2.push_back(new CustomPushButton("L", Qt::Key_L, this));

    //初始化字母按键第二行
    for(int i = 0; i < 9; i++){
        //设置按钮属性
        BtnsABC2[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        //将按钮添加到布局中
        gridLayout->addWidget(BtnsABC2[i],2,1+i*2,1,2);

    }

    BtnsABC3.push_back(new CustomPushButton("shift", Qt::Key_Shift, this));
    BtnsABC3.push_back(new CustomPushButton("Z", Qt::Key_Z, this));
    BtnsABC3.push_back(new CustomPushButton("X", Qt::Key_X, this));
    BtnsABC3.push_back(new CustomPushButton("C", Qt::Key_C, this));
    BtnsABC3.push_back(new CustomPushButton("V", Qt::Key_V, this));
    BtnsABC3.push_back(new CustomPushButton("B", Qt::Key_B, this));
    BtnsABC3.push_back(new CustomPushButton("N", Qt::Key_N, this));
    BtnsABC3.push_back(new CustomPushButton("M", Qt::Key_M, this));
    BtnsABC3.push_back(new CustomPushButton("删除", Qt::Key_Backspace, this));
    BtnsABC3.push_back(new CustomPushButton("确认", Qt::Key_Enter, this));

    allShiftChangeKeys.append(BtnsABC2[0]);
    allShiftChangeKeys.append(BtnsABC3[5]);
    allShiftChangeKeys.append(BtnsABC3[3]);
    allShiftChangeKeys.append(BtnsABC2[2]);
    allShiftChangeKeys.append(BtnsABC1[2]);
    allShiftChangeKeys.append(BtnsABC2[3]);
    allShiftChangeKeys.append(BtnsABC2[4]);
    allShiftChangeKeys.append(BtnsABC2[5]);
    allShiftChangeKeys.append(BtnsABC1[7]);
    allShiftChangeKeys.append(BtnsABC2[6]);
    allShiftChangeKeys.append(BtnsABC2[7]);
    allShiftChangeKeys.append(BtnsABC2[8]);
    allShiftChangeKeys.append(BtnsABC3[7]);
    allShiftChangeKeys.append(BtnsABC3[6]);
    allShiftChangeKeys.append(BtnsABC1[8]);
    allShiftChangeKeys.append(BtnsABC1[9]);
    allShiftChangeKeys.append(BtnsABC1[0]);
    allShiftChangeKeys.append(BtnsABC1[3]);
    allShiftChangeKeys.append(BtnsABC2[1]);
    allShiftChangeKeys.append(BtnsABC1[4]);
    allShiftChangeKeys.append(BtnsABC1[6]);
    allShiftChangeKeys.append(BtnsABC3[4]);
    allShiftChangeKeys.append(BtnsABC1[1]);
    allShiftChangeKeys.append(BtnsABC3[2]);
    allShiftChangeKeys.append(BtnsABC1[5]);
    allShiftChangeKeys.append(BtnsABC3[1]);


    //初始化字母按键第三行
    for(int i = 0; i < 10; i++){
        //设置按钮属性
        BtnsABC3[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        gridLayout->addWidget(BtnsABC3[i], 4, i*2, 1, 2);

    }

    BtnsTool.push_back(new CustomPushButton("符号", Qt::Key_Meta, this));
    BtnsTool.push_back(new CustomPushButton("123", Qt::Key_Meta, this));
    BtnsTool.push_back(new CustomPushButton(",", Qt::Key_Comma, this));
    BtnsTool.push_back(new CustomPushButton("space", Qt::Key_Space, this));
    BtnsTool.push_back(new CustomPushButton(".", Qt::Key_Period, this));
    BtnsTool.push_back(new CustomPushButton("", Qt::Key_Menu, this));
    BtnsTool.push_back(new CustomPushButton("手写", Qt::Key_Word, this));

    //初始化第五行
    int row = 0;
    for(int i = 0; i < 7; i++){
        //设置按钮属性
        BtnsTool[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        //将按钮添加到布局中
        if (i == 0 || i == 6){
            gridLayout->addWidget(BtnsTool[i],5,row,1,3);
            row += 3;
        }
        if (i == 1 || i == 2 || i == 4 || i == 5){
            gridLayout->addWidget(BtnsTool[i],5,row,1,2);
            row += 2;
        }
        if (i == 3){
            gridLayout->addWidget(BtnsTool[i],5,row,1,6);
            row += 6;
        }
    }
    //初始化键盘
    caseChanged(CustomPushButton::shift);

    createConnect();

    //设置控件之间的间距
    gridLayout->setSpacing(1);
    //设置栅格布局控件与窗体之间的间距
    gridLayout->setContentsMargins(0,0,0,0);
    this->setLayout(gridLayout);
}

void EnKeyboard::createConnect(){
    for(int i = 0; i < CustomPushButton::allBtns.size(); i++){
        connect(CustomPushButton::allBtns[i], &CustomPushButton::clicked,
                this, &EnKeyboard::keyClicked);
    }
}

/**
 * @brief EN_KeyBoard::keyClicked
 * @param unicode   字符
 * @param key       键
 * 按键点击事件处理方法
 */
void EnKeyboard::keyClicked(int unicode, int key)
{
    if(CustomPushButton::chinese)   //当前中英文切换按钮指向中文时
    {
        switch(key)
        {
        case Qt::Key_Menu:      //中英文切换事件处理
            if (CustomPushButton::shift){       //中文输入时将键盘英文字母改为小写
                CustomPushButton::shift = false;
                caseChanged(CustomPushButton::shift);
            }
            break;
        case Qt::Key_Comma:
            emit sendCandidateCharacterText("，");
            break;
        case Qt::Key_Period:
            emit sendCandidateCharacterText("。");
            break;
        default:            //普通按键处理
            if(Qt::Key_A <= key && key <= Qt::Key_Z)
            {
                emit a2zkeyClicked(unicode, key);
                return;
            }else if(Qt::Key_0 <= key && key <= Qt::Key_9)      //中文输入时数字按键点击事件处理
            {
                //如果候选框为空,代表用户想输入的是数字
                if(hTranslateView->dataStrings.isEmpty()){
                    emit sendCandidateCharacterText(QString(QChar(unicode)));

                }else{
                    //如果候选框不为空,代表用户选择的是下表为index的候选字
                    int index = QString(QChar(key)).toInt()-1;
                    if(hTranslateView->dataStrings.size() > index && index >= 0)
                    {
                        emit userSelectChinese(hTranslateView->dataStrings.at(index),index);
                        return;
                    }
                }

            }

        }
    }else{   //当前中英文切换按钮指向英文时
        switch (key) {
        case Qt::Key_Shift:
            caseChanged(CustomPushButton::shift);
            break;
        case Qt::Key_Menu:
            break;
        case Qt::Key_Comma:
            emit sendCandidateCharacterText(",");
            break;
        case Qt::Key_Period:
            emit sendCandidateCharacterText(".");
            break;
        default:
            if(Qt::Key_A <= key && key <= Qt::Key_Z){
                if(CustomPushButton::shift){
                    emit sendCandidateCharacterText(QString(QChar(unicode)));

                }else{
                    emit sendCandidateCharacterText(QString(QChar(unicode).toLower()));
                }
            }else if(Qt::Key_0 <= key && key <= Qt::Key_9)      //英文输入时数字按键点击事件处理
            {
                emit sendCandidateCharacterText(QString(QChar(unicode)));
            }
            break;
        }
        //qDebug() << QChar(unicode);
    }

    if (parent == nullptr){
        return;
    }
    //由父布局去处理空格、退格和回车事件
    switch(key)
    {
    case Qt::Key_Space:
        parent->spaceSlot();
        break;
    case Qt::Key_Backspace:
        parent->deleteSlot();
        break;
    case Qt::Key_Enter:
        parent->enterSlot();
        break;
    }

}

/**
 * @brief EN_KeyBoard::caseChanged
 * @param ch
 * 更改键盘大小写
 */
void EnKeyboard::caseChanged(bool ch)
{
    for(int i = 0; i < allShiftChangeKeys.size(); ++i)
    {
        if(ch){

        }else{

        }
        allShiftChangeKeys.at(i)->setText(QChar('A'+(ch?0:32)+i));
    }
}


bool EnKeyboard::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == BtnsTool[6]){
        if(e->type() == QEvent::MouseButtonDblClick){
            qDebug() << "拦截双击事件";
            return true;
        }
    }

    return QWidget::eventFilter(obj,e);
}
