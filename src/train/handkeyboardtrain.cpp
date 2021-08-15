#include "handkeyboardtrain.h"
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>

HandKeyboardTrain::HandKeyboardTrain(QWidget *parent) : QWidget(parent)
{
    setWindowFlag(Qt::WindowFlags::enum_type::WindowDoesNotAcceptFocus);

    server.init();
    CharacterEntity c;

    keyboard = new HandViewTrain(this);
    keyboard->setStyleSheet("background-color:white;");
    connect(keyboard, &HandViewTrain::charToParent, this, &HandKeyboardTrain::recognizeChinese);

    //设置右侧工具栏
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QWidget *w = new QWidget();
    layout = new QVBoxLayout(w);

    hLayout->addWidget(keyboard, 1);
    hLayout->addWidget(w);
    w->setMinimumWidth(80);
    this->resize(700, 600);
    setRightToolWidget();

}

void HandKeyboardTrain::setRightToolWidget()
{
    //删除按钮
    btnDel = new QToolButton();
    btnDel->setText("清空");
    btnDel->setMinimumSize(QSize(80, 80));
    connect(btnDel, &QToolButton::clicked, keyboard, &HandViewTrain::clearPoints);

    //确认按钮
    btnSure = new QToolButton();
    btnSure->setText("确认");
    btnSure->setMinimumSize(QSize(80, 80));
    connect(btnSure, &QToolButton::clicked, keyboard, &HandViewTrain::enterSolt);

    btnSave = new QToolButton();
    btnSave->setText("保存");
    btnSave->setMinimumSize(QSize(80, 80));
    connect(btnSave, &QToolButton::clicked, this, &HandKeyboardTrain::saveSolt);

    btnReset = new QToolButton();
    btnReset->setText("重置");
    btnReset->setMinimumSize(QSize(80, 80));
    connect(btnReset, &QToolButton::clicked, this, &HandKeyboardTrain::resetSolt);

    //设置按钮在布局中大小变化的属性，设置成随着布局的变化变化

    //设置右侧工具栏布局
    layout->addWidget(btnDel,1);
    layout->addWidget(btnSure,1);
    layout->addWidget(btnSave, 1);
    layout->addWidget(btnReset, 1);
    layout->addStretch();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(10);
}

void HandKeyboardTrain::recognizeChinese(CharacterEntity character)
{
    enterPoint(character);
    keyboard->clearPoints();
}

void HandKeyboardTrain::enterPoint(CharacterEntity character)
{
    bool ok = false;
    QString text;
    while(true){
        text = QInputDialog::getText(this, tr("数据保存"),tr("请输入坐标点对应汉字"), QLineEdit::Normal, nullptr, &ok);
        if (ok && !text.isEmpty())
        {
            character.word = text;
            characters.push_back(character);
            server.writeFile(character.toString() + "\n");
        }
        if (!ok){
            break;
        }
    }
}

void HandKeyboardTrain::saveSolt()
{
    int count = server.saveCharaters(characters);
    QMessageBox::critical(this,"save File Success",QString("成功添加%1个到字库").arg(count));
    characters.clear();
}

void HandKeyboardTrain::resetSolt()
{
    if (QMessageBox::warning(nullptr, "重置", QString("确定重置字库吗？这将失去自己你训练的所有字库"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        if (server.deleteFont()) {
            QMessageBox::critical(this,"重置",QString("重置成功，原文件可在~/.littlesun文件夹中寻找"));
        }
    }

}
