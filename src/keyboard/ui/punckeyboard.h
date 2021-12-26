#ifndef PUNCKEYBOARD_H
#define PUNCKEYBOARD_H

#include "softkeyboard.h"
#include "vscrollbarview.h"
#include "scrollbarcontainer.h"
#include "buttonitem.h"
#include "scrollbarmanage.h"
#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QToolButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QEvent>
#include <QLatin1Char>
#include <QStringList>


class PuncKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit PuncKeyboard(SoftKeyboard *parent = nullptr);

public slots:
    void userSelectPunctuation(const QString &text, int index);
    void onClicked(KeyButtonBase* but);

private:
    SoftKeyboard *parent;
    VScrollBarView *punc;

    QStringList loadSymbols(const QString &file);
    void initUi();
    //链接所有按钮的槽函数
    void initConnect();

private:
    int page = 1;
    QGridLayout *gridLayout;

    QList<KeyButtonBase*> mButs;
};

#endif // PUNCKEYBOARD_H
