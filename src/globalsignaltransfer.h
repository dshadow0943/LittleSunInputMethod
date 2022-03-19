/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef GLOBALSIGNALTRANSFER_H
#define GLOBALSIGNALTRANSFER_H

#include <QObject>

class WindowBase;
class KeyButtonBase;
class RadioButtonBase;
class ScrollBarBase;
class CheckBoxBase;
class SliderBase;
class MouseThread;
class GlobalSignalTransfer : public QObject
{
    Q_OBJECT

public:
    static GlobalSignalTransfer* getInstance();

protected:
    explicit GlobalSignalTransfer(QObject *parent = nullptr);

signals:
    void sendKeyButtonClicked(KeyButtonBase* but);
    void sendRadioButtonClicked(RadioButtonBase* but);
    void sendWindowClosed(int id);
    void sendScrollBarClosed(QString text, int index, int type);
    void sendCheckBoxClicked(CheckBoxBase *but);
    void sendSliderValueChange(SliderBase *but);
    void sendAppQuit();

//限制槽访问权限（避免全局滥用情况）
private slots:
    void onKeyButtonClicked(KeyButtonBase* but);
    void onRadioButtonClicked(RadioButtonBase* but);
    void onWindowClosed(int id);
    void onScrollBarclicked(QString text, int index, int type);
    void onCheckBoxClicked(CheckBoxBase *but);
    void onSliderValueChange(SliderBase *but);
    void onAppQuit();

    friend WindowBase;
    friend KeyButtonBase;
    friend RadioButtonBase;
    friend ScrollBarBase;
    friend CheckBoxBase;
    friend SliderBase;
    friend MouseThread;
};

#endif // GLOBALSIGNALTRANSFER_H
