#include "softkeyboard.h"
#include "ui_softkeyboard.h"
#include "handkeyboard.h"
#include "htranslateview.h"
#include "customskin.h"
#include <QLabel>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QFont>
#include <QApplication>
#include <QDesktopWidget>

SoftKeyboard::SoftKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoftKeyboard)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::WindowDoesNotAcceptFocus);
    chineseServer.init();
    initView();
    initCandidate();

    arrowIcon = new QImage;

    arrowChange();

    ui->site->setPixmap(QPixmap(":/icon/site.svg"));  //加载设置图标
}

SoftKeyboard::~SoftKeyboard()
{
    delete ui;
}

/**
 * @brief SoftKeyboard::init
 * 窗口初始化函数
 */
void SoftKeyboard::initView(){

    applicationRect = QGuiApplication::screens().at(0)->geometry();     //获取显示屏像素

    int w = applicationRect.width()*0.6;            //显示屏的宽
    int h = applicationRect.height()*0.5;           //显示屏的高

    if (w < winSizeW){
        winSizeW = w;               //根据显示屏大小设置顶层窗口的默认大小
    }
    winSizeW = winSizeW > h? h : winSizeW;

    winSizeH = winSizeW * 0.5;       //设置顶层窗口的默认高度

    winScale = winSizeW*1.0/900;    //根据界面大小等比例变换窗口大小

}

/**
 * @brief SoftKeyboard::initCandidate
 * 初始化候选框相关控件
 */
void SoftKeyboard::initCandidate()
{
    //初始化水平候选词拖拽控件
    translateHDragableWidget = ui->word_box;
    translateHDragableWidget->init(hTranslateView, CustomWidget::HORIZONTAL1);
    translateHDragableWidget->setMouseSensitivity(5);

    //初始化垂直候选词拖拽控件
    translateVDragableWidget = ui->page_cand;
    translateVDragableWidget->init(vTranslateView,CustomWidget::VERTICAL1);
    translateVDragableWidget->setMouseSensitivity(5);

    letterLabel = ui->candidate;
    QFont font = letterLabel->font();
    font.setUnderline(true);
    letterLabel->setFont(font);

    connect(hTranslateView, &CustomCharView::clicked, this, &SoftKeyboard::userSelectChinese);
    connect(vTranslateView, &CustomCharView::clicked, this, &SoftKeyboard::userSelectChinese);

}

/**
 * @brief SoftKeyboard::initKeyType
 * 初始化键盘相关控件
 */
void SoftKeyboard::initKeyboard()
{

}

/**
 * @brief SoftKeyboard::arrowClicked
 * 右上角箭头按钮按下事件
 */
void SoftKeyboard::arrowClicked()
{
    qDebug() << "arrowStatus: " << arrowStatus;
    switch(arrowStatus) {
        case ARROW_CLOSE:
             hide();   //只隐藏不退出
        break;
        case ARROW_CAND: switchPreviousKey();
        break;
        case ARROW_SHOW: switchPage(KEYBOARD_CAND);
        break;
    }


}

void SoftKeyboard::arrowChange()
{

    if (hTranslateView->dataStrings.isEmpty()){

        arrowIcon->load(":/icon/arrow_b.svg");
        arrowStatus = ARROW_CLOSE;
    } else if (ui->key_page->currentIndex() == KEYBOARD_CAND){
        arrowIcon->load(":/icon/arrow_b.svg");
        arrowStatus = ARROW_CAND;
    } else {
        arrowIcon->load(":/icon/arrow_r.svg");
        arrowStatus = ARROW_SHOW;
    }
    ui->close->setPixmap(QPixmap::fromImage(*arrowIcon));  //加载图标
}

/**
 * @brief SoftKeyboard::siteClicked
 * 设置按钮按下事件
 */
void SoftKeyboard::siteClicked()
{

}

/**
 * @brief SoftKeyboard::showEvent
 * @param event
 * 重写showEvent函数
 */
void SoftKeyboard::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    switchPage(KEYBOARD_EN);
    this->move((applicationRect.width()-width())/2, applicationRect.height()-height());       //移动窗口位置,默认出现在底端中部

    setMoveEnabled();
}

/**
 * @brief SoftKeyboard::switchPage
 * @param type 需要切换的布局
 * 切换布局，更新窗口大小
 *
 */
