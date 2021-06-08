#include "handkeyboard.h"
#include "ui_handkeyboard.h"
#include "handview.h"

#include <QColorDialog>
#include <QFontDialog>


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
    layout = new QVBoxLayout;
    //删除按钮
    btnDel = new CustomPushButton("删除",Qt::Key_Backspace, 2, this);
    connect(btnDel, &CustomPushButton::clicked1, parent, &SoftKeyboard::deleteSlot);

    //确认按钮
    btnSure = new CustomPushButton("确认",Qt::Key_Enter, 2, this);
    connect(btnSure, &CustomPushButton::clicked1, parent, &SoftKeyboard::enterSlot);

    //abc按钮
    btnabc = new CustomPushButton("A&8", Qt::Key_WWW, 2, this);
    connect(btnabc, &CustomPushButton::clicked1, this, [=]()->void{
        CustomPushButton::abc123 = !CustomPushButton::abc123;
    });

    //字符按钮
    btnChar = new CustomPushButton("&?", Qt::Key_Meta, 2, this);
    connect(btnChar, &CustomPushButton::clicked, parent, [=]()->void{
        parent->switchPage(KEYBOARD_PUNC);
    });

    //键盘按钮
    btnKeyBoard = new CustomPushButton("键盘",Qt::Key_Meta, 2, this);
    connect(btnKeyBoard, &CustomPushButton::clicked1, parent, [=]()->void{
        parent->switchPage(KEYBOARD_EN);
    });



    //设置右侧边框栏的所有按钮的样式
//    setStyleSheet("QToolButton{background-color: rgb(220, 220, 220);}"
//                     "QToolButton:hover{background-color: rgb(170, 170, 170); font-weight: 30px;}"
//                     "QToolButton:press{background-color: rgb(170, 170, 170); font-weight: 30px;}");



    //设置按钮在布局中大小变化的属性，设置成随着布局的变化变化
    btnDel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btnSure->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btnabc->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btnChar->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btnKeyBoard->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    //设置右侧工具栏布局
    layout->addWidget(btnDel,1);
    layout->addWidget(btnSure,1);
    layout->addWidget(btnabc,1);
    layout->addWidget(btnChar,1);
    layout->addWidget(btnKeyBoard,1);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(1);

    /*将布局设置给右侧工具栏部件*/
    ui->rightToolWidget->setLayout(layout);
    for(int i = 0; i < CustomPushButton::allHandBtns.size(); i++){
        connect(CustomPushButton::allHandBtns[i], &CustomPushButton::clicked, this, &HandKeyboard::KeyClicked);
    }
}

void HandKeyboard::KeyClicked(int unicode, int key)
{
    switch(key)
    {
    case Qt::Key_Backspace:
        parent->deleteSlot();
        break;
    case Qt::Key_Enter:
        parent->enterSlot();
        break;
    }
}

void HandKeyboard::recognizeChinese(CharacterEntity character)
{
    if (parent == nullptr){
        qDebug() << "null";
        return;
    }
    character.isNum = CustomPushButton::abc123;
    parent->getTextByHand(character);
}

HandKeyboard::~HandKeyboard()
{
    free(parent);
    delete ui;
}



