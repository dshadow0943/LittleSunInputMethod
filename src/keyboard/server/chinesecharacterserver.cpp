#include "chinesecharacterserver.h"
#include <QString>
#include <QThread>
#include <QFile>
#include <QDebug>
#include "model/filereadandwrite.h"
#include <QDir>

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
    if (mHandWrite.loadModelFileNew(":/handwriting.txt")){
    } else {

    }

    if (mHandWrite.loadModelFileNew(":/numhandwriting.txt", CHAR_NUM)){
    } else {

    }

    if (mWordAssociate.loadModelFile(":/words.txt")) {

    } else {

    }
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
    mHandWrite.recognize(character, &resultWords); //将查找到的候选词存放在候选词列表中
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
    return FileReadAndWrite::writeFile("./handpoint.txt", text);
}
