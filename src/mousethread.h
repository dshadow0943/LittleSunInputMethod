/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef MOUSETHREAD_H
#define MOUSETHREAD_H

#include <QThread>

class MouseThread : public QThread
{
public:
    MouseThread();
    ~MouseThread() override {
        // 请求终止
        quit();
        wait();
    }

protected:
    void run() override;
};

#endif // MOUSETHREAD_H
