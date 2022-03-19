/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef XYINPUTSEARCHINTERFACE_H
#define XYINPUTSEARCHINTERFACE_H

#include "dboperation.h"
#include <QObject>
#include <QStringList>
#include <QMap>
#include "phraseentity.h"

class PinyinRetrievalModel : public QObject
{
    Q_OBJECT
public:
    static PinyinRetrievalModel *getInstance();
    ~PinyinRetrievalModel();
    bool initInputBase(const QString &path);
    void resetSearch();
    QString getCurLetters();
    QStringList getCandidate(const QString &keyword, bool isEnglish = false);   //获取候选词组
    QStringList getCandidate(const QString &text, int index, QString &showText);    //获取后续词组
    QStringList getAssociationalWords(const QString &text);   //获取联想词
    QStringList getPunc(DBOperation::PuncType);

private:
    explicit PinyinRetrievalModel(QObject *parent = nullptr);

    void setChinese(bool ch);
    void saveItem(PhraseEntity item);
    void clearTemp();
    void deDuplication(QList<PhraseEntity > &items, bool del = true); // 删除重复的字词
    PhraseEntity autoCreateWords(const QString &keyword);  // 自动造词
    // 分割拼音，比如women-->wo%'men,返回分割后的字符串(并加上%模糊查找)，并带回有效的字数
    QString splitPinyin(const QString &pinyin, int &num);
    QStringList getVowelsByInitial(const QChar &initial);
    QList<PhraseEntity> &searchTranslates(const QString &keyword);
    QList<PhraseEntity> findItemsFromTemp(const QString &keyword, bool force = true);
    QList<PhraseEntity> findPossibleMust(const QString &keyword, int max = 200);
    QList<PhraseEntity> &completeInput(const QString &text, int index, QString &showText);
    QList<PhraseEntity> &completeInput(const QString &text, QString &showText, PhraseEntity item);
    QList<PhraseEntity> autoAssociational(const QString &text);  //智能联想

private:
    bool             mEnglish;
    PhraseEntity  mCompleteItem;
    PhraseEntity  mAutoCompleteItem;
    QString          mCurrentKeyWords; //缓存分割后的拼音
    QList<PhraseEntity> mSearchResults; //检索结果
    QMap<QString, QList<PhraseEntity>> mTempItemsMap; // 存储一次输入中查询过的词组
};

#endif // XYINPUTSEARCHINTERFACE_H
