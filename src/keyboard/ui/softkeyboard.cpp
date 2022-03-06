#include "softkeyboard.h"
#include "ui_softkeyboard.h"
#include "numkeyboard.h"
#include "handkeyboard.h"
#include "enkeyboard.h"
#include "punckeyboard.h"
#include "handkeyboard.h"
#include "settingmanage.h"
#include "settingmanage.h"
#include "globalsignaltransfer.h"
#include <QLabel>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QFont>
#include <QApplication>
#include <QDesktopWidget>

SoftKeyboard::SoftKeyboard(int id, QWidget *parent) :
    WindowBase(id, parent),
    ui(new Ui::SoftKeyboard)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::WindowDoesNotAcceptFocus);
    mThesaurusManage = ThesaurusRetrieval::getInstance();
    initUi();

    setMoveEnabled();
    setAttribute(Qt::WA_TranslucentBackground,  true);
    mAnimation = new QPropertyAnimation(ui->keyboard, "geometry");

    //连接主题更改事件
    connect(SettingManage::getInstance(), &SettingManage::sendThemeChange, this, &SoftKeyboard::onThemeChange);
    //连接主题更改事件
    connect(SettingManage::getInstance(), &SettingManage::sendKetTabCheBoxClicked, this, &SoftKeyboard::onKeyTabDisplayChange);
    //键盘大小更改事件
    connect(SettingManage::getInstance(), &SettingManage::sendKeyboardScaleChange, this, &SoftKeyboard::onKeyboardScaleChange);
    //连接键盘按键点击事件
    connect(GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::sendKeyButtonClicked,
            this, &SoftKeyboard::onKeyButtonClicked);
    //连接滑动框（候选词）点击事件
    connect(GlobalSignalTransfer::getInstance(), &GlobalSignalTransfer::sendScrollBarClosed,
            this, &SoftKeyboard::onSelectPhrase);
}

SoftKeyboard::~SoftKeyboard()
{
    delete ui;
    delete mAnimation;
}

void SoftKeyboard::initUi()
{
    setThemeStyleSheet();

    mVTranslateView = ScrollBarManage::getVCanditateView();
    mHTranslateView = ScrollBarManage::getHCanditateView();

    initCandidate();
    initKeyboard();
    initTab();
}

/**
 * @brief SoftKeyboard::initCandidate
 * 初始化候选框相关控件
 */
void SoftKeyboard::initCandidate()
{

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setMargin(0);
    vLayout->setMargin(0);
    mLetterLabel = new QLabel();
    QFont font = mLetterLabel->font();
    font.setUnderline(true);
    mLetterLabel->setFont(font);
    ScrollBarContainer *scroll = new ScrollBarContainer();
    scroll->setWidget(ScrollBarManage::getHCanditateView(), ScrollBarContainer::Horizontal, 2);
    vLayout->addWidget(mLetterLabel, 1);
    vLayout->addWidget(scroll, 2);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setMargin(0);
    hLayout->setMargin(0);

    mSite = new IconButton(":/icon/site.svg");

    mArrow = new IconButton(":/icon/arrow_b.svg");
    onArrowChange();
    hLayout->addWidget(mSite);
    hLayout->addLayout(vLayout, 8);
    hLayout->addWidget(mArrow);
    hLayout->setContentsMargins(2, 0, 4, 0);

    ui->candidata_box->setLayout(hLayout);
}

/**
 * @brief SoftKeyboard::initKeyType
 * 初始化键盘相关控件
 */
void SoftKeyboard::initKeyboard()
{
    ui->key_page->addWidget(new NumKeyboard(this));
    ui->key_page->addWidget(new EnKeyboard(this));
    HandKeyboard *hKeyboard = new HandKeyboard(this);
    ui->key_page->addWidget(hKeyboard);
    ui->key_page->addWidget(new PuncKeyboard(this));
    connect(hKeyboard, &HandKeyboard::sendPointToCharacter, this, &SoftKeyboard::onPointToChaeracter);

    ScrollBarContainer *sbc = new ScrollBarContainer(this);
    sbc->setWidget(ScrollBarManage::getVCanditateView(), ScrollBarContainer::Vertical, 1);
    ui->key_page->addWidget(sbc);

    onKeyTabDisplayChange();
}

