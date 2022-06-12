/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "fileutil.h"
#include <QTextStream>

FileUtil::FileUtil()
{

}

bool FileUtil::writeFile(QString filePath, QString text)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Append)){
        return false;
    }
    QTextStream streamFileOut(&file);
    streamFileOut << text;
    streamFileOut.flush();
    file.close();
    return true;
}

QString FileUtil::strToBase64(QString str)
{
    QByteArray ba;
    ba=str.toUtf8();           //QByteArray
    ba=ba.toBase64();          //Base64
    char * cx=ba.data();       //char *
    QString b64qs1=QString(cx);//QString
    return b64qs1;
}

QString FileUtil::base64ToStr(QString base)
{
    QByteArray ba;
    std::string stdStr = base.toStdString();//std::string
    ba=QByteArray(stdStr.c_str() );           //QByteArray
    ba=ba.fromBase64(ba);                     //unBase64
    QString str = QString::fromUtf8(ba);        //QString
    return  str;
}
