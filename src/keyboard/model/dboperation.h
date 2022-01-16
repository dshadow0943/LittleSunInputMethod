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
#ifndef XYDATABASEOPERATION_H
#define XYDATABASEOPERATION_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>

#define CONNECTIONNAME "LittleSunDB"

class PhraseEntity;
class DBOperation : public QObject
{
    Q_OBJECT
public:
    static DBOperation *getInstance();
    explicit DBOperation(QObject *parent = nullptr);
    ~DBOperation();

    enum PuncType {
        User = 1,
        Chinese,
        English,
        Math,
    };

    bool createDatabaseFile(const QString &filePath, const QString &passwd = "", bool fource = false);
    bool openDatabaseFile(const QString &filePath, const QString &passwd = "");

    bool createInputTable();
    bool insertData(PhraseEntity item, const QString &table);
    bool insertData(const QList<PhraseEntity > &list, const QString &table);
    bool delItem(PhraseEntity item);
    QList<PhraseEntity > findData(const QString &key,
                                      const QString &number,
                                      const QString &table,
                                      bool &haveFind, int max = 200);

    bool findPinyinByChinese(const QString& chinese, QString& pinyin);
    QList<PhraseEntity> findAssociational(const QString& table, const QString& head);
    QString findPunc(PuncType type);

private:
    static DBOperation *DB;

};

#define XYDB DBOperation::getInstance()
#endif // XYDATABASEOPERATION_H
