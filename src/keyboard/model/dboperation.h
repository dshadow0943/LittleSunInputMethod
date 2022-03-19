/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef XYDATABASEOPERATION_H
#define XYDATABASEOPERATION_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include <QMutex>
#include <QThread>

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
    bool initDatabaseFile(const QString &filePath, const QString &passwd = "");
    QSqlDatabase openDatabaseFile(const QString& connectionName);

    bool createInputTable();
    bool insertData(PhraseEntity item, const QString &table);
    bool insertData(const QList<PhraseEntity > &list, const QString &table);

    bool updatePunc(QString& data, QStringList& ret, PuncType type);

    bool delItem(PhraseEntity item);
    QList<PhraseEntity > findData(const QString &key,
                                      const QString &number,
                                      const QString &table,
                                      bool &haveFind, int max = 200);

    bool findPinyinByChinese(const QString& chinese, QString& pinyin);
    QList<PhraseEntity> findAssociational(const QString& table, const QString& head);
    QString findPunc(PuncType type);

private:
    static DBOperation *m_DB;
    QString m_DBFilePath;
    QString m_DBPasswod;
    QMutex m_mutex;

};

#define XYDB DBOperation::getInstance()
#endif // XYDATABASEOPERATION_H