void SoftKeyboard::switchPage(int type)
{
    //如需要切换的键盘和当前显示的键盘是同一个则直接不做处理，放置多次重复点击
    if (ui->key_page->currentIndex() == type){
        return;
    }

    int w, h;

    switch (type) {
        case KEYBOARD_NUM:
        case KEYBOARD_HAND:
        case KEYBOARD_PUNC:
            w = 800 * winScale;
            h = 500 * winScale;

            break;
        case KEYBOARD_EN:
            w = 1000 * winScale;
            h = 500 * winScale;
        break;
        case KEYBOARD_CAND:
            vTranslateView->dataStrings = hTranslateView->dataStrings;
            vTranslateView->update();
            break;
        default:
            return;
    }

    //切换键盘是将手写界面初始化为汉字识别
    CustomPushButton::abc123 = false;

    previousKey = ui->key_page->currentIndex();
//    for (int i = 0; i < 4; i++) {
//         keyTypeTab[i]->setStyleSheet("background-color:transparent;");
//    }
//    if (type < 4){
//        keyTypeTab[type]->setStyleSheet("background-color:white;");
//    }
    ui->key_page->setCurrentIndex(type);        //更新QStackedWidget栈布局内容
    arrowChange();

    //查看更多候选词时不用重新调节界面大小
    if (type != KEYBOARD_CAND){
        this->resize(w, h);    //更新窗口大小
    }

}

/**
 * @brief SoftKeyboard::fillCandidateText
 * @param strList 待填充的文本列表
 * 填充候选框文本(手写)
 */
void SoftKeyboard::fillCandidateText(QStringList strList){

    hTranslateView->dataStrings.clear();        //清空候选词
    hTranslateView->dataStrings.append(strList);    //填充候选词
    hTranslateView->update();
    arrowChange();  //更改箭头状态
}

/**
 * @brief addCandidateCharacterText
 * @param character
 * 将字符添加到输出框中
 */
void SoftKeyboard::addCandidateCharacterText(QString character)
{
    emit sendCandidateCharacter(character);
}

/**
 * @brief SoftKeyboard::clear_history
 * 重置候选框数据
 */
void SoftKeyboard::clearHistory()
{
    letterLabel->clear();
    alreadyInputLetters.clear();
    alreadySelectTranslates.clear();
    vTranslateView->dataStrings.clear();
    vTranslateView->update();
    hTranslateView->dataStrings.clear();
    hTranslateView->update();
    XYInputSearchInterface::getInstance()->resetSearch();
}

/**
 * @brief SoftKeyboard::search_begin
 * @param lists
 * 根据候选字母映射出候选词填充到候选框(拼音)
 */
void SoftKeyboard::searchBegin(QList<XYTranslateItem *> lists)
{
    hTranslateView->dataStrings.clear();
    foreach (XYTranslateItem *temp, lists) {
        hTranslateView->dataStrings.append(temp->msTranslate);
    }
    letterLabel->setText(XYInputSearchInterface::getInstance()->getCurLetters());
    hTranslateView->update();
    arrowChange();  //更改箭头状态
}

/**
 * @brief SoftKeyboard::userSelectChinese
 * @param text
 * @param index
 * 拼音输入时点击候选词的处理方法
 */
void SoftKeyboard::userSelectChinese(const QString &text, int index)
{
    QString showText;
    QList<XYTranslateItem *> lists = XYInputSearchInterface::getInstance()->completeInput(text, index, showText);
    letterLabel->setText(showText);

    if(lists.isEmpty()){        //点击候选词后无剩余候选字母
        //这里完成输入
        addCandidateCharacterText(alreadySelectTranslates.join("").append(text));  //将数据发送出去
        clearHistory();        //清空数据
        //如果是查看更多候选词界面则模拟点击箭头返回到原来界面
        if (ui->key_page->currentIndex() == KEYBOARD_CAND){
            arrowClicked();
        }
    }
    else    //如果还剩候选字母则留着等着再次处理globalPos()
    {
        alreadySelectTranslates.append(text);
        hTranslateView->dataStrings.clear();
        foreach(XYTranslateItem *temp, lists){
            hTranslateView->dataStrings.append(temp->msTranslate);
        }
        hTranslateView->move(0,0);
        hTranslateView->update();
        if(ui->key_page->currentIndex() == 4){
            hTranslateView->dataStrings = hTranslateView->dataStrings;
            hTranslateView->move(0,0);
            hTranslateView->update();
        }
    }
}

/**
 * @brief SoftKeyboard::a2zkeyClicked
 * @param unicode
 * @param key
 * @return
 * 添加候选字母
 */
bool SoftKeyboard::a2zkeyClicked(int unicode, int key)
{
    alreadyInputLetters.append(QChar(unicode).toLower());

    searchBegin(XYInputSearchInterface::getInstance()->searchTranslates(alreadyInputLetters));
    return true;
}

