/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include "englishbutton.h"
#include "numbutton.h"
#include "shiftbutton.h"
#include "ce_switchbutton.h"

#include <QObject>
#include <QList>


class ButtonItem : public QObject
{
    Q_OBJECT
public:
    explicit ButtonItem(QObject *parent = nullptr);

    static EnglishButton* getEnglishButton(QString str1, QString str2, int id = 0, KeyButtonBase::KeyType type = KeyButtonBase::Invalid, QWidget *parent = nullptr);
    static NumButton* getNumButton(QString num, int id = 0, KeyButtonBase::KeyType type = KeyButtonBase::Invalid, QWidget *parent = nullptr);
    static ShiftButton* getShiftButton();
    static CE_SwitchButton* getSwitchButton();

signals:

public slots:

private:
    QList<KeyButtonBase*> mButList;

};

#endif // BUTTONITEM_H
