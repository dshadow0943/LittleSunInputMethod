#include "handwritetreemodel.h"
#include <fstream>
#include <cmath>
#include <regex>
#include <string>
#include <QFile>
#include <QDebug>

HandwriteTreeModel::HandwriteTreeModel()
{

}

/**
 * @brief HandWriteModel::loadModelFileNew
 * @param filePath 文件路径
 * @param charType 读取类型
 * @return
 * 读取文件
 */
bool HandwriteTreeModel::loadModelFile(const char* filePath, int charType)
{
    QFile ifs(filePath);

    if(!ifs.open(QIODevice::ReadOnly)){
        perror("open");
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
                    point.leaf = d.toInt()%10;
                    point.direc = d.toInt()/10;
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

/**
 * @brief HandWriteModel::recognize
 * @param character   //待匹配字
 * @param resultWords //字储存位置
 * @return
 * 字匹配入口
 */
bool HandwriteTreeModel::recognize(CharacterEntity& character, QStringList* resultWords)
{
    if(character.strokeCount == 0)
        return false;
    getTurnPoints(&character);
    qDebug() << character.toDireString();
    QList<WordEntity> words;

    QList<CharacterItem>* cItems;
    if (!character.isNum){
        cItems = &charItems;
    } else {
        cItems = &numItems;
    }

    //循环匹配
    for(unsigned int i = 0; i < cItems->size(); ++i){
        int mdist = 100000;
        for (int j = 0; j < cItems->at(i).charItem.size(); ++j){
            CharacterEntity tmpCharacter = cItems->at(i).charItem[j];
            int d = distCharacter(&character, &tmpCharacter);
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
    for(unsigned int i = 0; i < words.size() && i < 10; ++i){
        WordEntity word = words[i];
        qDebug() << word.word << " dist: " << word.dist;
        resultWords->push_back(word.word);
    }
    return true;
}

/**
 * @brief HandWriteModel::dist
 * @param character1
 * @param character2
 * @return 差异值
 * 获取两字之间的差异值
 */
double HandwriteTreeModel::distCharacter(CharacterEntity* character1, CharacterEntity* character2)
{
    double dist = MAXDIST;
    if(character2->strokeCount >= character1->strokeCount && character2->strokeCount <= character1->strokeCount + 2){
        double allStrokeDist = 0.0f;
//        qDebug() << "ch1: " << character1->word << " ch2: " << character2->word;
//        qDebug() << character1->toDireString();
//        qDebug() << character2->toDireString();
        for(int i = 0; i < character1->strokeCount; ++i){
            StrokeEntity stroke1 = character1->strokes[i];
            StrokeEntity stroke2 = character2->strokes[i];
            double strokeDist = distStrokes(stroke1, stroke2);
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

double HandwriteTreeModel::distStrokes(StrokeEntity& stroke1, StrokeEntity& stroke2)
{
    double strokeDist = 100000;
    double dist = 0.0f;

    dist += stroke1.points[0].getDiff(stroke2.points[0]);
    dist += stroke1.points[stroke1.points.size()-1].getDiff(stroke2.points[stroke2.points.size()-1]);

    if (stroke1.points.size() == 2) {
        for (int i = 1; i < stroke2.points.size() - 1; i++){
            dist += stroke2.points[i].getDiff(stroke2.points[i-1]);
        }
    } else if(stroke2.points.size() == 2) {
        for (int i = 1; i < stroke1.points.size() - 1; i++){
            dist += stroke1.points[i].getDiff(stroke1.points[i-1]);
        }
    } else {
        std::vector<int> stack1, stack2;
        int index1 = 1, index2 = 1;
        while (index1 < stroke1.points.size() - 1 && index2 < stroke2.points.size()) {
//            qDebug() << "index1: " << index1 << "  index2: " << index2;
            dist += stroke1.points[index1].getDiff(stroke2.points[index2]);
            stack1.push_back(index1);
            stack2.push_back(index2);

            if (stroke1.points.at(index1).leaf % 2 == 1 && stroke2.points.at(index2).leaf % 2 == 1){
                index1++;
                index2++;
            } else {
                if (stroke1.points.at(index1).leaf % 2 == 1) {
                    dist += distTail(stroke1, index1);
                } else if (stroke2.points.at(index2).leaf % 2 == 1) {
                    dist += distTail(stroke2, index2);
                }
//                qDebug() << "L index1: " << index1 << "  index2: " << index2;
                while (stack1.size() > 0 && stack2.size() > 0) {
                    int p1 = stack1[stack1.size()-1];
                    int p2 = stack2[stack2.size()-1];
                    stack1.pop_back();
                    stack2.pop_back();
                    if (stroke1.points.at(p1).leaf >= 2 && stroke2.points.at(p2).leaf >= 2) {
                        break;
                    }
                    if (stroke1.points.at(p1).leaf >= 2){
                        dist += distTail(stroke1, index1);
                    } else if (stroke2.points.at(p2).leaf >= 2) {
                        dist += distTail(stroke2, index2);
                    }
                }
//                qDebug() << "R index1: " << index1 << "  index2: " << index2;
                index1++;
                index2++;
            }

        }
    }
    //收缩差异值
    strokeDist = dist / stroke1.points.size();
    return strokeDist;

}


double HandwriteTreeModel::distTail(StrokeEntity& stroke, int& index)
{
    double dist = 0;
    int count = 1;
    int i = index;
    while (count > 0) {
        index++;
        count--;
        count += stroke.points.at(index).leaf/2 + stroke.points.at(index).leaf % 2;
        dist += stroke.points[index].getDiff(stroke.points[index-1]);
    }
    return dist;
}

/**
 * @brief HandWriteModel::getTurnPoints
 * @param character
 * 获取特征点
 */
void HandwriteTreeModel::getTurnPoints(CharacterEntity* character)
{
    for(int i = 0; i < character->strokeCount; ++i){
         StrokeEntity *stroke = &character->strokes[i];
         if(stroke->points.size() > 0){
             std::vector<PointEntity> points;
             stroke->points[0].direc = 0;
             if (i != 0){
                 stroke->points[0].setDire(character->strokes.at(i - 1).points[0]);
             }
             points.push_back(stroke->points[0]);
             turnPoints(stroke, &points, 0, (int)stroke->points.size() - 1, stroke->points[0]);
             if (stroke->points[stroke->points.size()-1].direc == -1) {
                 stroke->points[stroke->points.size()-1].setDire(points.at(points.size()-1));
             }
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
int HandwriteTreeModel::turnPoints(StrokeEntity *stroke, std::vector<PointEntity> *points, int start, int end, const PointEntity& point)
{
    if(start < 0 || end <= 0 || start >= end - 1)
        return 0;
    const float b = stroke->points[start].x - stroke->points[end].x;
    const float a = stroke->points[end].y - stroke->points[start].y;
    const float c = stroke->points[start].x * a + stroke->points[start].y * b;
    float len = sqrt(a*a + b*b)/2;
    float max = 0.17632698;    //tan(10°)
    int maxDistPointIndex = -1;
    for(int i = start + 1; i < end && len > 2; ++i){
        PointEntity p = stroke->points[i];
        float h = abs(a * p.x + b * p.y - c)/sqrt(a*a + b*b);
        const float dist = h/len;
        if (dist > max) {
            max = dist;
            maxDistPointIndex = i;
        }
    }
    if(maxDistPointIndex != -1){
        points->push_back(stroke->points[maxDistPointIndex]);
        int i = points->size()-1;
        int ret = 0;
        ret += turnPoints(stroke, points, start, maxDistPointIndex, point);
        if (ret == 0){
            points->at(i).setDire(point);
        } else {
            points->at(i).setDire(points->at(points->size()-1));
        }
        ret += turnPoints(stroke, points, maxDistPointIndex, end, stroke->points[maxDistPointIndex]) * 2;
        if (ret == 1){
            points->at(i).setDire(stroke->points[maxDistPointIndex]);
        }
        points->at(i).leaf = ret;
        return 1;
    }
    return 0;
}
