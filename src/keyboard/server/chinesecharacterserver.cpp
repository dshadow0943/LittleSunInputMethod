#include "chinesecharacterserver.h"
#include <QString>
#include <QThread>
#include <QFile>
#include <QDebug>
#include "model/filereadandwrite.h"
#include <QDir>

ChineseCharacterServer::ChineseCharacterServer()
{

}

void ChineseCharacterServer::init()    //初始化
{

    if (mHandWrite.loadModelFileNew(":/handwriting.txt")){
//        qDebug() << "打开文件成功";
    } else {
//        qDebug() << "打开文件失败:";
    }

    if (mHandWrite.loadModelFileNew(":/numhandwriting.txt", CHAR_NUM)){
//        qDebug() << "打开文件成功";
    } else {
//        qDebug() << "打开文件失败:";
    }

    if (mWordAssociate.loadModelFile(":/words.txt")) {

    } else {
        qDebug() << "words文件打开失败";
    }

}

QStringList ChineseCharacterServer::getWordAssociate(QString word)
{
    return mWordAssociate.searchWords(word);

//    qDebug() << "words: " << mWordAssociate.searchWords(word);

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
QStringList ChineseCharacterServer::getChineseByHand(CharacterEntity character, int count)
{
    //清空候选词列表
    resultWords.clear();
    this->wordCount = count;
    this->index = 0;
    mHandWrite.recognize(character, &resultWords); //将查找到的候选词存放在候选词列表中
//    qDebug() << "1:" << character.toString();
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

bool ChineseCharacterServer::writeFile(QString text){
    return FileReadAndWrite::writeFile(QDir::currentPath()+"/" + "handpoint.txt", text);
}
