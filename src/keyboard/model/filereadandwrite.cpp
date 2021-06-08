#include "filereadandwrite.h"
#include <QTextStream>

FileReadAndWrite::FileReadAndWrite()
{

}

bool FileReadAndWrite::writeFile(QString filePath, QString text)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Append)){
        perror("open");
        return false;
    }
    QTextStream streamFileOut(&file);
    streamFileOut.setCodec("GBK");
    streamFileOut << text;
    streamFileOut.flush();
    file.close();

    return true;
}

bool FileReadAndWrite::readPointFile(QString filePath, QList<CharacterEntity>* Characters)
{
    QFile ifs(filePath);

    if(!ifs.open(QIODevice::ReadOnly)){
        perror("open");
        return false;
    }
    QTextStream in(&ifs);
    in.setCodec("GBK");     //以GBK的编码读取字符串

    while(!ifs.atEnd()){

        QString line = ifs.readLine();
        if (line.length() == 0){
            continue;
        }
//        qDebug() << line;
//        CharacterItem charItem;
        QStringList chs = line.split(":");
//        charItem.word = chs[0];
        for (int i = 1; i < chs.size(); ++i){
            CharacterEntity character;
            character.strokeCount = 0;
            QStringList strokeList = chs[i].split("|");
//            character.text = strokeList[0];
    //        qDebug() << character.text;
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
//            charItem.charItem.push_back(character);
        }
//        qDebug() << charItem.toDireString();
//        charItems.push_back(charItem);
    }
    return true;

}