void SoftKeyboard::initTab()
{
    QVBoxLayout *vLayout = new QVBoxLayout(ui->key_tabs);
    vLayout->setMargin(0);
    vLayout->setSpacing(5);

    mLog = new IconButton(":/icon/littlesun.png");
    mLog->setMinimumHeight(10);
    vLayout->addWidget(mLog, 1);

    mTabSidebar = new KeyboardSidebar({"数字", "拼音", "手写", "符号"});
    connect(mTabSidebar, &KeyboardSidebar::sendCurrentIndex, this, &SoftKeyboard::onSwitchKeyBoard);
    vLayout->addWidget(mTabSidebar, 7);

    ui->key_tabs->setLayout(vLayout);
}

/**
 * @brief SoftKeyboard::arrowClicked
 * 右上角箭头按钮按下事件
 * 根据当前输入状态执行相应的下一步操作
 */
void SoftKeyboard::onArrowClicked()
{
    switch(arrowStatus) {
        case ARROW_CLOSE:
//        delete this;
            hideKeyboard();
            closeWindow();
        break;
        case ARROW_CAND: switchPreviousKey();    //（当前是查看更多候选词状态）返回上一界面
        break;
        case ARROW_SHOW: onSwitchKeyBoard(KEYBOARD_CAND);  //（当前是输入状态）进入更多候选词界面
        break;
    }
}

void SoftKeyboard::onArrowChange()
{
    QString path;

    if (mHTranslateView->dataStrings.isEmpty()){
        path = ":/icon/arrow_b.svg";
        arrowStatus = ARROW_CLOSE;
    } else if (ui->key_page->currentIndex() == KEYBOARD_CAND){
        path = ":/icon/arrow_b.svg";
        arrowStatus = ARROW_CAND;
    } else {
        path = ":/icon/arrow_r.svg";
        arrowStatus = ARROW_SHOW;
    }
    mArrow->setIconPath(path);  //加载图标
}

/**
 * @brief SoftKeyboard::siteClicked
 * 设置按钮按下事件
 */
void SoftKeyboard::onSiteClicked()
{
    emit sendSiteClicked();
}

void SoftKeyboard::onThemeChange()
{
    setThemeStyleSheet();
    mTabSidebar->setCurrentIndex();
}

/**
 * @brief SoftKeyboard::onKeyButtonClicked
 * 键盘点击事件响应
 * @param but 按下的键
 */
void SoftKeyboard::onKeyButtonClicked(KeyButtonBase* but)
{
    switch (but->getId()) {
    case Qt::Key_Backspace:
        deleteClicked();
        break;
    case Qt::Key_Enter:
        enterClicked();
        break;
    case Qt::Key_Space:
        spaceClicked();
        break;
    case KeyButtonBase::KeyNum:
        mTabSidebar->setCurrentIndex(KEYBOARD_NUM);
        break;
    case KeyButtonBase::keyPinyin:
        mTabSidebar->setCurrentIndex(KEYBOARD_EN);
        break;
    case KeyButtonBase::keyPunc:
        mTabSidebar->setCurrentIndex(KEYBOARD_PUNC);
        break;
    case KeyButtonBase::keyHand:
        mTabSidebar->setCurrentIndex(KEYBOARD_HAND);
        break;
    case KeyButtonBase::KeyBack:
        mTabSidebar->setCurrentIndex(mPreviousKey);
        break;
    case KeyButtonBase::KeyChinese:
        break;
    case KeyButtonBase::KeyEnglish:
        break;
    case KeyButtonBase::KeyMath:
        break;
    default: {
        if (but->getType() == KeyButtonBase::Tab || but->getType() == KeyButtonBase::Func) {
            break;
        }
        if (ButtonItem::getSwitchButton()->isEnglish()) {
            pushCandidateCharacterText(but->getText());
            break;
        } else {
            if (but->getType() == KeyButtonBase::PinyinNum) {
                if (!mHTranslateView->selectPhrase(but->getText().toInt())) {
                    pushCandidateCharacterText(but->getText());
                    break;
                }
            } else if (but->getType() == KeyButtonBase::PinyinLetter) {
                addCandidateLetter(but->getText());
                break;
            } else {
                pushCandidateCharacterText(but->getText());
                break;
            }
        }
    }
    }
}

/**
 * @brief SoftKeyboard::showEvent
 * @param event
 * 重写showEvent函数
 */
