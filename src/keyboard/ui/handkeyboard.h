#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "softkeyboard.h"
#include "characteritem.h"
#include "buttonitem.h"

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>

namespace Ui {
class HandKeyboard;
}

class HandKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit HandKeyboard(SoftKeyboard *parent);
    ~HandKeyboard();

signals:
    void toEN_keyBoard();

public slots:
    void recognizeChinese(CharacterEntity&);
    void onClicked(KeyButtonBase* but);

private:
    Ui::HandKeyboard *ui;

    SoftKeyboard *parent;
    //右侧工具栏__相关

    QList<KeyButtonBase*> mButs;

private:
        void setRightToolWidget();

};

#endif // MYWIDGET_H
