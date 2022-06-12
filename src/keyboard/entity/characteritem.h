#ifndef CHARACTERITEM_H
#define CHARACTERITEM_H

#include "entity/characterentity.h"
#include <QList>

class CharacterItem
{
public:
    CharacterItem();

    QList<CharacterEntity> charItem;
    QString word;

    QString toString();
    QString toDireString();
};

#endif // CHARACTERITEM_H
