/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "buttoninterface.h"

ButtonInterface::ButtonInterface(int id, int type)
{
    this->mId = id;
    this->mType = type;
}

int ButtonInterface::getId()
{
    return this->mId;
}

int ButtonInterface::getType()
{
    return this->mType;
}
