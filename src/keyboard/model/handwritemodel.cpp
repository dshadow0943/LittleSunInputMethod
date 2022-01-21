/*
* Copyright (C) 2019 ~ 2019 UnionTech Software Technology Co.,Ltd.
*
* Author:     leilong <dshadow@foxmail.com>
*
* Maintainer: leilong <dshadow@foxmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "handwritemodel.h"
#include <fstream>
#include <cmath>
#include <regex>
#include <string>
#include <QFile>
#include <QDebug>

/**
 * @brief HandWriteModel::HandWriteModel
 * 手写字匹配实现类
 */
HandWriteModel::HandWriteModel()
{

}

/**
 * @brief HandWriteModel::loadModelFileNew
 * @param filePath 文件路径
 * @param charType 读取类型
 * @return
 * 读取文件
 */
bool HandWriteModel::loadModelFile(const QString filePath, int charType)
{
    QFile ifs(filePath);

    if(!ifs.open(QIODevice::ReadOnly)){
//        perror("open");
        return false;
    }

    QList<CharacterItem>* cItems;
    if (charType == CHAR_CHINESE){
        cItems = &charItems;
    } else if (charType == CHAR_NUM){
        cItems = &numItems;
    } else {
        return  false;
    }

    while(!ifs.atEnd()){

        QString line = ifs.readLine();
        if (line.length() == 0){
            continue;
        }
        CharacterItem charItem;
        QStringList chs = line.split(":");
        charItem.word = chs[0];
        for (int i = 1; i < chs.size(); ++i){
            CharacterEntity character;
            character.strokeCount = 0;
            QStringList strokeList = chs[i].split("|");
            for (int i = 0; i < strokeList.length(); ++i){
                QStringList points = strokeList.at(i).split(",");
                StrokeEntity strocke;
                for(QString d : points){
                    PointEntity point;
                    point.direc = d.toDouble();
                    strocke.points.push_back(point);
                }
                character.strokes.push_back(strocke);
                character.strokeCount++;
            }
            charItem.charItem.push_back(character);
        }
        cItems->push_back(charItem);
    }
    return true;
}

bool HandWriteModel::wirteFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)){
        perror("open");
        return false;
    }
    QTextStream streamFileOut(&file);
    for (CharacterItem cItem : charItems){
        streamFileOut << cItem.toDireString() << '\n';
    }
    streamFileOut.flush();
    file.close();

    return true;
}

/**
 * @brief HandWriteModel::recognize
 * @param character   //待匹配字
 * @param resultWords //字储存位置
 * @return
 * 字匹配入口
 */
bool HandWriteModel::recognize(CharacterEntity& character, QStringList* resultWords)
{
    if(character.strokeCount == 0)
        return false;
    getTurnPoints(&character);
    norm(&character);
    QList<WordEntity> words;

    QList<CharacterItem>* cItems = &numItems;
    if (!character.isNum) {
        cItems = &charItems;
    }

    //循环匹配
    for(int i = 0; i < cItems->size(); ++i){
        int mdist = 100000;
        for (int j = 0; j < cItems->at(i).charItem.size(); ++j){
            CharacterEntity tmpCharacter = cItems->at(i).charItem[j];
            int d = int(dist(&character, &tmpCharacter));
            if (d >= 0 && d < mdist){
                mdist = d;
            }
        }

        WordEntity word;
        word.word = cItems->at(i).word;
        word.dist = mdist;
        if(word.dist < 100000){
            words.push_back(word);
        }
    }

    std::sort(words.begin(), words.end(), WordEntity::cmpWordDist);
    for(int i = 0; i < words.size(); ++i){
        WordEntity word = words[i];
        resultWords->push_back(word.word);
    }
    return true;
}

int HandWriteModel::megerCharacter(QList<CharacterEntity>& characters)
{
    int count = 0;
    for (CharacterEntity c : characters) {
        getTurnPoints(&c);
        qDebug() << "megerCharacter: " << c.word << c.toDireString();
        //循环匹配
        int i = 0;
        for(i = 0; i < charItems.size(); ++i){
            int mdist = 100000;
            if (c.word != charItems.at(i).word) {
                continue;
            }
            for (int j = 0; j < charItems.at(i).charItem.size(); ++j){
                CharacterEntity tmpCharacter = charItems.at(i).charItem[j];
                int d = int(dist(&c, &tmpCharacter));
                if (d >= 0 && d < mdist){
                    mdist = d;
                }
                if (mdist < 500) {
                    break;
                }
            }
            if (mdist >= 500) {
                charItems[i].charItem.push_back(c);
                count++;
            }
            break;
        }
        if (i == charItems.size()) {
            CharacterItem cItem;
            cItem.word = c.word;
            cItem.charItem.push_back(c);
            charItems.push_back(cItem);
            count ++;
        }
    }
    return count;
}

/**
 * @brief HandWriteModel::dist
 * @param character1
 * @param character2
 * @return 差异值
 * 获取两字之间的差异值
 */
double HandWriteModel::dist(const CharacterEntity* character1, const CharacterEntity* character2)
{
    double dist = MAXDIST;
    if(character2->strokeCount >= character1->strokeCount && character2->strokeCount <= character1->strokeCount + 2){
        double allStrokeDist = 0.0;
        for(int i = 0; i < character1->strokeCount; ++i){
            StrokeEntity stroke1 = character1->strokes[i];
            StrokeEntity stroke2 = character2->strokes[i];
            double strokeDist = distBetweenStrokes(stroke1, stroke2);

            allStrokeDist += strokeDist;

            if(strokeDist > MAX_DIFF_PER_STROKE){
                allStrokeDist = MAXDIST;
                return allStrokeDist;
            }
        }
        // 笔画更接近的优先级更高、对笔画数不一样的增加差异值
        return allStrokeDist / character1->strokeCount + (character2->strokeCount - character1->strokeCount)*10000/character1->strokeCount;
    }
    return dist;
}

