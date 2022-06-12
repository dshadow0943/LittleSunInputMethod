#ifndef CHINESECHARACTERSERVER_H
#define CHINESECHARACTERSERVER_H

#include "handwritemodel.h"
#include "handwritetreemodel.h"
#include "pinyinretrievalmodel.h"
#include "puncretrirvalmode.h"
#include "globalconfig.h"
#include <QStringList>
#include <QThread>
#include <QStandardPaths>
#include <QDebug>


class ThesaurusRetrieval : public QThread
{
    Q_OBJECT
public:

    static ThesaurusRetrieval* getInstance();
    void initDB();    //初始化
    QStringList getNext();
    QStringList getPhraseByPinyin(QString keyword, bool isEnglish = false);
    QStringList getPhraseByPinyin(const QString &text, int index, QString &showText);
    QStringList getChineseByHand(CharacterEntity Character, int count = 20);
    QStringList getAssociateWords(QString word);
    QStringList getPunc(DBOperation::PuncType);

    void updatePunc(QString& data, DBOperation::PuncType type);

    bool writeFile(QString text);
    int saveCharaters(QList<CharacterEntity>&);
    bool deleteFont();
    void reset();

signals:
    void comming(std::function<void()> f);

private slots:
    void onConming(std::function<void()> f);

private:
    ThesaurusRetrieval(QObject *parent = nullptr);

public:
    QString mShowLetters;   //候选框字母

private:
    int mWordCount;
    int mIndex;
    QStringList mResultWords;
    HandWriteModel mHandWrite;
    HandwriteTreeModel mHandTree;
    PuncRetrirvalMode mPunc;
    PinyinRetrievalModel *mPinyin;

    const QString mDirPath = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + APPLOCALPATH;

protected:
    void run();

public:
    //异步执行内部类
    template <class T>
    class AsynRetrieval {
    public:
        //回调函数
       std::function<void(T)> m_func = nullptr;
       //执行类实例
       ThesaurusRetrieval *m_p = nullptr;

       AsynRetrieval(ThesaurusRetrieval *p, std::function<void(T)> func) {
           m_func = func;
           m_p = p;
       }

       static AsynRetrieval<T>* getInstace(ThesaurusRetrieval *p, std::function<void(T)> func = nullptr) {
           static AsynRetrieval obj(p, func);
           obj.m_func = func;
           return &obj;
       }
       void getPhraseByPinyin(const QString &keyword, bool isEnglish = false) {
           std::thread([=] (ThesaurusRetrieval* e) {
                    m_func(e->getPhraseByPinyin(keyword, isEnglish));
           }, m_p).detach();
       }
       void getPhraseByPinyin(const QString &text, int index) {
           std::thread([=] (ThesaurusRetrieval* e) {
                    m_func(e->getPhraseByPinyin(text, index, e->mShowLetters));
           }, m_p).detach();
       }
       void getChineseByHand(CharacterEntity& Character, int count = 20) {
           std::thread([=] (ThesaurusRetrieval* e) {
                m_func(e->getChineseByHand(Character, count));
           }, m_p).detach();
       }
       void getAssociateWords(QString word) {
           std::thread([=] (ThesaurusRetrieval* e) {
                m_func(e->getAssociateWords(word));
           }, m_p).detach();
       }
       void getPunc(DBOperation::PuncType type) {
           std::thread([=] (ThesaurusRetrieval* e) {
                m_func(e->getPunc(type));
           }, m_p).detach();
       }
    };

    /**
     * @brief asynExec 获取异步执行实例
     * @param res 回调函数
     * @return 异步执行实例
     */
    template <typename T>
    AsynRetrieval<T>* asynExec(std::function<void(T)> res) {
        return AsynRetrieval<T>::getInstace(this, res);
    }
};

#endif // CHINESECHARACTERSERVER_Hthis->start();