void SoftKeyboard::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    //设置显示键盘类型
    mTabSidebar->setCurrentIndex(SettingManage::getInstance()->getDefaultKeyboard());
    //调整键盘大小
    onKeyboardScaleChange();
    //拼音键盘设置为英文输入状态
    ButtonItem::getSwitchButton()->switchText(true);
    //展示动画
    showKeyboard();
}

/**
 * @brief SoftKeyboard::switchPage
 * @param type 需要切换的布局
 * 切换布局，更新窗口大小
 *
 */
void SoftKeyboard::onSwitchKeyBoard(int type)
{
    //如需要切换SoftKeyboard::的键盘和当前显示的键盘是同一个则直接不做处理，防止连续重复点击
    if (ui->key_page->currentIndex() == type && -1 != mPreviousKey){
        return;
    }

    int w = EN_DEFAULT_WIDTH, h = EN_DEFAULT_HEIGHT;

    switch (type) {
        case KEYBOARD_NUM:
        case KEYBOARD_HAND:
        case KEYBOARD_PUNC:
            w = int(DEFAULT_WIDTH * winScale);
            h = int(DEFAULT_HEIGHT * winScale);
            break;
        case KEYBOARD_EN:
            w = int(EN_DEFAULT_WIDTH * winScale);
            h = int(EN_DEFAULT_HEIGHT * winScale);
        break;
        case KEYBOARD_CAND:
            break;
        default:
            return;
    }

    if (!(type == KEYBOARD_CAND || (ui->key_page->currentIndex() == KEYBOARD_CAND && type == mPreviousKey))) {
        clearHistory(); //重置清空候选词
        this->resize(w, h);    //更新窗口大小
        ui->keyboard->resize(this->size());
    }

    if (ui->key_page->currentIndex() != KEYBOARD_CAND) {
        mPreviousKey = ui->key_page->currentIndex();
    }

    ui->key_page->setCurrentIndex(type);        //更新QStackedWidget栈布局内容
    onArrowChange();
}

/**
 * @brief SoftKeyboard::fillCandidateText
 * @param strList 待填充的文本列表
 * 填充候选框文本(手写)
 */
void SoftKeyboard::fillCandidateText(QStringList& strList){

    ScrollBarManage::getInstace()->setCanditeData(strList);  //填充候选词
    onArrowChange();  //更改箭头状态
}

/**
 * @brief addCandidateCharacterText
 * @param character
 * 将字符添加到输出框中
 */
void SoftKeyboard::pushCandidateCharacterText(QString character)
{
    emit sendCandidateCharacter(character);
}

/**
 * @brief SoftKeyboard::clear_history
 * 重置候选框数据
 */
void SoftKeyboard::clearHistory()
{
    mLetterLabel->clear();
    mAlreadyInputLetters.clear();
    mAlreadySelectTranslates.clear();
    mVTranslateView->clearData();
    mHTranslateView->clearData();
    mThesaurusManage->reset();
}

void SoftKeyboard::refreshCandidatePhrases(QStringList data)
{
    ScrollBarManage::getInstace()->setCanditeData(data);
    mLetterLabel->setText(PinyinRetrievalModel::getInstance()->getCurLetters());
    onArrowChange();  //更新箭头状态
}

/**
 * @brief SoftKeyboard::userSelectChinese
 * @param text
 * @param index
 * 拼音输入时点击候选词的处理方法
 */
void SoftKeyboard::onSelectPhrase(QString text, int index)
{
    QString showText;
    QStringList data = PinyinRetrievalModel::getInstance()->getCandidate(text, index, showText);
    mLetterLabel->setText(showText);

    if(data.isEmpty()){        //点击候选词后无剩余候选字母
        //这里完成输入
        QString word = mAlreadySelectTranslates.join("").append(text);
        pushCandidateCharacterText(word);  //将数据发送出去
        clearHistory();        //清空数据

        //如果是查看更多候选词界面则模拟点击箭头返回到原来界面
        if (ui->key_page->currentIndex() == KEYBOARD_CAND){
            onArrowClicked();
        }
        onArrowChange();

        //查找联想词
        QStringList words = mThesaurusManage->getAssociateWords(text);
        if (words.size() != 0) {
            fillCandidateText(words);
        }
    }
    else    //如果还剩候选字母则留着等着再次处理
    {
        mAlreadySelectTranslates.append(text);
        ScrollBarManage::getInstace()->setCanditeData(data);
    }
}

void SoftKeyboard::onKeyTabDisplayChange()
{
    if (!mTabLock) {
        ui->key_tabs->setVisible(false);
        return;
    }
    ui->key_tabs->setVisible(SettingManage::getInstance()->getKeyTabDisplay());
}

