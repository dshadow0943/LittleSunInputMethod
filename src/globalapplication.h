/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef GLOBALAPPLICATION_H
#define GLOBALAPPLICATION_H

#include <QObject>
#include <QApplication>
#include "mousethread.h"

class GlobalApplication : public QApplication
{
public:
    GlobalApplication(int& argc,char **argv);

    bool notify(QObject*, QEvent *) override;

    MouseThread m;

};

#endif // GLOBALAPPLICATION_H
