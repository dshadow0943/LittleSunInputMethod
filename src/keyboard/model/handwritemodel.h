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
#ifndef HANDWRITEMODEL_H
#define HANDWRITEMODEL_H

#include "characteritem.h"
#include "characterentity.h"
#include "wordentity.h"
#include <qlist.h>

#define MAXDIST 100000
#define MAX_DIFF_PER_STROKE 35000
//#define VERTICAL 1001
//#define HORIZONTAL 1002

#define CHAR_CHINESE 0
#define CHAR_NUM 1

class HandWriteModel
{
public:
    HandWriteModel();

    bool loadModelFile(const QString filePath, int charType = CHAR_CHINESE);
    bool recognize(CharacterEntity& ch, QStringList *resultWords);
    bool wirteFile(const QString& filePath);
    int megerCharacter(QList<CharacterEntity>&);
    static void getTurnPoints(CharacterEntity* character);
    static void turnPoints(StrokeEntity *stroke, std::vector<PointEntity> *points, int pointIndex1, int pointIndex2);

private:
    QList<CharacterItem> charItems;
    QList<CharacterItem> numItems;
    double dist(const CharacterEntity* character1, const CharacterEntity* character2);
    double distBetweenStrokes(const StrokeEntity stroke1, const StrokeEntity stroke2);

    void norm(CharacterEntity* character);

};

#endif // HANDWRITEMODEL_H
