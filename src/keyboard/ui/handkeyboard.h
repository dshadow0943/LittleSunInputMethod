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
    void sendPointToCharacter(CharacterEntity);

public slots:
    void onPointToCharacter(CharacterEntity&);

private:
    Ui::HandKeyboard *ui;

private:
    void setRightToolWidget();

};

#endif // MYWIDGET_H
