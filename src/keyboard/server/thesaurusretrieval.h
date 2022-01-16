#ifndef CHINESECHARACTERSERVER_H
#define CHINESECHARACTERSERVER_H

#include "handwritemodel.h"
#include "handwritetreemodel.h"
#include "pinyinretrievalmodel.h"
#include "globalconfig.h"
#include <QStringList>
#include <QThread>
#include <QStandardPaths>

class ThesaurusRetrieval : public QThread
{
public:
    static ThesaurusRetrieval* getInstance();
    void initDB();    //初始化
    QStringList getNext();
    QStringList getPhraseByPinyin(const QString &keyword, bool isEnglish = false);
    QStringList getPhraseByPinyin(const QString &text, int index, QString &showText);
    QStringList getChineseByHand(CharacterEntity& Character, int count = 20);
    QStringList getAssociateWords(QString word);
    QStringList getPunc(DBOperation::PuncType);

    bool writeFile(QString text);
    int saveCharaters(QList<CharacterEntity>&);
    bool deleteFont();
    void reset();

private:
    ThesaurusRetrieval();

private:

    int mWordCount;
    int mIndex;
    QStringList mResultWords;
    HandWriteModel mHandWrite;
    HandwriteTreeModel mHandTree;
    PinyinRetrievalModel *mPinyin;

    const QString mDirPath = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + APPLOCALPATH;

protected:
    void run();
};

#endif // CHINESECHARACTERSERVER_Hthis->start();
