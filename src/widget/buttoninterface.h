/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef BUTTONINTERFACE_H
#define BUTTONINTERFACE_H

class ButtonInterface
{

public:
    int getId();
    int getType();

protected:
    explicit ButtonInterface(int id = 0, int type = 0);

protected:
    int mId;
    int mType;
};

#endif // BUTTONINTERFACE_H