void SoftKeyboard::onKeyboardScaleChange()
{
    static QRect applicationRect = QGuiApplication::screens().at(0)->geometry();     //获取显示屏像素
    winScale = SettingManage::getInstance()->getKeyboardSizeScale();
    if (0 < winScale){
        ui->key_tabs->setMaximumWidth(int(110*winScale));
        ui->key_tabs->setMinimumWidth(int(110*winScale));
        int w = EN_DEFAULT_WIDTH, h = EN_DEFAULT_HEIGHT;
        int page = ui->key_page->currentIndex();
        if (KEYBOARD_CAND == page) {
            page = mPreviousKey;
        }
        int criticalValue = 500;
        switch (page) {
            case KEYBOARD_NUM:
            case KEYBOARD_HAND:
            case KEYBOARD_PUNC:
                w = int(DEFAULT_WIDTH * winScale);
                h = int(DEFAULT_HEIGHT * winScale);
                criticalValue = 400;
                break;
            case KEYBOARD_EN:
                w = int(EN_DEFAULT_WIDTH * winScale);
                h = int(EN_DEFAULT_HEIGHT * winScale);
                criticalValue = 500;
            break;
            default:
                return;
        }
        this->resize(w, h);    //更新窗口大小
        ui->keyboard->resize(this->size());
        this->move((applicationRect.width()-width())/2, applicationRect.height()-height());       //移动窗口位置,默认出现在底端中部

        int size = ui->candidata_box->height()/3;
        ScrollBarManage::getHCanditateView()->setUnitFontSize(size + int(winScale*3));
        mTabSidebar->setFontSize(ui->key_tabs->width()/3);
        QFont font = mLetterLabel->font();
        font.setPixelSize(size-1);
        mLetterLabel->setFont(font);

        if (mTabLock && this->width() <= criticalValue) {
            mTabLock = false;
            onKeyTabDisplayChange();
        } else if (!mTabLock && this->width() > criticalValue) {
            mTabLock = true;
            onKeyTabDisplayChange();
        }
    } else {
        int w = int(applicationRect.width()*0.35);            //显示屏的宽
        int h = applicationRect.height();           //显示屏的高

        int winSizeW = EN_DEFAULT_WIDTH;   //键盘顶层布局宽度，默认(最大)1000

        if (w < winSizeW){
            winSizeW = w;               //根据显示屏大小设置顶层窗口的默认大小
        }
        winSizeW = winSizeW > h? h : winSizeW;

        winScale = winSizeW*1.0/EN_DEFAULT_WIDTH;    //根据界面大小等比例变换窗口大小
        ui->key_tabs->setMaximumWidth(int(110*winScale));
        SettingManage::getInstance()->setKeyboardSizeScale(winScale);
    }
}

void SoftKeyboard::addCandidateLetter(QString letter)
{
    mAlreadyInputLetters.append(letter.toLower());
    refreshCandidatePhrases(mThesaurusManage->getPhraseByPinyin(mAlreadyInputLetters));
}

/* 重写事件 */

/**
 * @brief SoftKeyboard::setMoveEnabled
 * @param moveEnabled
 * 设置是否可拖动
 */
void SoftKeyboard::setMoveEnabled(bool moveEnabled) {
    mIsMoveEnabled = moveEnabled;
}

void SoftKeyboard::onPointToChaeracter(CharacterEntity character)
{
    QStringList strs = mThesaurusManage->getChineseByHand(character, 20);
    fillCandidateText(strs);
}

void SoftKeyboard::switchPreviousKey()
{
    onSwitchKeyBoard(mPreviousKey);
}

void SoftKeyboard::showKeyboard()
{
    ui->keyboard->move(0, height());
//    ui->keyboard->hide();
    mAnimation->setDuration(100);

    int w = ui->keyboard->width();
    int h = ui->keyboard->height();
    int x = 0;
    int y = 0;

    if (ui->keyboard->isHidden())
    {
//        ui->keyboard->move(0, height());
        ui->keyboard->show();
    }
    mAnimation->setStartValue(ui->keyboard->geometry());

    mAnimation->setEndValue(QRect(x, y, w, h));
    mAnimation->setEasingCurve(QEasingCurve::Linear); //设置动画效果

    mAnimation->start();
}

