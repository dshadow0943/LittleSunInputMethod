﻿/*
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
#include "dboperation.h"
#include "phraseentity.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QVariant>
#include <QDebug>

DBOperation *DBOperation::DB = nullptr;
DBOperation *DBOperation::getInstance()
{
    if (DB == nullptr)
    {
        DB = new DBOperation;
    }
    return DB;
}

DBOperation::DBOperation(QObject *parent)
    : QObject(parent)
{

}

DBOperation::~DBOperation()
{

}

bool DBOperation::createDatabaseFile(const QString &filePath, const QString &passwd, bool fource)
{
    if (QFile::exists(filePath)) // 文件存在
    {
        if (fource)
        {
            if (!QFile::remove(filePath)) // 删除失败也返回错误
            {
                return false;
            }
        }
        else    // 不强制创建返回错误
        {
            return false;
        }
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", CONNECTIONNAME);
    db.setDatabaseName(filePath);
    db.setPassword(passwd);
    db.setConnectOptions("QSQLITE_CREATE_KEY");
    return db.open();
}

bool DBOperation::openDatabaseFile(const QString &filePath, const QString &passwd)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains(CONNECTIONNAME)){
        db = QSqlDatabase::database(CONNECTIONNAME);
        if(db.isOpen()){
            return true;
        }
        db.setDatabaseName(filePath);
        db.setPassword(passwd);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE", CONNECTIONNAME);
        db.setDatabaseName(filePath);
        db.setPassword(passwd);
        db.setConnectOptions("QSQLITE_CREATE_KEY");
    }

    bool ret = db.open();
    db.close();

    return ret;
}

bool DBOperation::createInputTable()
{

    QSqlQuery query(QSqlDatabase::database(CONNECTIONNAME));

    // 单字表
    bool ok = query.exec("CREATE TABLE IF NOT EXISTS  singlePinyin ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "pinyin VARCHAR NOT NULL,"
                         "chinese VARCHAR NOT NULL,"
                         "extra VARCHAR NULL,"
                         "times INTEGER NOT NULL,"
                         "stick BOOL NULL);");
    if (!ok)
    {
        qDebug("error: %s", query.lastError().text().toUtf8().data());
        return false;
    }

    // 基础表
    for (int i = 'A'; i <= 'Z'; ++i)
    {
        ok = query.exec(QString("CREATE TABLE IF NOT EXISTS  basePinyin_%1 ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "pinyin VARCHAR NOT NULL,"
                        "chinese VARCHAR NOT NULL,"
                        "extra VARCHAR NULL,"
                        "times INTEGER NOT NULL,"
                        "stick BOOL NULL);").arg(QChar(i)));
        if (!ok)
        {
            qDebug("error: %s", query.lastError().text().toUtf8().data());
            return false;
        }
    }

    // 用户表
    ok = query.exec("CREATE TABLE IF NOT EXISTS  userPinyin ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "pinyin VARCHAR NOT NULL,"
                    "chinese VARCHAR NOT NULL,"
                    "extra VARCHAR NULL,"
                    "times INTEGER NOT NULL,"
                    "stick BOOL NULL);");
    if (!ok)
    {
        qDebug("error: %s", query.lastError().text().toUtf8().data());
        return false;
    }

    // 英文表
    ok = query.exec("CREATE TABLE IF NOT EXISTS  englishTable ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "english VARCHAR NOT NULL,"
                    "translate VARCHAR NOT NULL,"
                    "extra VARCHAR NULL,"
                    "times INTEGER NOT NULL,"
                    "stick BOOL NULL);");
    if (!ok)
    {
        qDebug("error: %s", query.lastError().text().toUtf8().data());
        return false;
    }

    // 英文用户表
    ok = query.exec("CREATE TABLE IF NOT EXISTS  userEnglishTable ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "english VARCHAR NOT NULL,"
                    "translate VARCHAR NOT NULL,"
                    "extra VARCHAR NULL,"
                    "times INTEGER NOT NULL,"
                    "stick BOOL NULL);");
    if (!ok)
    {
        qDebug("error: %s", query.lastError().text().toUtf8().data());
        return false;
    }
    return ok;
}

bool DBOperation::insertData(PhraseEntity item, const QString &table)
{
    QString field1, field2;
    if (table.toLower().contains("english"))
    {
        field1 = "english";
        field2 = "translate";
    }
    else
    {
        field1 = "pinyin";
        field2 = "chinese";
    }

    QSqlQuery query(QSqlDatabase::database(CONNECTIONNAME));
    bool ok = true;

    query.prepare(QString("INSERT INTO %1 (id, %2, %3, extra, times, stick) "
                              "VALUES (:id, :%4, :%5, :extra, :times, :stick);")
                      .arg(table)
                      .arg(field1)
                      .arg(field2)
                      .arg(field1)
                      .arg(field2));
        query.bindValue(QString(":%1").arg(field1), item.mCompletePinyin);
        query.bindValue(QString(":%1").arg(field2), item.mPhrase);
        query.bindValue(":extra", item.mExtra);
        query.bindValue(":times", item.mTimes);
        query.bindValue(":stick", item.mStick);
        ok = query.exec();

    if (!ok)
    {
        qDebug("error: %s", query.lastError().text().toUtf8().data());
    }
    return ok;
}

/**
 * @brief XYDatabaseOperation::insertData
 * 插入数据
 * @param list
 * @param table
 * @return
 */
