#ifndef CHARACTERENTITY_H
#define CHARACTERENTITY_H

#include "entity/strokeentity.h"
#include <QString>

#define DEAFULT_WIDTH 1000
#define DEAFULT_HEIGHT 1000

class CharacterEntity
{
public:
    CharacterEntity();

    bool isNum = false;
    int lastStrokeId;
    int strokeCount;
    QString word;
    QList<StrokeEntity> strokes;

    bool addPoint(int strokeId, int x, int y);
    void clear();
    QString toString();
    QString toDireString();

};

#endif // CHARACTERENTITY_H
