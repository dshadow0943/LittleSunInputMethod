#ifndef HANDKEYBOARDTRAIN_H
#define HANDKEYBOARDTRAIN_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include "characterentity.h"
#include "handviewtrain.h"
#include "chinesecharacterserver.h"

class HandKeyboardTrain : public QWidget
{
    Q_OBJECT
public:
    explicit HandKeyboardTrain(QWidget *parent = nullptr);

       void setRightToolWidget();

       //右侧工具栏__相关
       //删除按钮
       QToolButton *btnDel;
       //确认按钮
        QToolButton *btnSure;

       HandViewTrain *keyboard;
       //右侧工具栏布局
       QVBoxLayout *layout;

   private:

       ChineseCharacterServer server;

       void savePoint(CharacterEntity);

   signals:
       void toEN_keyBoard();

   public slots:
       void recognizeChinese(CharacterEntity);
       void enterSlot();

   };

#endif // HANDKEYBOARDTRAIN_H