bool DBOperation::insertData(const QList<PhraseEntity > &list, const QString &table)
{
    QString field1, field2;
    if (table.toLower().contains("english"))
    {
        field1 = "english";
        field2 = "translate";
    }
    else
    {
        field1 = "pinyin";
        field2 = "chinese";
    }
    QSqlDatabase::database(CONNECTIONNAME).transaction();   //开始一个事务
    QSqlQuery query(QSqlDatabase::database(CONNECTIONNAME));
    bool ok = true;
    for (int i = 0; i < list.size(); ++i)
    {
        query.prepare(QString("INSERT INTO %1 (id, %2, %3, extra, times, stick) "
                              "VALUES (:id, :%4, :%5, :extra, :times, :stick);")
                      .arg(table)
                      .arg(field1)
                      .arg(field2)
                      .arg(field1)
                      .arg(field2));
        query.bindValue(QString(":%1").arg(field1), list.at(i).mCompletePinyin);
        query.bindValue(QString(":%1").arg(field2), list.at(i).mPhrase);
        query.bindValue(":extra", list.at(i).mExtra);
        query.bindValue(":times", list.at(i).mTimes);
        query.bindValue(":stick", list.at(i).mStick);
        ok = query.exec();
        if (!ok)
        {
            qDebug("error: %s", query.lastError().text().toUtf8().data());
            break;
        }
    }
    if (ok)
    {
        QSqlDatabase::database(CONNECTIONNAME).commit();
    }
    else
    {
        QSqlDatabase::database(CONNECTIONNAME).rollback();
    }
    return ok;
}

/**
 * @brief XYDatabaseOperation::delItem
 * 删除词组数据
 * @param item
 * @return
 */
bool DBOperation::delItem(PhraseEntity item)
{
    QSqlQuery query(QSqlDatabase::database(CONNECTIONNAME));
    if (item.mSource == "singlePinyin") // 理论上基础的几个表内容都不能删除，这里只不准删除单字的表
    {
        qDebug("Can't delete item in singlePinyin!");
        return false;
    }
    bool ok = query.exec(QString("DELETE FROM %1 WHERE id = %2;")
                         .arg(item.mSource)
                         .arg(item.mID));
    if (!ok)
    {
        qDebug("error: %s", query.lastError().text().toUtf8().data());
    }
    return ok;
}

/**
 * @brief XYDatabaseOperation::findData
 * 检索词组
 * @param key
 * @param number
 * @param table
 * @param haveFind
 * @param max
 * @return
 */
