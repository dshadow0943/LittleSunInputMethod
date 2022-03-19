/*
*
* Author:     leilong <dshadow@foxmail.com>
*
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
    int showView(bool force = false);
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
