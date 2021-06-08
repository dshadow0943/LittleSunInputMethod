#ifndef WORDENTITY_H
#define WORDENTITY_H

#include <QString>

class WordEntity
{
public:
    WordEntity();

    QString word;
    double dist;

    static bool cmpWordDist(const WordEntity word1, const WordEntity word2);

};

#endif // WORDENTITY_H
