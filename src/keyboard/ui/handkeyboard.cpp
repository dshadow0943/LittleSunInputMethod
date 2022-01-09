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

    //设置右侧工具栏
    setRightToolWidget();

    connect(ui->handWritingWidget, &HandView::sendPonit, this, &HandKeyboard::onPointToCharacter);
}

void HandKeyboard::setRightToolWidget()
{
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(ButtonItem::getNumButton("删除", Qt::Key_Backspace, KeyButtonBase::Func, this));
    layout->addWidget(ButtonItem::getNumButton("确认", Qt::Key_Enter, KeyButtonBase::Func, this));
    layout->addWidget(ButtonItem::getNumButton("数字", KeyButtonBase::KeyNum, KeyButtonBase::Func, this));
    layout->addWidget(ButtonItem::getNumButton("符号", KeyButtonBase::keyPunc, KeyButtonBase::Func, this));
    layout->addWidget(ButtonItem::getNumButton("拼音", KeyButtonBase::keyPinyin, KeyButtonBase::Func, this));

    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(4);

    /*将布局设置给右侧工具栏部件*/
    ui->rightToolWidget->setLayout(layout);
}

void HandKeyboard::onPointToCharacter(CharacterEntity& character)
{
    emit sendPointToCharacter(character);
}

HandKeyboard::~HandKeyboard()
{
    delete ui;
}



