/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include <QWidget>
#include <QMainWindow>

class WindowBase : public QWidget
{
    Q_OBJECT
public:
    explicit WindowBase(int id = 0, QWidget *parent = nullptr);

signals:
    void sendWindowClosed(int mId);

public slots:

protected:
    void closeEvent(QCloseEvent *event);
    void closeWindow();

private:
    int mId;

};

#endif // WINDOWBASE_H
