#ifndef WORDASSOCIATEMODEL_H
#define WORDASSOCIATEMODEL_H

#include "wordentity.h"

#include <QList>

class WordAssociateModel
{
public:
    WordAssociateModel();

    bool loadModelFile(const QString filePath);

    QStringList searchWords(QString word);

private:

    QStringList backResult(QString word, int index);

private:

    QList<WordEntity*> words;


};

#endif // WORDASSOCIATEMODEL_H
