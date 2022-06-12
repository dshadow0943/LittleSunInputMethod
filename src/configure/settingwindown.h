/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef SETTINGWINDOWN_H
#define SETTINGWINDOWN_H

#include "settingcontenttab.h"
#include "settingcontentview.h"
#include "windowbase.h"

#include <QWidget>

class RadioButtonBase;
class CheckBoxBase;
class SliderBase;
class SettingWindown : public WindowBase
{
    Q_OBJECT
public:
    explicit SettingWindown(int id = 0, QWidget *parent = nullptr);
    ~SettingWindown();
signals:

public slots:
    void onRadioButtonClicked(RadioButtonBase* but);
    void onCheBoxClicked(CheckBoxBase* but);
    void onSliderValueChange(SliderBase* but);

private:
    void initUi();
    void addBasicCard();
    void addKeyboardCard();
    void addHelpCard();
    void addSkinCard();

private:
    SettingContentView *mContentView {nullptr};
    SettingContentTab *mContentTab {nullptr};
};

#endif // SETTINGWINDOWN_H
