#include "handkeyboardtrain.h"
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>

HandKeyboardTrain::HandKeyboardTrain(QWidget *parent) : QWidget(parent)
{
    setWindowFlag(Qt::WindowFlags::enum_type::WindowDoesNotAcceptFocus);

    CharacterEntity c;

    QLabel *label = new QLabel();
    keyboard = new HandViewTrain(label);
    label->setStyleSheet("background-color:white;");
    connect(keyboard, &HandViewTrain::charToParent, this, &HandKeyboardTrain::recognizeChinese);

    //设置右侧工具栏
    setRightToolWidget();
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(label);
    hLayout->addLayout(layout);
    keyboard->resize(600, 600);

    this->resize(650, 600);
}

void HandKeyboardTrain::setRightToolWidget()
{
    layout = new QVBoxLayout;
    //删除按钮
    btnDel = new QToolButton();
    btnDel->setText("清空");
    connect(btnDel, &QToolButton::clicked, keyboard, &HandViewTrain::clearPoints);

    //确认按钮
    btnSure = new QToolButton();
    btnSure->setText("保存");
    connect(btnSure, &QToolButton::clicked, this, &HandKeyboardTrain::enterSlot);
    connect(btnSure, &QToolButton::clicked, keyboard, &HandViewTrain::savePoint);




    //设置按钮在布局中大小变化的属性，设置成随着布局的变化变化

    //设置右侧工具栏布局
    layout->addWidget(btnDel,1);
    layout->addWidget(btnSure,1);
    layout->addStretch();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(1);
}

void HandKeyboardTrain::enterSlot(){

}

void HandKeyboardTrain::recognizeChinese(CharacterEntity character)
{
    qDebug() << character.toString();
    savePoint(character);
    keyboard->clearPoints();
}

void HandKeyboardTrain::savePoint(CharacterEntity character)
{
    bool ok = false;
    QString text;
    while(true){
        text = QInputDialog::getText(this, tr("数据保存"),tr("请输入坐标点对应汉字"), QLineEdit::Normal,0, &ok);
        qDebug() << ok;
        if (ok && !text.isEmpty())
        {
            character.word = text;
            if (server.writeFile(character.toString() + "\n")){
                QMessageBox::critical(this,"save File Success",QString::fromUtf8("保存文件成功"));
            } else {
                QMessageBox::critical(this,"save File Failed",QString::fromUtf8("保存文件失败"));
            }
            break;
        }
        if (!ok){
            break;
        }
    }
}