void SoftKeyboard::hideKeyboard()
{
//    mAnimation->setTargetObject(ui->keyboard);

    mAnimation->setDuration(100);

    int w = ui->keyboard->width();
    int h = ui->keyboard->height();
    int x = 0;
    int y = ui->keyboard->height();

    mAnimation->setStartValue(ui->keyboard->geometry());
    mAnimation->setEndValue(QRect(x, y, w, h));
    mAnimation->setEasingCurve(QEasingCurve::Linear); //设置动画效果

    mAnimation->start();
}

/**
 * @brief SoftKeyboard::mousePressEvent
 * @param event
 * 捕捉鼠标按下事件
 * 重写鼠标按下键，获取鼠标左键按下时的全局位置，将窗口的可移动标志设置为true
 */
void SoftKeyboard::mousePressEvent(QMouseEvent *event) {
    mCursorGlobalPos = event->globalPos();  //获取鼠标按下时的全局位置

    arrowRect = QRect(mArrow->mapTo(this, QPoint(0, 0)), mArrow->size());
    if(event->button() == Qt::LeftButton && arrowRect.contains(event->pos()))
    {
        arrowPressed = true;
        return;
    }

    siteRect = QRect(mSite->mapTo(this, QPoint(0, 0)), mSite->size());
    if(event->button() == Qt::LeftButton && siteRect.contains(event->pos()))
    {
        sitePressed = true;
        return;
    }

    if (event->button() == Qt::LeftButton
            && (mLog->geometry().contains(event->pos()) || ui->candidata_box->geometry().contains(event->pos())))//左键按下
    {
        mIsMousePress = true;
    }
}

/**
 * @brief SoftKeyboard::mouseMoveEventglobalPos()
 * @param event
 * 重写鼠标移动事件，使窗口跟着鼠标移动
 */
void SoftKeyboard::mouseMoveEvent(QMouseEvent *event) {

    if (event->buttons() & Qt::LeftButton && mIsMousePress && mIsMoveEnabled) {
        window()->move(window()->pos() +  event->globalPos() - mCursorGlobalPos);
        mCursorGlobalPos = event->globalPos();
    }
}

/**
 * @brief SoftKeyboard::mouseReleaseEvent
 * @param event
 * 重写鼠标抬起（释放）事件，将窗口的可移动标志设置为false
 */
void SoftKeyboard::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)//左键释放
    {
        mIsMousePress = false;
        if(arrowPressed){
            if (arrowRect.contains(event->pos())){
                onArrowClicked();
            }
        }
        arrowPressed = false;
        if(sitePressed){
            if (siteRect.contains(event->pos())){
                onSiteClicked();
            }
        }
        sitePressed = false;
    }
}

/* 特殊按键响应槽 */

/**
 * @brief deleteSlot
 * 删除按钮被点击时若拼音字母栏有字符则删除拼音字母栏的最后一个字母，否则删除输出框的最后一个字符
 */
void SoftKeyboard::deleteClicked()
{
    if (!mAlreadyInputLetters.isEmpty()){
        mAlreadyInputLetters = mAlreadyInputLetters.mid(0, mAlreadyInputLetters.size()-1);
        refreshCandidatePhrases(PinyinRetrievalModel::getInstance()->getCandidate(mAlreadyInputLetters));
    } else if (!mHTranslateView->dataStrings.isEmpty()){
        clearHistory();
        onArrowChange();
    } else {
        emit sendDeleteCharacter();
    }
}

void SoftKeyboard::enterClicked()
{
    if(mLetterLabel->text().isEmpty())
    {
        pushCandidateCharacterText("\r");
        return;
    }
    else if(mHTranslateView->dataStrings.size() > 0){
        pushCandidateCharacterText(mAlreadyInputLetters);
    }
    clearHistory();
}

void SoftKeyboard::spaceClicked()
{
    if (!mHTranslateView->selectPhrase(0)) {
        pushCandidateCharacterText(" ");
    }
}

void SoftKeyboard::setThemeStyleSheet()
{
    skin_color s = SettingManage::getInstance()->getSkinColor(SkinType::Theme);

    ui->keyboard->setStyleSheet(QString("QWidget#keyboard{border-radius: 10px; background:qradialgradient("
                          "spread:pad, cx:0.5, cy:0.5, radius:0.8, fx:0.5, fy:0.5,stop:0 %1,stop:1 %2);}")
                  .arg(s.normal.name())
                  .arg(s.pressed.name()));

}
