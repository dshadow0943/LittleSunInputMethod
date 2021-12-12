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
#include "scrollbarmanage.h"

ScrollBarManage::ScrollBarManage() : QObject ()
{

}

ScrollBarManage* ScrollBarManage::getInstace()
{
    static ScrollBarManage bar;
    return &bar;
}

void ScrollBarManage::setCanditeData(QStringList& data)
{
    getHCanditateView()->setData(data);
    getVCanditateView()->setData(data);
}

VScrollBarView* ScrollBarManage::getVCanditateView()
{
    static VScrollBarView view;
    return &view;
}

HScrollBarView* ScrollBarManage::getHCanditateView()
{
    static HScrollBarView view;
    return &view;
}

VScrollBarView* ScrollBarManage::getVSrcllBarView(QWidget *parent)
{
    return new VScrollBarView(parent);
}

HScrollBarView* ScrollBarManage::getHSrcllBarView(QWidget *parent)
{
    return new HScrollBarView(parent);
}
