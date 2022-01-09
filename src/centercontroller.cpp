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
#include "centercontroller.h"
#include "ui_centercontroller.h"
#include "settingmanage.h"
#include "globalsignaltransfer.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>
#include <QApplication>
#include <QKeyEvent>

CenterController::CenterController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterController)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::WindowDoesNotAcceptFocus);

    this->move(SettingManage::getInstance()->getNavigationWindowPos());
    connect(GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::sendWindowClosed,
            this, &CenterController::onWindowClosed);

    //填充log
    QImage Image;
    Image.load(":/icon/littlesun.png");
    QPixmap pixmap = QPixmap::fromImage(Image);
    int with = ui->title->width();
    int height = ui->title->height();
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // 饱满填充
    ui->title->setPixmap(fitpixmap);
}

CenterController::~CenterController()
{
    delete SettingManage::getInstance();
    delete ui;
}

void CenterController::showSoftKeyboard()
{
    if (nullptr == mSoftKeyboard) {
        mSoftKeyboard = new SoftKeyboard(SettingManage::WindowKeyboard);
        connect(mSoftKeyboard, &SoftKeyboard::sendCandidateCharacter, this, &CenterController::candidateCharacterSlots);
        connect(mSoftKeyboard, &SoftKeyboard::sendDeleteCharacter, this, &CenterController::deleteCharacterSlots);
        connect(mSoftKeyboard, &SoftKeyboard::sendSiteClicked, this, &CenterController::on_btn_site_clicked);
    }

    mSoftKeyboard->show();
}

void CenterController::on_btn_key_clicked()
{
    showSoftKeyboard();
}

void CenterController::on_btn_hand_clicked()
{
    if (mHandkeyboatd == nullptr){
        mHandkeyboatd = new HandKeyboardTrain(SettingManage::WindowTrain);
    }
    mHandkeyboatd->show();
}

void CenterController::on_btn_close_clicked()
{
    qApp->quit();
}

/**
 * @brief CenterController::candidateCharacterSlots
 * @param character
 * 向插件发送字符
 */
void CenterController::candidateCharacterSlots(QString character)
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                            "/littlesun",
                            "org.fcitx.Fcitx.LittleSun",
                            "CommitString");
    //发送消息
    message << QString(character);
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    emit sendCandidateCharacter((character));
}

/**
 * @brief CenterController::deleteCharacterSlots
 * 发送退格信号
 */
void CenterController::deleteCharacterSlots()
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                            "/littlesun",
                            "org.fcitx.Fcitx.LittleSun",
                            "DeleteChar");
     //发送消息
     QDBusMessage response = QDBusConnection::sessionBus().call(message);
}

int CenterController::initView()
{
    return 0;
}

int CenterController::showView()
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.fcitx.Fcitx",
                                "/inputmethod",
                                "org.fcitx.Fcitx.InputMethod",
                                "GetCurrentIM");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    this->show();
    showSoftKeyboard();
//    if (response.arguments().first().value<QString>() == "keyboard-littlesun") {
//        this->show();
//        showSoftKeyboard();
//    } else {
//        qDebug() << response.arguments().first().value<QString>();
//        qApp->quit();
//    }
    return 0;
}

int CenterController::hideView()
{
//    this->hide();
    mSoftKeyboard->hide();
//    qApp->quit();
    return 0;
}

/**
 * @brief SoftKeyboard::mousePressEvent
 * @param event
 * 捕捉鼠标按下事件
 * 重写鼠标按下键，获取鼠标左键按下时的全局位置，将窗口的可移动标志设置为true
 */
void CenterController::mousePressEvent(QMouseEvent *event) {
    cursorGlobalPos = event->globalPos();  //获取鼠标按下时的全局位置
    if (event->button() == Qt::LeftButton)//左键按下
    {
        isMousePress = true;
    }
    return QWidget::mousePressEvent(event);
}

/**
 * @brief SoftKeyboard::mouseMoveEventglobalPos()
 * @param event
 * 重写鼠标移动事件，使窗口跟着鼠标移动
 */
void CenterController::mouseMoveEvent(QMouseEvent *event) {

    if (event->buttons() & Qt::LeftButton && isMousePress) {
        window()->move(window()->pos() +  event->globalPos() - cursorGlobalPos);
        cursorGlobalPos = event->globalPos();
        SettingManage::getInstance()->setNavigationWindowPos(cursorGlobalPos);
    }
    return QWidget::mousePressEvent(event);
}

/**
 * @brief SoftKeyboard::mouseReleaseEvent
 * @param event
 * 重写鼠标抬起（释放）事件，将窗口的可移动标志设置为false
 */
void CenterController::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)//左键释放
    {
        isMousePress = false;
    }
    return QWidget::mousePressEvent(event);
}

void CenterController::on_btn_site_clicked()
{
    if (!mSettingWindown) {
        mSettingWindown = new SettingWindown(SettingManage::WindowConfig);
    }
    mSettingWindown->show();
}

void CenterController::onWindowClosed(int id)
{
    switch (id) {
    case SettingManage::WindowKeyboard:
        break;
    case SettingManage::WindowConfig:
        SettingManage::getInstance()->setConfigWindowPos(mSettingWindown->pos());
        break;
    case SettingManage::WindowTrain:
        SettingManage::getInstance()->setTrainWindowPos(mHandkeyboatd->pos());
        break;
    }
}
