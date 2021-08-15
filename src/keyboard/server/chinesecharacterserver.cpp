#include "chinesecharacterserver.h"
#include <QString>
#include <QThread>
#include <QFile>
#include <QDebug>
#include "model/filereadandwrite.h"
#include <QDir>
#include <QDateTime>

/**
 * @brief ChineseCharacterServer::ChineseCharacterServer
 * 服务类
 */
ChineseCharacterServer::ChineseCharacterServer()
{

}

void ChineseCharacterServer::init()    //初始化
{
    this->start();
}

void ChineseCharacterServer::run()
{

    //顺序比对算法
    if (!mHandWrite.loadModelFile(dirPath + "/numhandwriting.txt", CHAR_NUM)) {
        mHandWrite.loadModelFile(":/numhandwriting.txt", CHAR_NUM);
    }

//    if (!mHandWrite.loadModelFile(":/handwriting.txt")){
//        mHandWrite.loadModelFile(":/handwriting.txt");
//    }

    //树型比对算法
//    if (!mHandTree.loadModelFile(dirPath + "/numhandwritingtree.txt", CHAR_NUM)) {
//        mHandTree.loadModelFile(":/numhandwritingtree.txt", CHAR_NUM);
//    }

    if (!mHandTree.loadModelFile(dirPath + "/handwritingtree.txt")) {
        mHandTree.loadModelFile(":/handwritingtree.txt");
    }


    mWordAssociate.loadModelFile(":/words.txt");
}

/**
 * @brief ChineseCharacterServer::getWordAssociate
 * @param word
 * @return
 * 检索联想词
 */
QStringList ChineseCharacterServer::getWordAssociate(QString word)
{
    return mWordAssociate.searchWords(word);

}

QStringList ChineseCharacterServer::getChineseByPinyin(QString str)
{
    Q_UNUSED(str);
    return getNext();
}

/**
 * @brief ChineseCharacterServer::getChineseByHand
 * @param character 用户的手写数据
 * @param count 最大返回候选词数量
 * @return 候选词列表
 * 根据传进来的手写数据和数量查找到相应的候选词并返回
 */
QStringList ChineseCharacterServer::getChineseByHand(CharacterEntity& character, int count)
{
    //清空候选词列表
    resultWords.clear();
    this->wordCount = count;
    this->index = 0;
    //将查找到的候选词存放在候选词列表中
    if (character.isNum) {
        mHandWrite.recognize(character, &resultWords);
    } else {
        mHandTree.recognize(character, &resultWords);
    }
    return getNext();   //返回候选词
}

//从候选词列表中获取一定数量的候选词并返回
QStringList ChineseCharacterServer::getNext()
{
    QStringList str;

    for (int i = index; i < this->wordCount && i < resultWords.size(); ++i){
        str.append(resultWords.at(this->index++));
    }
    return str;
}

/**
 * @brief ChineseCharacterServer::writeFile
 * @param text
 * @return
 * 训练字库保存
 */
bool ChineseCharacterServer::writeFile(QString text){
    QDir dir;
    if (!dir.exists(dirPath)) {
        dir.mkpath(dirPath);
    }
    return FileReadAndWrite::writeFile(dirPath + "/handpoint.txt", text);
}

int ChineseCharacterServer::saveCharaters(QList<CharacterEntity>& charactrs)
{
    int count = mHandTree.megerCharacter(charactrs);
    mHandTree.wirteFile(dirPath + "/handwritingtree.txt");
    return count;
}

bool ChineseCharacterServer::deleteFont()
{
    QFile file(QString("%1/handwritingtree.txt").arg(dirPath));

    int timeT = QDateTime::currentDateTime().toTime_t()/1000%(365*24*60*60);   //获取当前时间戳

    bool ok = file.rename(QString("%1/handwritingtree_%2.txt").arg(dirPath).arg(timeT));
    if (!ok) {
        perror("rename");
    }
    return ok;
}
