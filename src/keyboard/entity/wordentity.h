#ifndef WORDENTITY_H
#define WORDENTITY_H

#include <QString>

class WordEntity
{
public:
    WordEntity();

    QString word;  //词
    double dist;  //区分度
    int fre;   //词频

    static bool cmpWordDist(const WordEntity& word1, const WordEntity& word2);  //区分度比较

};

#endif // WORDENTITY_H
