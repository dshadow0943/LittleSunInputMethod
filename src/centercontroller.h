#ifndef CENTERCONTROLLER_H
#define CENTERCONTROLLER_H

#include <QWidget>
#include "softkeyboard.h"

namespace Ui {
class CenterController;
}

class CenterController : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.fcitx.littlesun.server")

public:
    explicit CenterController(QWidget *parent = nullptr);
    ~CenterController();



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

    void on_pushButton_clicked();

    void on_btn_dbus_clicked();

private:
    Ui::CenterController *ui;
    SoftKeyboard* softKeyboard;
};

#endif // CENTERCONTROLLER_H
