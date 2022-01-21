/*
* Copyright (C) 2019 ~ 2019 UnionTech Software Technology Co.,Ltd.
*
* Author:     leilong <dshadow@foxmail.com>
*
* Maintainer: leilong <dshadow@foxmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CENTERCONTROLLER_H
#define CENTERCONTROLLER_H

#include "softkeyboard.h"
#include "handkeyboardtrain.h"
#include "settingwindown.h"
#include <QWidget>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

namespace Ui {
class CenterController;
}

class CenterController : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.fcitx.littlesun.server")

public:
    explicit CenterController(QWidget *parent = nullptr);
    bool getInputState();
    ~CenterController()  override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    int initView();
    int showView();
    int hideView();
    void onCandidateCharacter(QString character);
    void onDeleteCharacter();
    void onWindowClosed(int id);
    void onQuit();
    void onTrayClicked(QSystemTrayIcon::ActivationReason reason);

signals:
    //发送字符
    void sendCandidateCharacter(const QString& character);

private slots:
    void on_btn_key_clicked();
    void on_btn_hand_clicked();
    void on_btn_close_clicked();
    void on_btn_site_clicked();

private:
    void showSoftKeyboard();
    void initDbus();
    void initTray();

private:
    Ui::CenterController *ui;
    SoftKeyboard* mSoftKeyboard = nullptr;
    HandKeyboardTrain* mHandkeyboatd = nullptr;
    SettingWindown *mSettingWindown = nullptr;

    QMenu *mTrayMenu;//托盘菜单
    QSystemTrayIcon *mTray;//托盘图标

    //无边框窗口移动相关参数
    QPoint cursorGlobalPos;
    bool isMousePress=false;
    int mFlag = 0;
};

#endif // CENTERCONTROLLER_H
