#include "thesaurusretrieval.h"
#include "fileutil.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDateTime>

Q_DECLARE_METATYPE(std::function<void()>);

/**
 * @brief ChineseCharacterServer::ChineseCharacterServer
 * 服务类
 */
ThesaurusRetrieval::ThesaurusRetrieval(QObject *parent) : QThread (parent)
{
    mPinyin = PinyinRetrievalModel::getInstance();
    start();

    qRegisterMetaType<std::function<void()>>();
    connect(this, &ThesaurusRetrieval::comming, this, &ThesaurusRetrieval::onConming);
}

ThesaurusRetrieval* ThesaurusRetrieval::getInstance()
{
    static ThesaurusRetrieval obj;
    return &obj;
}

void ThesaurusRetrieval::onConming(std::function<void()> f){
    f();
}

void ThesaurusRetrieval::initDB()    //初始化
{
    bool ret = true;
    QString filePath = mDirPath + "/chineseBase/chinese.db";
    if (!QFile(filePath).exists()) {

        if (!QDir(mDirPath + "/chineseBase").exists()){
            QDir().mkpath(mDirPath + "/chineseBase");
        }
        if (QFile().copy("/usr/local/littlesun/chineseBase/chinese.db", filePath)) {
        } else if (QFile().copy("./chineseBase/chinese.db", filePath)) {
        } else if (QFile().copy("./../../chineseBase/chinese.db", filePath)) {
        } else {
            ret = false;
        }
    }

    if (ret) {
        mPinyin->initInputBase(filePath);
    } else {
        qCritical() << "Load SqlDateBase failed!";
    }
}

void ThesaurusRetrieval::run()
{
    //顺序比对算法
//    if (!mHandWrite.loadModelFile(mDirPath + "/numhandwriting.txt", CHAR_NUM)) {
//        mHandWrite.loadModelFile(":/numhandwriting.txt", CHAR_NUM);
//    }

    //树型比对算法
//    if (!mHandTree.loadModelFile(dirPath + "/numhandwritingtree.txt", CHAR_NUM)) {
//        mHandTree.loadModelFile(":/numhandwritingtree.txt", CHAR_NUM);
//    }

    initDB();

    if (!mHandTree.loadModelFile(mDirPath + "/handwritingtree.txt")) {
        mHandTree.loadModelFile(":/handwritingtree.txt");
    }
}

void ThesaurusRetrieval::reset()
{
    mWordCount = 0;
    mIndex = 0;
    mResultWords.clear();
    mPinyin->resetSearch();
}

/**
 * @brief ThesaurusRetrieval::::getWordAssociate
 * @param word
 * @return
 * 检索联想词
 */
QStringList ThesaurusRetrieval::getAssociateWords(QString word)
{
    return mPinyin->getAssociationalWords(word);

}

QStringList ThesaurusRetrieval::getPunc(DBOperation::PuncType type)
{
    return mPunc.getPunc(type);
}

void ThesaurusRetrieval::updatePunc(QString& data, DBOperation::PuncType type)
{
    std::thread([=](){
        mPunc.updatePunc(data, type);
    }).detach();
}

QStringList ThesaurusRetrieval::getPhraseByPinyin(QString keyword, bool isEnglish)
{
    return mPinyin->getCandidate(keyword, isEnglish);
}

QStringList ThesaurusRetrieval::getPhraseByPinyin(const QString &text, int index, QString &showText)
{
    return mPinyin->getCandidate(text, index, showText);
}

/**
 * @brief ThesaurusRetrieval::::getChineseByHand
 * @param character 用户的手写数据
 * @param count 最大返回候选词数量
 * @return 候选词列表
 * 根据传进来的手写数据和数量查找到相应的候选词并返回
 */
QStringList ThesaurusRetrieval::getChineseByHand(CharacterEntity character, int count)
{
    //清空候选词列表
    mResultWords.clear();
    this->mWordCount = count;
    this->mIndex = 0;
    //将查找到的候选词存放在候选词列表中
    if (character.isNum) {
        mHandWrite.recognize(character, &mResultWords);
    } else {
        mHandTree.recognize(character, &mResultWords);
    }
    return getNext();   //返回候选词
}

//从候选词列表中获取一定数量的候选词并返回
QStringList ThesaurusRetrieval::getNext()
{
    QStringList str;

    for (int i = mIndex; i < this->mWordCount && i < mResultWords.size(); ++i){
        str.append(mResultWords.at(this->mIndex++));
    }
    return str;
}

/**
 * @brief ThesaurusRetrieval::::writeFile
 * @param text
 * @return
 * 训练字库保存
 */
bool ThesaurusRetrieval::writeFile(QString text){
    QDir dir;
    if (!dir.exists(mDirPath)) {
        dir.mkpath(mDirPath);
    }
    return FileUtil::writeFile(mDirPath + "/handpoint.txt", text);
}

int ThesaurusRetrieval::saveCharaters(QList<CharacterEntity>& charactrs)
{
    int count = mHandTree.megerCharacter(charactrs);
    mHandTree.wirteFile(mDirPath + "/handwritingtree.txt");
    return count;
}

bool ThesaurusRetrieval::deleteFont()
{
    QFile file(QString("%1/handwritingtree.txt").arg(mDirPath));

    int timeT = QDateTime::currentDateTime().toTime_t()/1000%(365*24*60*60);   //获取当前时间戳

    bool ok = file.rename(QString("%1/handwritingtree_%2.txt").arg(mDirPath).arg(timeT));
    if (!ok) {
        perror("rename");
    }
    return ok;
}
