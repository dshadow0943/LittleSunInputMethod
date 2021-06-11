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
        qDebug() << "打开文件成功";
    } else {
        qDebug() << "打开文件失败:";
    }

    if (mHandWrite.loadModelFileNew(":/numhandwriting.txt", CHAR_NUM)){
        qDebug() << "打开文件成功";
    } else {
        qDebug() << "打开文件失败:";
    }

}

QStringList ChineseCharacterServer::getChineseByPinyin(QString str)
{
    return getNext();
}

QStringList ChineseCharacterServer::getChineseByHand(CharacterEntity character, int count)
{
    resultWords.clear();
    this->wordCount = count;
    this->index = 0;
    mHandWrite.recognize(character, &resultWords);
//    qDebug() << "1:" << character.toString();
    return resultWords;
}

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
