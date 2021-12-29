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
#ifndef GLOBALSIGNALTRANSFER_H
#define GLOBALSIGNALTRANSFER_H

#include <QObject>

class WindowBase;
class KeyButtonBase;
class RadioButtonBase;
class GlobalSignalTransfer : public QObject
{
    Q_OBJECT

public:
    static GlobalSignalTransfer* getInstance();

protected:
    explicit GlobalSignalTransfer(QObject *parent = nullptr);

signals:
    void sendKeyButtonClicked(KeyButtonBase* but);
    void sendRadioButtonClicked(RadioButtonBase* but);
    void sendWindowClosed(int id);

//限制槽访问权限（避免全局滥用情况）
private slots:
    void onKeyButtonClicked(KeyButtonBase* but);
    void onRadioButtonClicked(RadioButtonBase* but);
    void onWindowClosed(int id);


    friend WindowBase;
    friend KeyButtonBase;
    friend RadioButtonBase;
};

#endif // GLOBALSIGNALTRANSFER_H
