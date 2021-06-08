#ifndef STROKEENTITY_H
#define STROKEENTITY_H

#include "entity/pointentity.h"

#include <QList>

class StrokeEntity
{
public:
    StrokeEntity();

    QList<PointEntity> points;
};

#endif // STROKEENTITY_H
