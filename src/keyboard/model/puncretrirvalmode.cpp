/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "puncretrirvalmode.h"
#include <QDebug>

PuncRetrirvalMode::PuncRetrirvalMode() : QObject()
{
}

QStringList PuncRetrirvalMode::getPunc(DBOperation::PuncType type)
{
    QStringList datas;
    datas = XYDB->findPunc(type).split(" ");
    return datas;
}

void PuncRetrirvalMode::updatePunc(QString data, DBOperation::PuncType type)
{
    QStringList datas;
    XYDB->updatePunc(data, datas, type);
//    qInfo() << datas;
}
