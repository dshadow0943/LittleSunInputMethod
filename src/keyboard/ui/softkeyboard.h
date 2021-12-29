#ifndef SOFTKEYBOARD_H
#define SOFTKEYBOARD_H

#include "keyboardsidebar.h"
#include "scrollbarcontainer.h"
#include "dboperation.h"
#include "pinyinretrievalmodel.h"
#include "phraseentity.h"
#include "thesaurusretrieval.h"
#include "scrollbarmanage.h"
#include "windowbase.h"

#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#define KEYBOARD_NUM 0
#define KEYBOARD_EN 1
#define KEYBOARD_HAND 2
#define KEYBOARD_PUNC 3
#define KEYBOARD_CAND 4
#define ARROW_CLOSE 0
#define ARROW_CAND 1
#define ARROW_SHOW 2
#define ARROW_CLEAR 3
#define EN_DEFAULT_WIDTH 1000
#define EN_DEFAULT_HEIGHT 500
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 500

namespace Ui {
class SoftKeyboard;
}

class SoftKeyboard : public WindowBase
{
    Q_OBJECT

public:
    explicit SoftKeyboard(int id = 0, QWidget *parent = nullptr);
    ~SoftKeyboard();

    void setMoveEnabled(bool moveEnabled=true);//设置无边框窗口移动使能

    /* 给子布局的接口 */
    void clearHistory();           //重置候选框
    void onSearchBegin(QStringList data); //根据候选字母映射出候选词

    QLineEdit *textShow;        //文本显示区域

signals:
    //发送字符
    void sendCandidateCharacter(QString character);
    void sendDeleteCharacter();

public slots:
    /* 特殊按键响应槽 */
    void deleteSlot();//删除输入的响应槽
    void enterSlot();//回车被按下的响应槽
    void spaceSlot(); //空格被按下的响应槽
//    void finishSlot();  //完成输入键被点击的响应槽
    void getTextByHand(CharacterEntity character);
    void switchPreviousKey();
    void switchPage(int type = -1);      //切换键盘
    void addCandidateCharacterText(QString character);  //非中文输入时的添加字符到输入框 / 中文输入时将选中的候选框的文字添加到候选框
    void addCandidateLetter(QString letter);
    void userSelectChinese(QString, int);    //拼音输入时点击候选词的处理方法

private slots:
    void on_btn_num_key_clicked();

    void on_btn_en_key_clicked();

    void on_btn_hand_key_clicked();

    void on_btn_punc_key_clicked();

    void arrowClicked();

    void arrowChange();

    void siteClicked();
    void onThemeChange();


protected:
    /* 重写的相关函数 */
    void showEvent(QShowEvent *event) override;         //重写窗口绘制函数

    //通过这三个事件处理函数实现无边框窗口的移动
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::SoftKeyboard *ui;

    QPushButton *keyTypeTab[4];          //更改键盘的控件
//    KeyboardSidebar *mKeyboardSidebar;    //侧边栏

    /* 相关配置参数  */
    int winSizeH = 500;   //键盘顶层布局高度，默认(最大)500
    int winSizeW = 1000;   //键盘顶层布局宽度，默认(最大)1000
    double winScale = 1;    //默认缩放比例
    int previousKey = -1;   //上一次键盘
    QRect applicationRect;      //显示屏相关数据对象
    ThesaurusRetrieval *mThesaurusManage;
    QImage *arrowIcon; //关闭按钮的图像对象
    int    arrowStatus = ARROW_CLOSE;         //记录箭头状态
    bool   arrowPressed = false;     //记录箭头按下状态
    QRect  arrowRect;            //记录箭头按钮的矩形框
    bool   sitePressed = false;  //记录设置按钮按下状态
    QRect  siteRect;            //记录箭头按钮的矩形框


    //无边框窗口移动相关参数
    QPoint mCursorGlobalPos;
    bool mIsMousePress=false;
    bool mIsMoveEnabled;

    QString mAlreadyInputLetters; //用户输入的所有字母
    QStringList mAlreadySelectTranslates; //用户选择的所有中文词组

    VScrollBarView *mVTranslateView;
    HScrollBarView *mHTranslateView;

    QLabel *mLetterLabel;               //输入字母显示控件，同时提供对键盘的移动操作

private:

    /* 控件相关初始化方法 */
    void initView();            //初始化函数
    void initUi();
    void initKeyboard();    //初始化键盘
    void initCandidate();   //初始化候选框
    void initLog();         //初始化log和设置图标

    void fillCandidateText(QStringList&);   //填充候选框文本
    void setThemeStyleSheet();
    void setTabStyleSheet();
};

#endif // SOFTKEYBOARD_H
