#include "punckeyboard.h"
#include <QColorDialog>
#include <QFontDialog>
#include <QGridLayout>
#include <QFile>
#include <QHBoxLayout>

/**
 * @brief PuncKeyboard::PuncKeyboard
 * @param parent
 * 符号键盘
 */
PuncKeyboard::PuncKeyboard(SoftKeyboard *parent) : QWidget(parent)
{
    this->parent = parent;

    punctuations->dataStrings = loadSymbols(":/symbol.txt");
    punctuations->setUnitMinHeight(40);
    punctuations->setUnitMinWidth(50);
    customViw = new CustomWidget(this);
    customViw->init(punctuations,CustomWidget::VERTICAL1);
    customViw->setMouseSensitivity(5);


    setRightToolWidget();
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(customViw, 5);
    QWidget *w = new QWidget;
    w->setLayout(layout);
    hLayout->addWidget(w, 1);
    layout->setSpacing(4);
    hLayout->setMargin(0);
    hLayout->setSpacing(0);

    connect(punctuations, &VTranslateView::clicked, this, &PuncKeyboard::userSelectPunctuation);
}

void PuncKeyboard::userSelectPunctuation(const QString &text, int index)
{
    parent->addCandidateCharacterText(text);
}

/**
 * @brief PunctuationsView::setRightToolWidget
 * 设置右工具栏
 */
void PuncKeyboard::setRightToolWidget()
{
    layout = new QVBoxLayout;
    //删除按钮
    btnDel = new CustomPushButton("删除", Qt::Key_Backspace, this);
    connect(btnDel, &CustomPushButton::clicked1, parent, &SoftKeyboard::deleteSlot);

    //确认按钮
    btnSure = new CustomPushButton(" ",0,this);

    //abc按钮
    btnabc = new CustomPushButton(" ",0,this);

    //123按钮
    btn123 = new CustomPushButton(" ",0,this);

    //上一页
    btnLast = new CustomPushButton(" ",0,this);

    //下一页
    btnBack = new CustomPushButton("返回",Qt::Key_Back, this);
    connect(btnBack, &CustomPushButton::clicked1, parent, &SoftKeyboard::switchPreviousKey);
    connect(btnBack, &CustomPushButton::clicked1, parent, [=]()->void{
        qDebug() << "back:  ";
    });

//    设置按钮在布局中大小变化的属性，设置成随着布局的变化变化
    btnDel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btnSure->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btnabc->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btn123->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btnLast->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    btnBack->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    //设置右侧工具栏布局
    layout->addWidget(btnDel,1);
    layout->addWidget(btnSure,1);
    layout->addWidget(btnabc,1);
    layout->addWidget(btn123,1);
    layout->addWidget(btnLast,1);
    layout->addWidget(btnBack,1);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(1);

    /*将布局设置给右侧工具栏部件*/
//    ui->rightTool->setLayout(layout);
}

QStringList PuncKeyboard::loadSymbols(const QString &file)
{
    QFile symbol_file(file);
    QStringList symbols;
    if (symbol_file.open(QIODevice::ReadOnly))
    {
        QString lineSymbols;
        while (!symbol_file.atEnd())
        {
            lineSymbols = QString::fromUtf8(symbol_file.readLine());
            lineSymbols = lineSymbols.trimmed();
            for (int i = 0; i < lineSymbols.size(); ++i)
            {
                symbols.append(lineSymbols.at(i));
            }
        }
        symbol_file.close();
    }

    return symbols;
}

