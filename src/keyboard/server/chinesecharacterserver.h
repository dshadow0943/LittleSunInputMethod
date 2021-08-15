#ifndef CHINESECHARACTERSERVER_H
#define CHINESECHARACTERSERVER_H

#include "handwritemodel.h"
#include "wordassociatemodel.h"
#include "handwritetreemodel.h"
#include <QStringList>
#include <QThread>
#include <QStandardPaths>

class ChineseCharacterServer : public QThread
{
public:
    ChineseCharacterServer();

    void init();    //初始化
    QStringList getChineseByPinyin(QString);
    QStringList getChineseByHand(CharacterEntity& Character, int count = 20);
    QStringList getNext();

    QStringList getWordAssociate(QString word);

    bool writeFile(QString text);
    int saveCharaters(QList<CharacterEntity>&);
    bool deleteFont();

private:

    QStringList resultWords;
    int wordCount;
    int index;
    HandWriteModel mHandWrite;
    HandwriteTreeModel mHandTree;
    WordAssociateModel mWordAssociate;

    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.littlesun";

protected:
    void run();
};

#endif // CHINESECHARACTERSERVER_H
