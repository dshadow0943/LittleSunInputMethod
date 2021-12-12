#ifndef HANDWRITETREEMODEL_H
#define HANDWRITETREEMODEL_H

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

class HandwriteTreeModel
{
public:
    HandwriteTreeModel();

    bool loadModelFile(const QString filePath, int charType = CHAR_CHINESE);
    bool recognize(CharacterEntity& ch, QStringList *resultWords);
    bool wirteFile(const QString& filePath);
    int megerCharacter(QList<CharacterEntity>&);
    static void getTurnPoints(CharacterEntity* character);
    static int turnPoints(StrokeEntity *stroke, std::vector<PointEntity> *points, int start, int end, const PointEntity& point);

private:
    QList<CharacterItem> charItems;
    QList<CharacterItem> numItems;
    double distCharacter(CharacterEntity* character1, CharacterEntity* character2);

    void norm(CharacterEntity* character);

    static double distStrokes(StrokeEntity& stroke1, StrokeEntity& stroke2);
    static double distTail(StrokeEntity& stroke, int& index);
};

#endif // HANDWRITETREEMODEL_H
