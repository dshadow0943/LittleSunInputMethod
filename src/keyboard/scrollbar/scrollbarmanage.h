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
#ifndef SCROLLBARMANAGE_H
#define SCROLLBARMANAGE_H

#include <vscrollbarview.h>
#include <hscrollbarview.h>

class ScrollBarManage : QObject
{
    Q_OBJECT
public:
    explicit ScrollBarManage();

    static ScrollBarManage* getInstace();
    static VScrollBarView* getVCanditateView();
    static HScrollBarView* getHCanditateView();
    static VScrollBarView* getVSrcllBarView(ScrollBarBase::ViewType type = ScrollBarBase::Invavid, QWidget *parent = nullptr);
    static HScrollBarView* getHSrcllBarView(ScrollBarBase::ViewType type = ScrollBarBase::Invavid, QWidget *parent = nullptr);

    void setCanditeData(QStringList& data);

signals:

public slots:

private:


};

#endif // SCROLLBARMANAGE_H
