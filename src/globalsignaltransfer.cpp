/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "globalsignaltransfer.h"

GlobalSignalTransfer::GlobalSignalTransfer(QObject *parent) : QObject(parent)
{

}

GlobalSignalTransfer* GlobalSignalTransfer::getInstance()
{
    static GlobalSignalTransfer obj;
    return &obj;
}

void GlobalSignalTransfer::onKeyButtonClicked(KeyButtonBase* but)
{
    emit sendKeyButtonClicked(but);
}

void GlobalSignalTransfer::onRadioButtonClicked(RadioButtonBase* but)
{
    emit sendRadioButtonClicked(but);
}

void GlobalSignalTransfer::onWindowClosed(int id)
{
    emit sendWindowClosed(id);
}

void GlobalSignalTransfer::onScrollBarclicked(QString text, int index, int type)
{
    emit sendScrollBarClosed(text, index, type);
}

void GlobalSignalTransfer::onCheckBoxClicked(CheckBoxBase *but)
{
    emit sendCheckBoxClicked(but);
}

void GlobalSignalTransfer::onSliderValueChange(SliderBase *but)
{
    emit sendSliderValueChange(but);
}

void GlobalSignalTransfer::onAppQuit()
{
    emit sendAppQuit();
}
