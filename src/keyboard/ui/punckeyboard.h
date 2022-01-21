#ifndef PUNCKEYBOARD_H
#define PUNCKEYBOARD_H

#include "softkeyboard.h"
#include "vscrollbarview.h"
#include "scrollbarcontainer.h"
#include "buttonitem.h"
#include "scrollbarmanage.h"
#include <QWidget>
#include <QList>
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
    void onTabClicked(int);

protected:
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    VScrollBarView *mPunc;
    void initUi();
    void setPuncData(QStringList);

private:
    QList<KeyButtonBase*> mButs;
    KeyboardSidebar *mTabSider = nullptr;
};

#endif // PUNCKEYBOARD_H
