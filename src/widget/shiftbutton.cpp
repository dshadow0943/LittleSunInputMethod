/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "shiftbutton.h"
#include <QPainter>

ShiftButton::ShiftButton(QString text, int id, KeyButtonBase::KeyType type, QWidget *parent) : KeyButtonBase (id, type, parent)
{
    setText(text);
}

void ShiftButton::onClicked()
{
    KeyButtonBase::onClicked();
    if (mIsCapsLook) {
        return;
    }
    mIsCaps = !mIsCaps;
    emit sendShiftClicked(mIsCaps);
    update();
}

void ShiftButton::onEnglishInput(bool isEnglish)
{
    if (isEnglish  == mIsCaps) {
        onClicked();
    }
    mIsCapsLook = !isEnglish;
}

void ShiftButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    if(mText.isEmpty()) {
        return;
    }
    QTextOption o;
    o.setWrapMode(QTextOption::WrapAnywhere);
    o.setAlignment(Qt::AlignCenter);

    QPainter painter(this);
    QFont font = painter.font();

    int size = width() < height()? width() : height();
    size /= 3;
    if (mIsCaps) {
        size += 4;
        QPen pen = painter.pen();
        pen.setColor(Qt::red);
        painter.setPen(pen);
    }
    font.setPixelSize(size);
    painter.setFont(font);
    painter.drawText(this->rect(), mText, o);
}
