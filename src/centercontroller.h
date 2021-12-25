#ifndef CENTERCONTROLLER_H
#define CENTERCONTROLLER_H

#include <QWidget>
#include "softkeyboard.h"
#include "handkeyboardtrain.h"
#include "settingwindown.h"

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
    void candidateCharacterSlots(QString character);
    void deleteCharacterSlots();

signals:
    //发送字符
    void sendCandidateCharacter(const QString& character);

private slots:
    void on_btn_key_clicked();

    void on_btn_hand_clicked();

    void on_btn_close_clicked();

    void on_btn_site_clicked();

private:
    Ui::CenterController *ui;
    SoftKeyboard* softKeyboard = nullptr;
    HandKeyboardTrain* handkeyboatd = nullptr;
    SettingWindown *mSettingWindown = nullptr;

    //无边框窗口移动相关参数
    QPoint cursorGlobalPos;
    bool isMousePress=false;
};

#endif // CENTERCONTROLLER_H
