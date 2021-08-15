#include "wordassociatemodel.h"
#include <QDebug>

/**
 * @brief WordAssociateModel::WordAssociateModel
 * 联想词检索实现类
 */
WordAssociateModel::WordAssociateModel()
{

}

/**
 * @brief WordAssociateModel::loadModelFile
 * @param filePath
 * @return
 * 读取文件
 */
bool WordAssociateModel::loadModelFile(const QString filePath)
{
    QFile ifs(filePath);

    if(!ifs.open(QIODevice::ReadOnly)){
        perror("open");
        return false;
    }

    while (!ifs.atEnd()){

        QString line = ifs.readLine();
        QStringList s = line.split(" ");
        WordEntity *word = new WordEntity();
        word->word = s[0];
        word->fre = s[1].toInt();
        words.push_back(word);

    }
    return true;
}

/**
 * @brief WordAssociateModel::searchWords
 * @param word
 * @return
 * 采用二分法查找匹配词汇
 */
QStringList WordAssociateModel::searchWords(QString word)
{
    int front = 0;
    int last = words.size();
    int mid = 0;
    while (front < last) {
        mid = (front + last)/2;

        int ret = QString::compare(word, words.at(mid)->word.left(word.size()));
        if (ret == 0) {
            return backResult(word, mid);
        } else if (ret < 0) {
            last = mid-1;
        } else if (ret > 0) {
            front = mid+1;
        }
    }
    QStringList result;
    return result;
}

/**
 * @brief WordAssociateModel::backResult
 * @param word
 * @param index
 * @return
 * 获取匹配的词汇
 */
QStringList WordAssociateModel::backResult(QString word, int index)
{
    while (index >= 0 && QString::compare(word, words.at(index)->word.left(word.size())) == 0) {
        index--;
    }
    index++;

    QStringList resultWords;
    while (index < words.size() && QString::compare(word, words.at(index)->word.left(word.size())) == 0) {
        if (word.size() == words.at(index)->word.size()){
            continue;
        }
        resultWords.push_back(words.at(index)->word.right(words.at(index)->word.size()-1));
        index++;
    }
    return resultWords;
}
