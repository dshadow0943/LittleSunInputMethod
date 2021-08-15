#include "pointentity.h"
#include <QtMath>

PointEntity::PointEntity(int x, int y)
{
    this->x = x;
    this->y = y;

}

PointEntity::PointEntity(){}

/**
 * @brief PointEntity::setDire
 * @param lastPoint 上一个坐标点
 * 根据上一个坐标点设置当前坐标的偏移量
 */
void PointEntity::setDire(PointEntity lastPoint)
{
    this->direc = -1;
    double d = atan2(this->y - lastPoint.y,  this->x - lastPoint.x)/3.1415926*180;
    if (d < 0){
        d += 360;
    }
    this->direc = (int)(d * 100);
}

/**
 * @brief PointEntity::setDire
 * @param lastPoint 上一个坐标点
 * @param startPoint    当前坐标点
 * @return 静态方法， 获取两坐标点的偏移量
 */
double PointEntity::setDire(const PointEntity lastPoint, const PointEntity startPoint)
{
    double result = -1;
     result = atan2(startPoint.y - lastPoint.y,  startPoint.x - lastPoint.x)/3.1415926*180;
     if (result < 0){
         result += 360;
     }
     return int(result * 100);
}

/**
 * @brief PointEntity::toString
 * @return 以字符串的形式返回当前坐标的数据
 */
QString PointEntity::toString()
{
    QString str;
    str.append(QString::number(x)).append(" ").append(QString::number(y));
    return str;
}

/**
 * @brief PointEntity::copy
 * @param point
 * @return 返回拷贝后的坐标点对象
 */
PointEntity PointEntity::copy(PointEntity point){
    PointEntity p;
    p.x = point.x;
    p.y = point.y;
    p.direc = point.direc;
    return p;
}

int PointEntity::getDegree(PointEntity vertexPoint, PointEntity point1, PointEntity point2){
    return PointEntity::getDegree(vertexPoint.x, vertexPoint.y, point1.x, point1.y, point2.x, point2.y);
}

double PointEntity::getDiff(const PointEntity& point)
{
    double d = fabs(this->direc - point.direc);
    if (d > 18000){
        d = 36000 - d;
    }
    return d;
}

/**
 *
 * @param vertexPointX -- 角度对应顶点X坐标值
 * @param vertexPointY -- 角度对应顶点Y坐标值
 * @param point0X
 * @param point0Y
 * @param point1X
 * @param point1Y
 * @return
 */
int PointEntity::getDegree(int vertexPointX, int vertexPointY, int point0X, int point0Y, int point1X, int point1Y) {
    //向量的点乘
    int vector = (point0X - vertexPointX) * (point1X - vertexPointX) + (point0Y - vertexPointY) * (point1Y - vertexPointY);
    //向量的模乘
    double sq = sqrt(
            (abs((point0X - vertexPointX) * (point0X - vertexPointX)) + abs((point0Y - vertexPointY) * (point0Y - vertexPointY)))
                    * (abs((point1X - vertexPointX) * (point1X - vertexPointX)) + abs((point1Y - vertexPointY) * (point1Y - vertexPointY)))
    );
    //反余弦计算弧度
    double radian = acos(vector / sq);
    //弧度转角度制
    return int(180 * radian / 3.14159265358979323846);
}
