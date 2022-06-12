/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef SHIFTBUTTON_H
#define SHIFTBUTTON_H

#include <keybuttonbase.h>

class ShiftButton : public KeyButtonBase
{
    Q_OBJECT
public:
    explicit ShiftButton(QString text = "⇧", int id = Qt::Key_Shift, KeyButtonBase::KeyType type = KeyButtonBase::Func, QWidget *parent = nullptr);

signals:
    void sendShiftClicked(bool mIsCaps);

public slots:

    void onEnglishInput(bool isEnglish);

protected:
    void onClicked() override;
    void paintEvent(QPaintEvent *event) override;

private:
    bool mIsCaps = false;
    bool mIsCapsLook = false;
};

#endif // SHIFTBUTTON_H
