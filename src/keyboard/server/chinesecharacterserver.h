#ifndef CHINESECHARACTERSERVER_H
#define CHINESECHARACTERSERVER_H

#include "handwritemodel.h"
#include "wordassociatemodel.h"
#include <QStringList>

class ChineseCharacterServer
{
public:
    ChineseCharacterServer();

    void init();    //初始化
    QStringList getChineseByPinyin(QString);
    QStringList getChineseByHand(CharacterEntity Character, int count = 8);
    QStringList getNext();

    QStringList getWordAssociate(QString word);

    bool writeFile(QString text);

private:

    QStringList resultWords;
    int wordCount;
    int index;
    HandWriteModel mHandWrite;
    WordAssociateModel mWordAssociate;
};

#endif // CHINESECHARACTERSERVER_H
