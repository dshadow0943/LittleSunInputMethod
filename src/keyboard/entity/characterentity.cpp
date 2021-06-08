#include "characterentity.h"

CharacterEntity::CharacterEntity()
{
    clear();
}

void CharacterEntity::initSize(int tmpWidth, int tmpHeight){
}

bool CharacterEntity::addPoint(int strokeId, double x, double y){
    if(strokeId < 0)
        return false;
    if(strokeId != lastStrokeId){
        lastStrokeId = strokeId;
        strokeCount++;
        StrokeEntity stroke;
        strokes.push_back(stroke);
    }
    PointEntity point(x, y);
    strokes[strokeCount - 1].points.push_back(point);
    return true;
}

void CharacterEntity::clear(){
    strokeCount = 0;
    lastStrokeId = -1;
    strokes.clear();
}

/**
 * @brief CharacterEntity::toString
 * @return 返回这个字的所有坐标点字符串
 */
QString CharacterEntity::toString()
{
    QString str;
    str.append(word);
    for (int i = 0; i < strokes.size(); ++i){
        str.append("|");
        for (int j = 0; j < strokes.at(i).points.size(); ++j){
            if (j > 0){
                str.append(",");
            }
            str.append(strokes[i].points[j].toString());
        }
    }
    return str;
}

/**
 * @brief CharacterEntity::toDireString
 * @return 返回这个字的所有坐标偏移量字符串
 */
QString CharacterEntity::toDireString(){
    QString str;
    for (int i = 0; i < strokes.size(); ++i){
        if (i != 0){
            str.append("|");
        }
        for (int j = 0; j < strokes.at(i).points.size(); ++j){
            if (j != 0){
                str.append(",");
            }
            str.append(QString::number(strokes.at(i).points.at(j).direc));
        }
    }
    return str;
}
