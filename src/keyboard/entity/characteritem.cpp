#include "characteritem.h"
#include <qlist.h>


CharacterItem::CharacterItem()
{



}

/**
 * @brief CharacterItem::toString
 * @return 返回改字所有写法的坐标偏移量字符串
 */
QString CharacterItem::toString()
{
    QString str;
    str += word;
    for(CharacterEntity c : charItem){
        str += ":";
        str += c.toDireString();
    }
    return str;
}

QString CharacterItem:: toDireString(){
    QString str;
    str += word;
    for(CharacterEntity c : charItem){
        str += ":";
        str += c.toDireString();
    }
    return str;
}
