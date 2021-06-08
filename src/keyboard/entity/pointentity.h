#ifndef POINT_H
#define POINT_H

#include <QString>

class PointEntity
{
public:
    PointEntity(int x, int y);
    PointEntity();

    int x;
    int y;
    double direc;

    void setDire(PointEntity);
    static double setDire(PointEntity, PointEntity);

    static PointEntity copy(PointEntity);
    static int getDegree(PointEntity vertexPoint, PointEntity point1, PointEntity point2);
    static int getDegree(int vertexPointX, int vertexPointY, int point0X, int point0Y, int point1X, int point1Y);
    QString toString();

};

#endif // POINT_H
