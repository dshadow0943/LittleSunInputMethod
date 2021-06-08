#ifndef FILEREADANDWRITE_H
#define FILEREADANDWRITE_H

#include <QString>
#include <QFile>
#include "characteritem.h"

class FileReadAndWrite
{
public:
    FileReadAndWrite();

    static bool writeFile(QString filePath, QString text);
    static bool readPointFile(QString filePath, QList<CharacterEntity>* Characters);

};

#endif // FILEREADANDWRITE_H
