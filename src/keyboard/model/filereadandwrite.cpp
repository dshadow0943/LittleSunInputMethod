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
    streamFileOut << text;
    streamFileOut.flush();
    file.close();

    return true;
}
