#include "numkeyboard.h"

NumKeyboard::NumKeyboard(SoftKeyboard *parent) : QWidget(parent)
{
    this->parent = parent;

    //创建栅格布局
    gridLayout = new QGridLayout;
    initKeyboard();

//    setStyleSheet("QToolButton{background-color: rgb(255, 255, 255);}"
//                     "QToolButton:hover{background-color: rgb(190, 190, 190); font-weight: 30px;}"
//                     "QToolButton:press{background-color: rgb(190, 190, 190); font-weight: 30px;}");
    //设置控件之间的间距
    gridLayout->setSpacing(1);
    //设置栅格布局控件与窗体之间的间距
    gridLayout->setContentsMargins(0,0,0,0);
    this->setLayout(gridLayout);
}

/**
 * @brief num_keyboard::initKeyboard
 * 初始化键盘
 */
void NumKeyboard::initKeyboard()
{
    initKeyValue();
    int line = 0;
    int count = 0;
    for(int i = 0; i < 5; i++){
        if(i == 0 || i == 4){
            gridLayout->addWidget(BtnsLine1[i], line, count, 1, 2);
            count+=2;
        }else{
            gridLayout->addWidget(BtnsLine1[i], line, count, 1, 3);
            count+=3;
        }
    }
    line++;
    count = 0;
    for(int i = 0; i < 5; i++){
        if(i == 0 || i == 4){
            gridLayout->addWidget(BtnsLine2[i], line, count, 1, 2);
            count+=2;
        }else{
            gridLayout->addWidget(BtnsLine2[i], line, count, 1, 3);
            count+=3;
        }
    }
    line++;
    count = 0;
    for(int i = 0; i < 5; i++){
        if(i == 0 || i == 4){
            gridLayout->addWidget(BtnsLine3[i], line, count, 1, 2);
            count+=2;
        }else{
            gridLayout->addWidget(BtnsLine3[i], line, count, 1, 3);
            count+=3;
        }
    }
    line++;
    count = 0;
    for(int i = 0; i < 5; i++){
        if(i == 0 || i == 4){
            gridLayout->addWidget(BtnsLine4[i], line, count, 1, 2);
            count+=2;
        }else{
            gridLayout->addWidget(BtnsLine4[i], line, count, 1, 3);
            count+=3;
        }
    }


}

/**
 * @brief num_keyboard::initKeyValue
 * 初始化按键
 */
void NumKeyboard::initKeyValue()
{
    QList<QString> values = {",", "1", "2", "3", ".", "4", "5", "6", "*", "@", "7", "8", "9", "#", "0"};
    //初始化第一行
    BtnsLine1.push_back(new CustomPushButton("*",Qt::Key_Asterisk,0, this));
//    BtnsLine1.push_back(new CustomPushButton(",",Qt::Key_Comma, 0, this));
    BtnsLine1.push_back(new CustomPushButton("1", Qt::Key_1, 0, this));
    BtnsLine1.push_back(new CustomPushButton("2", Qt::Key_2, 0, this));
    BtnsLine1.push_back(new CustomPushButton("3", Qt::Key_3, 0, this));
    BtnsLine1.push_back(new CustomPushButton("删除", Qt::Key_Backspace, 0, this));

    //初始化第二行
    BtnsLine2.push_back(new CustomPushButton("#",Qt::Key_Context2,0, this));
//    BtnsLine2.push_back(new CustomPushButton(".",Qt::Key_Period,0, this));
    BtnsLine2.push_back(new CustomPushButton("4",Qt::Key_4,0, this));
    BtnsLine2.push_back(new CustomPushButton("5",Qt::Key_5,0, this));
    BtnsLine2.push_back(new CustomPushButton("6",Qt::Key_6,0, this));
//    BtnsLine2.push_back(new CustomPushButton("*",Qt::Key_Asterisk,0, this));
    BtnsLine2.push_back(new CustomPushButton(",",Qt::Key_Comma, 0, this));

    //初始化第三行
    BtnsLine3.push_back(new CustomPushButton("@",Qt::Key_Context1,0, this));
    BtnsLine3.push_back(new CustomPushButton("7",Qt::Key_7,0, this));
    BtnsLine3.push_back(new CustomPushButton("8",Qt::Key_8,0, this));
    BtnsLine3.push_back(new CustomPushButton("9",Qt::Key_9,0, this));
//    BtnsLine3.push_back(new CustomPushButton("#",Qt::Key_Context2,0, this));
    BtnsLine3.push_back(new CustomPushButton(".",Qt::Key_Period,0, this));

    //初始化第四行
    BtnsLine4.push_back(new CustomPushButton("符号",Qt::Key_Meta,0, this));
    BtnsLine4.push_back(new CustomPushButton("abc",Qt::Key_Meta,0, this));
    BtnsLine4.push_back(new CustomPushButton("0",Qt::Key_0,0, this));
    BtnsLine4.push_back(new CustomPushButton("空格",Qt::Key_Space,0, this));
    BtnsLine4.push_back(new CustomPushButton("手写",Qt::Key_Word,0, this));


    connect(BtnsLine4[0], &CustomPushButton::clicked1, this, [=]()->void{
        parent->switchPage(KEYBOARD_PUNC);
    });
    connect(BtnsLine4[1], &CustomPushButton::clicked1, this, [=]()->void{
        parent->switchPage(KEYBOARD_EN);
    });
    //点击手写跳转到手写页面
    connect(BtnsLine4[4], &CustomPushButton::clicked1, this, [=]()->void{
        parent->switchPage(KEYBOARD_HAND);
    });

    createConnect();

}

void NumKeyboard::createConnect()
{
    if(CustomPushButton::allNumBtns.size() != 0){
        for(int i = 0; i < CustomPushButton::allNumBtns.size(); i++){
            connect(CustomPushButton::allNumBtns[i], &CustomPushButton::clicked,
                    this, &NumKeyboard::keyClicked);
        }
    }else{
        qDebug() << "数字键盘按钮个数为0";
    }

}

void NumKeyboard::keyClicked(int unicode, int key)
{
    switch(key)
    {
    case Qt::Key_Space:
        parent->spaceSlot();
        break;
    case Qt::Key_Backspace:
        parent->deleteSlot();
        break;
    case Qt::Key_Word://跳转到手写键盘
        break;
    case Qt::Key_Meta: //跳转到abc/符号键盘
        break;
    case Qt::Key_Comma://,符号
        break;

    case Qt::Key_Period://.符号
        break;

    case Qt::Key_Context1://@符号
        break;

    case Qt::Key_Context2://#符号
        break;
    default:
        if(Qt::Key_0 <= key && key <= Qt::Key_9)
            parent->addCandidateCharacterText(QString(QChar(unicode)));
        break;
    }
}
