#ifndef XYTRANSLATEITEM_H
#define XYTRANSLATEITEM_H

#include <QString>

class PhraseEntity
{
public:
    PhraseEntity(const QString &source = "", // 输入源
                    const QString &translate = "", // 存放当前想输入的类型（比如中文，或者英文）
                    const QString &complete = "", // 完整的拼音（比如中文对应的拼音，或者完整的）
                    const QString &extra = "", // 额外的信息（比如中文词组的字数）
                    int id = -1,
                    int times = 1, // 词频
                    bool stick = false); // 是否置顶
    ~PhraseEntity();
    void clear();

private:
    QString  mSource;      //数据库表
    QString  mPhrase;       //检索到的词组
    QString  mCompletePinyin;    //完整拼音
    QString  mExtra;       //词组字数
    int      mID;          //词组id
    int      mTimes;       //词组使用频次
    bool     mStick;       //置顶

    friend class PinyinRetrievalModel;
    friend class DBOperation;
};

#endif // XYTRANSLATEITEM_H