/* 重写事件 */

/**
 * @brief SoftKeyboard::setMoveEnabled
 * @param moveEnabled
 * 设置是否可拖动
 */
void SoftKeyboard::setMoveEnabled(bool moveEnabled) {
    isMoveEnabled = moveEnabled;
}

void SoftKeyboard::getTextByHand(CharacterEntity character)
{
    QStringList strs = chineseServer.getChineseByHand(character, 20);
    fillCandidateText(strs);
}

void SoftKeyboard::switchPreviousKey()
{
    switchPage(previousKey);
}

/**
 * @brief SoftKeyboard::mousePressEvent
 * @param event
 * 捕捉鼠标按下事件
 * 重写鼠标按下键，获取鼠标左键按下时的全局位置，将窗口的可移动标志设置为true
 */
void SoftKeyboard::mousePressEvent(QMouseEvent *event) {
    cursorGlobalPos = event->globalPos();  //获取鼠标按下时的全局位置
    if (event->button() == Qt::LeftButton && ui->title->geometry().contains(event->pos()))//左键按下
    {
        isMousePress = true;
    }

    arrowRect = QRect(ui->close->mapTo(this, QPoint(0, 0)), ui->close->size());
    if(event->button() == Qt::LeftButton && arrowRect.contains(event->pos()))
    {
        arrowPressed = true;
    }

    siteRect = QRect(ui->site->mapTo(this, QPoint(0, 0)), ui->site->size());
    if(event->button() == Qt::LeftButton && siteRect.contains(event->pos()))
    {
        sitePressed = true;
    }
    event->ignore();
}

/**
 * @brief SoftKeyboard::mouseMoveEventglobalPos()
 * @param event
 * 重写鼠标移动事件，使窗口跟着鼠标移动
 */
void SoftKeyboard::mouseMoveEvent(QMouseEvent *event) {

    if (event->buttons() & Qt::LeftButton && isMousePress && isMoveEnabled) {
        window()->move(window()->pos() +  event->globalPos() - cursorGlobalPos);
        cursorGlobalPos = event->globalPos();
    }
    event->ignore();
}

/**
 * @brief SoftKeyboard::mouseReleaseEvent
 * @param event
 * 重写鼠标抬起（释放）事件，将窗口的可移动标志设置为false
 */
void SoftKeyboard::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)//左键释放
    {
        isMousePress = false;
        if(arrowPressed){
            if (arrowRect.contains(event->pos())){
                arrowClicked();
            }
        }
        arrowPressed = false;
        if(sitePressed){
            if (siteRect.contains(event->pos())){
                siteClicked();
            }
        }
        sitePressed = false;
    }
    event->ignore();
}

void SoftKeyboard::paintEvent(QPaintEvent *e)
{

}

/* 特殊按键响应槽 */

/**
 * @brief deleteSlot
 * 删除按钮被点击时若拼音字母栏有字符则删除拼音字母栏的最后一个字母，否则删除输出框的最后一个字符
 */
void SoftKeyboard::deleteSlot()
{
    if (!alreadyInputLetters.isEmpty()){
        alreadyInputLetters = alreadyInputLetters.mid(0, alreadyInputLetters.size()-1);
        searchBegin(XYInputSearchInterface::getInstance()->searchTranslates(alreadyInputLetters));
    } else{
        if(!hTranslateView->dataStrings.isEmpty()){
            clearHistory();
        }
        arrowChange();
        emit sendDeleteCharacter();
    }

}

void SoftKeyboard::enterSlot()
{

    if(letterLabel->text().isEmpty())
    {
        addCandidateCharacterText("\n");
        return;
    }
    else if(hTranslateView->dataStrings.size() > 0){
        addCandidateCharacterText(alreadyInputLetters);
    }
    clearHistory();

}

void SoftKeyboard::spaceSlot()
{
    if(letterLabel->text().isEmpty())
    {
        addCandidateCharacterText(" ");
        return;
    }
    else if(hTranslateView->dataStrings.size() > 0){
        userSelectChinese(hTranslateView->dataStrings.at(0),0);
    }
}

void SoftKeyboard::on_btn_num_key_clicked()
{
    switchPage(KEYBOARD_NUM);
}

void SoftKeyboard::on_btn_en_key_clicked()
{
    switchPage(KEYBOARD_EN);
}

void SoftKeyboard::on_btn_hand_key_clicked()
{
    switchPage(KEYBOARD_HAND);
}

void SoftKeyboard::on_btn_punc_key_clicked()
{
    switchPage(KEYBOARD_PUNC);
}