/**
 * @brief HandWriteModel::distBetweenStrokes
 * @param stroke1
 * @param stroke2
 * @return
 * 获取笔画差异值
 */
double HandWriteModel::distBetweenStrokes(const StrokeEntity stroke1, const StrokeEntity stroke2)
{
    double strokeDist = MAXDIST;
    double dist = 0.0;
    int minLength = int(fmin(stroke1.points.size(), stroke2.points.size()));
    StrokeEntity largeStroke = stroke1.points.size() > minLength ? stroke1 : stroke2;
    StrokeEntity smallStroke = stroke1.points.size() > minLength ? stroke2 : stroke1;

    //比较minLength-1个特征点，最后一个最后比较
    for(int j = 0; j < minLength-1; ++j){
        double diretion1 = largeStroke.points[j].direc;
        double diretion2 = smallStroke.points[j].direc;
        double d = fabs(diretion1 - diretion2);
        if (d > 18000){
            d = 36000 - d;
        }
        dist += d;
    }

    //特征点数量不一致的特征点多的笔画的除倒数第一个外的后续特征点以特征点少的笔画的倒数第二个特征点作比较
    for (int j = minLength-1; j < largeStroke.points.size()-1; ++j){
        double d = fabs(largeStroke.points[j].direc - smallStroke.points[minLength-1].direc);
        if (d > 18000){
            d = 36000 - d;
        }
        dist += d;
    }

    //单独比较最后一个特征点
    double d = fabs(largeStroke.points[largeStroke.points.size()-1].direc - smallStroke.points[smallStroke.points.size()-1].direc);
    if (d > 18000){
        d = 36000 - d;
    }
    dist += d;
    //收缩差异值
    strokeDist = dist / minLength;
    return strokeDist;
}

/**
 * @brief HandWriteModel::getTurnPoints
 * @param character
 * 获取特征点
 */
void HandWriteModel::getTurnPoints(CharacterEntity* character)
{
    for(int i = 0; i < character->strokeCount; ++i){
         StrokeEntity *stroke = &character->strokes[i];
         if(stroke->points.size() > 1){
             std::vector<PointEntity> points;
             points.push_back(stroke->points[0]);
             turnPoints(stroke, &points, 0, stroke->points.size() - 1);
             points.push_back(stroke->points[stroke->points.size() - 1]);
             stroke->points.clear();
             for(unsigned int i = 0; i < points.size(); ++i){
                 stroke->points.push_back(points[i]);
             }
         }
     }
}

/**
 * @brief HandWriteModel::turnPoints
 * @param stroke
 * @param points
 * @param pointIndex1
 * @param pointIndex2
 * 递归获取特征点
 */
void HandWriteModel::turnPoints(StrokeEntity *stroke, std::vector<PointEntity> *points, int pointIndex1, int pointIndex2)
{
    if(pointIndex1 < 0 || pointIndex2 <= 0 || pointIndex1 >= pointIndex2 - 1)
        return;
    const double b = stroke->points[pointIndex1].x - stroke->points[pointIndex2].x;
    const double a = stroke->points[pointIndex2].y - stroke->points[pointIndex1].y;
    const double c = stroke->points[pointIndex1].x * a + stroke->points[pointIndex1].y * b;
    double len = sqrt(a*a + b*b)/2;
    double max = 0.17632698;    //tan(10°)
    int maxDistPointIndex = -1;
    for(int i = pointIndex1 + 1; i < pointIndex2 && len > 2; ++i){
        PointEntity point = stroke->points[i];
        double h = abs(a * point.x + b * point.y - c)/sqrt(a*a + b*b);
        const double dist = h/len;
        if (dist > max) {
            max = dist;
            maxDistPointIndex = i;
        }
    }
    if(maxDistPointIndex != -1){
        turnPoints(stroke, points, pointIndex1, maxDistPointIndex);
        points->push_back(stroke->points[maxDistPointIndex]);
        turnPoints(stroke, points, maxDistPointIndex, pointIndex2);
    }
}

/**
 * @brief HandWriteModel::norm
 * @param character
 * 获取特征点值
 */
void HandWriteModel::norm(CharacterEntity* character)
{
    PointEntity lastPoint(-1, -1);
    PointEntity lastStrick(-1, -1);
    for(int i = 0; i < character->strokes.size(); ++i){
        StrokeEntity stroke = character->strokes[i];
        PointEntity tmpPoint(-1, -1);
        for(int j = 0; j < stroke.points.size(); ++j){
            tmpPoint = stroke.points[j];
            if (lastPoint.x == -1 && lastPoint.y == -1){
                character->strokes[i].points[j].direc = 0;

            } else {
                character->strokes[i].points[j].setDire(lastPoint);
            }
            lastPoint = tmpPoint;
        }
        PointEntity point;
        if (i == 0){
            point.direc = 0;
        } else {
            point.direc = PointEntity::setDire(character->strokes[i-1].points[0], character->strokes[i].points[0]);
        }
        lastStrick = lastPoint;
        character->strokes[i].points.push_back(point);
    }
}
