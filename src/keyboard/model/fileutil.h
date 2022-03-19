/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef FILEREADANDWRITE_H
#define FILEREADANDWRITE_H

#include <QString>
#include <QFile>
#include "characteritem.h"

class FileUtil
{
public:
    FileUtil();

    static bool writeFile(QString filePath, QString text);
    static bool readPointFile(QString filePath, QList<CharacterEntity>* Characters);
    static QString strToBase64(QString str);
    static QString base64ToStr(QString base);

};

#endif // FILEREADANDWRITE_H
