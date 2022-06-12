/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef PUNCRETRIRVALMODE_H
#define PUNCRETRIRVALMODE_H

#include "dboperation.h"
#include <QObject>

class PuncKeyboard;
class PuncRetrirvalMode : public QObject
{
    Q_OBJECT
public:
    PuncRetrirvalMode();

    QStringList getPunc(DBOperation::PuncType);
    void updatePunc(QString data, DBOperation::PuncType type);

signals:

public slots:


};

#endif // PUNCRETRIRVALMODE_H
