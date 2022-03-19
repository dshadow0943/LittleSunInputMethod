/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef KEYBOARDSIDEBAR_H
#define KEYBOARDSIDEBAR_H

#include <QWidget>
#include <QPushButton>

class KeyboardSidebar : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardSidebar(QStringList tabs = QStringList(), QWidget *parent = nullptr);

    void setCurrentIndex(int index);
    void setCurrentIndex();
    void setFontSize(int);

signals:
    void sendCurrentIndex(int index);

public slots:
    void onButtonClicked(int);

private:
    void initUi();

private:
    QList<QPushButton*> mButList;
    QStringList mTabs;

    int mCurrentIndex = -1;

};

#endif // KEYBOARDSIDEBAR_H