QList<PhraseEntity > DBOperation::findData(const QString &key, const QString &number,
                                                      const QString &table, bool& haveFind, int max)
{
    static bool comein = false;
    QList<PhraseEntity > list;
    if (haveFind)
    {
        haveFind = false;
    }
    if (comein)
    {
        return list;
    }
    else
    {
        comein = true;
    }

    QString table_fact = table;
    if (table_fact == "basePinyin" && !key.isEmpty())
    {
        if (!key.at(0).isLetter() || number.toInt() > 6) // 如果都不以字母开头或者超过6个字查找，肯定找不到，直接返回
        {
            comein = false;
            haveFind = true;
            return list;
        }
        else
        {
            table_fact += QString("_%1").arg(key.at(0).toUpper());
        }
    }
    QString field1, field2;
    if (table.toLower().contains("english"))
    {
        field1 = "english";
        field2 = "translate";
    }
    else
    {
        field1 = "pinyin";
        field2 = "chinese";
    }
    QSqlQuery query(QSqlDatabase::database(CONNECTIONNAME));
    bool ok = query.exec(QString("SELECT id, %1, %2, extra, times, stick FROM %3 "
                       "WHERE %4 like \"%5\" AND extra like \"%6\" "
                       "ORDER BY times DESC LIMIT 0,%7;")
               .arg(field1)
               .arg(field2)
               .arg(table_fact)
               .arg(field1)
               .arg(key)
               .arg(number)
               .arg(max));

    if (!ok)
    {
        qCritical("error: %s", query.lastError().text().toUtf8().data());
    }

    while (query.next())
    {
        list.append(PhraseEntity(table_fact,
                                        query.value(2).toString().trimmed(),
                                        query.value(1).toString().trimmed(),
                                        query.value(3).toString().trimmed(),
                                        query.value(0).toInt(),
                                        query.value(4).toInt(),
                                        query.value(5).toBool()));
    }

    comein = false;
    haveFind = true;
    return list;
}

bool DBOperation::findPinyinByChinese(const QString& chinese, QString& pinyin)
{
    QSqlQuery query(QSqlDatabase::database(CONNECTIONNAME));
    bool ok = query.exec(QString("SELECT pinyin FROM singlePinyin "
                                 "WHERE chinese like \"%1\";")
                         .arg(chinese));
    if (!ok)
    {
        qCritical("error: %s", query.lastError().text().toUtf8().data());
    }
    if (query.next()) {
        qInfo() << query.value(0).toString().trimmed();
        pinyin = query.value(0).toString().trimmed();
        return true;
    }
    return false;
}

QList<PhraseEntity> DBOperation::findAssociational(const QString& table, const QString& head)
{
    QSqlQuery query(QSqlDatabase::database(CONNECTIONNAME));
    bool ok = query.exec(QString("SELECT id, pinyin, chinese, extra, times, stick FROM %1 "
                       "WHERE chinese like \"%2\" "
                       "ORDER BY times DESC;")
               .arg(table)
               .arg(head));
    if (!ok)
    {
        qCritical("error: %s", query.lastError().text().toUtf8().data());
    }

    QList<PhraseEntity > list;

    while (query.next())
    {
        list.append(PhraseEntity(table,
                                        query.value(2).toString().trimmed(),
                                        query.value(1).toString().trimmed(),
                                        query.value(3).toString().trimmed(),
                                        query.value(0).toInt(),
                                        query.value(4).toInt(),
                                        query.value(5).toBool()));
    }
    return list;
}

QString DBOperation::findPunc(PuncType type)
{
    QSqlQuery query(QSqlDatabase::database(CONNECTIONNAME));
    QString pType = "";
    switch (type) {
    case User: pType = "user";
        break;
    case Chinese: pType = "chinese";
        break;
    case English: pType = "english";
        break;
    case Math: pType = "math";
        break;
    }
    bool ok = query.exec(QString("SELECT punc FROM basePunc "
                       "WHERE type = \'%1\';")
               .arg(pType));
    if (!ok)
    {
        qCritical("error: %s", query.lastError().text().toUtf8().data());
    }
    if (query.next()) {
        return query.value(0).toString().trimmed();
    }
    return "";
}

