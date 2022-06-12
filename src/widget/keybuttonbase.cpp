/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "keybuttonbase.h"
#include "globalsignaltransfer.h"
#include <QPainter>
#include <QDebug>

KeyButtonBase::KeyButtonBase(int id, KeyType type, QWidget *parent)
  : QPushButton(parent)
  , ButtonInterface (id, type)

{
    setKeyStyleSheet();
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QPushButton::connect(this, &KeyButtonBase::sendClicked, GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::onKeyButtonClicked);
    QPushButton::connect(SettingManage::getInstance(), &SettingManage::sendThemeChange, this, &KeyButtonBase::onThemeChange);
}

void KeyButtonBase::setText(const QString &str)
{
    mText = str;
    update();
}

QString KeyButtonBase::getText()
{
    return mText;
}

void KeyButtonBase::setKeyStyleSheet()
{
    switch (mType) {
    case KeyButtonBase::Func:
        colors = SettingManage::getInstance()->getSkinColor(SkinType::Func);
        break;
    case KeyButtonBase::Tab:
        colors = SettingManage::getInstance()->getSkinColor(SkinType::Tab);
        break;
    default:
        colors = SettingManage::getInstance()->getSkinColor(SkinType::Key);
    }

    QString button_style = QString("QPushButton{color:%1; background-color:%2;"
                                  "border-radius: 10px;  border: 1px groove gray; border-style: outset;}"
                                  "QPushButton:hover{background-color:%3;} "
                                  "QPushButton:pressed{background-color:%4; border-style: inset;}")
            .arg(colors.font.name())
            .arg(colors.normal.name())
            .arg(colors.hover.name())
            .arg(colors.pressed.name());

    setStyleSheet(button_style);
}

void KeyButtonBase::onClicked()
{
    emit sendClicked(this);
}

void KeyButtonBase::onThemeChange()
{
    setKeyStyleSheet();
}

void KeyButtonBase::mousePressEvent(QMouseEvent *event)
{
    mTimerId = -1;
    if (event->button() == Qt::LeftButton) {
        mPressed = true;
        if (mType != Func || mId == Qt::Key_Enter || mId == Qt::Key_Backspace || mId == Qt::Key_Space) {
            mCount = 0;
            mTimerId = this->startTimer(100);
        }
    }

    QPushButton::mousePressEvent(event);
}

void KeyButtonBase::mouseReleaseEvent(QMouseEvent *event)
{
    if (mTimerId != -1) {
        killTimer(mTimerId);
    }
    if (mPressed && event->button() == Qt::LeftButton && rect().contains(event->pos())) {
        mPressed = false;
        onClicked();
    }
    QPushButton::mouseReleaseEvent(event);
}

void KeyButtonBase::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    if (mCount < 5) {
        mCount++;
        return;
    }
    onClicked();
}

void KeyButtonBase::paintEvent(QPaintEvent *event)
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
//    font.setFamily("楷体"); //字体

    int size = width() < height()? width() : height();
    size /= 3;
    font.setPixelSize(size);
    painter.setFont(font);
    painter.drawText(this->rect(), mText, o);
}
