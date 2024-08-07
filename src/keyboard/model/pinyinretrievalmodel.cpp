﻿/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#include "pinyinretrievalmodel.h"
#include <QDebug>
#include <QFile>

PinyinRetrievalModel *PinyinRetrievalModel::getInstance()
{
    static PinyinRetrievalModel obj;
    return &obj;
}

PinyinRetrievalModel::PinyinRetrievalModel(QObject *parent)
    : QObject(parent), mEnglish(false)
{

}

PinyinRetrievalModel::~PinyinRetrievalModel()
{

}

bool PinyinRetrievalModel::initInputBase(const QString &path)
{
    return XYDB->initDatabaseFile(path);
}

void PinyinRetrievalModel::resetSearch()
{
    mCompleteItem.clear();
    mAutoCompleteItem.clear();
    mCurrentKeyWords.clear();
    mSearchResults.clear();
    mTempItemsMap.clear();
}

QString PinyinRetrievalModel::getCurLetters()
{
    QString letters = mCurrentKeyWords;
    return letters.replace("%", "");
}

/**
 * @brief XYInputSearchInterface::getCandidate
 * 获取候选词组
 * @param keyword
 * @param isEnglish
 * @return
 */
QStringList PinyinRetrievalModel::getCandidate(const QString &keyword, bool isEnglish)
{
    mEnglish = isEnglish;
    QList<PhraseEntity > items = searchTranslates(keyword);
    QStringList data;
    for (PhraseEntity item : items) {
        data.append(item.mPhrase);
    }
    return data;
}

/**
 * @brief XYInputSearchInterface::getCandidate
 * 获取后续候选词组
 * @param text
 * @param index
 * @param showText
 * @return
 */
QStringList PinyinRetrievalModel::getCandidate(const QString &text, int index, QString &showText)
{
    if (index < mSearchResults.size())
    {
        completeInput(text, showText, mSearchResults.at(index));
    }
    else
    {
        mSearchResults.clear();
    }
    QStringList data;
    for (PhraseEntity item : mSearchResults) {
        data.append(item.mPhrase);
    }
    return data;
}

/**
 * @brief XYInputSearchInterface::getAssociationalWord
 * 获取联想词组
 * @param text
 * @param index
 * @return
 */
QStringList PinyinRetrievalModel::getAssociationalWords(const QString &text)
{
    QStringList datas;
    for (PhraseEntity item : autoAssociational(text)) {
        QString data = item.mPhrase.remove(text);
        if (!data.isEmpty()) {
            datas.append(data);
        }
    }
    return datas;
}

QStringList PinyinRetrievalModel::getPunc(DBOperation::PuncType type)
{
    QStringList datas;
    datas = XYDB->getInstance()->findPunc(type).split(" ");
    return datas;
}

/**
 * @brief XYInputSearchInterface::searchTranslates
 * 检索词组
 * @param keyword
 * @return
 */
QList<PhraseEntity > &PinyinRetrievalModel::searchTranslates(const QString &keyword)
{
    QList<PhraseEntity > list;

    if (keyword.trimmed().isEmpty()) // 如果传入的词为空了，代表删完了，应该关闭输入窗口
    {
        mCurrentKeyWords.clear();
        mSearchResults.clear();
        return mSearchResults;
    }

    QString splitPY;
    bool find_new = false;
    if (mEnglish)
    {
        splitPY = keyword;
        list = findItemsFromTemp(splitPY, false);
        if (list.isEmpty())
        {
            find_new = true;
            list = XYDB->findData(splitPY + "%", "", "userEnglishTable", find_new);
            list += XYDB->findData(splitPY + "%", "", "englishTable", find_new);
            deDuplication(list, true);
        }
    }
    else
    {
        int num = 0;
        splitPY = splitPinyin(keyword, num);
        splitPY.replace("\'", "%\'");
        list = findPossibleMust(splitPY);

        //智能造句
//        XYTranslateItem autoTranslate = autoCreateWords(splitPY); // 智能造句
//        if (autoTranslate.miID == -1)
//        {
//            list.prepend(autoTranslate);
//        }
    }

    mCurrentKeyWords = splitPY;

    mSearchResults = list;
    return mSearchResults;
}

void PinyinRetrievalModel::setChinese(bool ch)
{
    mEnglish = !ch;
}

/**
 * @brief XYInputSearchInterface::splitePinyin
 * 分割拼音
 * @param pinyin
 * @param num
 * @return  分割后的拼音
 */
QString PinyinRetrievalModel::splitPinyin(const QString &pinyin, int &num)
{
    QString initial = "bpmfdtnlgkhjqxzcsywr";       //声母
    QStringList zcs = QString("z c s").split(" ");
    QStringList vowelList = QString("a o e ai ao ou ei er an ang en eng").split(" "); //可单独成音的韵母

    QString result;     //分割结果

    if (pinyin.contains("\'"))
    {
        bool endfgf = pinyin.endsWith("\'");
        QStringList children = pinyin.split("\'", QString::SkipEmptyParts);
        for (int i = 0; i < children.size(); ++i)
        {
            int cur_num = 0;
            if (!result.isEmpty() && !result.endsWith("%\'")) // 每次进入一定是新的字的拼音
            {
                result += "%\'";
            }
            result += splitPinyin(children.at(i), cur_num);
            num += cur_num;
        }
        if (endfgf)
        {
            result += "\'";
        }
        return result;
    }
    int curIndex = 0;
    while (curIndex < pinyin.size())
    {
        //以声母开头
        if (initial.contains(pinyin.at(curIndex))) // 是声母
        {
            int ym = 1; //韵母偏移量
            int h = 0; // zh ch sh标记
            // zh ch sh 多加一位
            if (zcs.contains(pinyin.at(curIndex)) && curIndex + 1 < pinyin.size() && pinyin.at(curIndex + 1) == 'h')
            {
                h = 1;
                ym++;
            }

            //获取声母可匹配的所有韵母
            QStringList vowels = getVowelsByInitial(pinyin.at(curIndex));

            // 贪心查找 （尽可能长的找到满足的）
            while ((ym + curIndex) < pinyin.size())
            {
                bool find = false;
                for (int i = 0; i < vowels.size(); ++i)
                {
                    QString c_py = vowels.at(i);
                    if (c_py.startsWith(pinyin.mid(curIndex + 1 + h, ym - h)))
                    {
                        find = true;
                    }
                }
                if (!find)
                {
                    if (ym > h)
                    {
                        ym--;
                    }
                    break;
                }
                ym++;
            }

            if (!result.isEmpty() && !result.endsWith("%\'"))
            {
                result += "%\'";
            }
            result += pinyin.mid(curIndex, ym + 1);
            curIndex += ym;
        }
        //上一组拼音以g n r结尾
        else
        {
            if (result.endsWith("g") // 如果是特殊的几个韵母结束的，到这里应该截取下来，重新匹配
                    || result.endsWith("n")
                    || result.endsWith("r") )
            {
                int last_index = result.lastIndexOf("%\'");
                QString last; //最后一组拼音
                if (last_index != -1)
                {
                    last = result.mid(last_index + 2);
                }
                else
                {
                    last = result;
                }
                last.remove(last.size() - 1, 1);

                // 判断截取之后是否是可以组合的拼音
                if (last.size() > 0 && getVowelsByInitial(last.at(0)).contains(last.mid(1)))
                {
                    result.remove(result.size() - 1, 1);
                    curIndex -= 1;
                    continue;
                }
            }

            //以a o e 开头
            if (vowelList.contains(pinyin.at(curIndex)))
            {
                int ym = 0;
                while ((ym + curIndex) < pinyin.size())
                {
                    bool find = false;
                    for (int i = 0; i < vowelList.size(); ++i)
                    {
                        QString c_py = vowelList.at(i);
                        if (c_py.startsWith(pinyin.mid(curIndex, ym + 1)))
                        {
                            find = true;
                        }
                    }
                    if (find)
                    {
                        ym++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (!result.isEmpty() && !result.endsWith("%\'"))
                {
                    result += "%\'";
                }
                result += pinyin.mid(curIndex, ym);
                curIndex += ym - 1;
            }
            //最后的不再作处理
            else
            {
                if (!result.isEmpty() && !result.endsWith("%\'"))
                {
                    result += "%\'";
                }
                result += pinyin.at(curIndex);
            }
        }

        num++;
        curIndex++;
    }
    if (num == 0)
    {
        num++;
    }

    return result;
}

/**
 * @brief XYInputSearchInterface::deDuplication
 * 过滤重复词汇
 * @param items
 * @param del
 */
void PinyinRetrievalModel::deDuplication(QList<PhraseEntity> &items, bool del)
{
    Q_UNUSED(del);

    for(int i=0; i < items.size(); ++i) {
        for(int j = items.size()-1; j > i; --j) {
            if (mEnglish) {
                if(items.at(i).mCompletePinyin == items.at(j).mCompletePinyin)
                {
                    items.removeAt(j);
                }
            } else if (items.at(i).mPhrase == items.at(j).mPhrase) {
                items.removeAt(j);
            }
        }
    }
}

PhraseEntity PinyinRetrievalModel::autoCreateWords(const QString &keyword)
{
    mAutoCompleteItem.clear();
    QString exists = keyword;
    QMap<QString, QList<PhraseEntity > >::iterator it = mTempItemsMap.find(exists);
    while(it == mTempItemsMap.end() || it.value().isEmpty())
    {
        if (exists.contains("%\'"))
        {
            exists = exists.mid(0, exists.lastIndexOf("%\'"));
        }
        else
        {
            break;
        }

        it = mTempItemsMap.find(exists);
    };

    if (exists == keyword || it == mTempItemsMap.end() || it.value().isEmpty())
    {
        return mAutoCompleteItem;
    }

    PhraseEntity comAll = mAutoCompleteItem;
    comAll.mCompletePinyin = it.value().at(0).mCompletePinyin;
    comAll.mPhrase = it.value().at(0).mPhrase;
    QString keys = keyword.mid(exists.size());
    if (keys.startsWith("%\'"))
    {
        keys.remove(0, 2);
    }

    int k_nums = keys.split("%\'", QString::SkipEmptyParts).size();
    int f_nums = 0;
    while (k_nums > f_nums)
    {
        for (int i = 0; i < f_nums; ++i)
        {
            if (!keys.contains("%\'"))
            {
                keys.clear();
            }
            else
            {
                keys = keys.mid(keys.indexOf("%\'") + 2);
            }
        }
        if (keys.isEmpty())
        {
            break;
        }

        QList<PhraseEntity > list = findPossibleMust(keys);
        if (!list.isEmpty())
        {
            comAll.mCompletePinyin += "\'";
            comAll.mCompletePinyin += list.at(0).mCompletePinyin;

            comAll.mPhrase += list.at(0).mPhrase;

            f_nums = list.at(0).mCompletePinyin.split("\'").size();
        }
        else
        {
            break;
        }
    };

    return comAll;
}

QList<PhraseEntity > PinyinRetrievalModel::findItemsFromTemp(const QString &keyword, bool force)
{
    QList<PhraseEntity > list;
    if (force || mTempItemsMap.find(keyword) != mTempItemsMap.end())
    {
        QString delsuf = keyword.mid(0, keyword.lastIndexOf("%"));
        QMap<QString, QList<PhraseEntity > >::iterator it = mTempItemsMap.begin();
        while (mTempItemsMap.end() != it)
        {
            QString last_key = it.key();
            if (delsuf.startsWith(last_key))
            {
                list = it.value() + list;
            }
            it++;
        }
    }

    return list;
}

/**
 * @brief XYInputSearchInterface::findPossibleMust
 * 检索词汇
 * @param keyword
 * @param max
 * @return
 */
QList<PhraseEntity > PinyinRetrievalModel::findPossibleMust(const QString &keyword, int max)
{
    QStringList words = keyword.split("%\'");
    QList<PhraseEntity > results;
    QString key;
    for (int i = 0; i < words.size(); ++i)
    {
        if (!key.isEmpty())
        {
            key += "%\'";
        }
        key += words.at(i);

        QList<PhraseEntity > list;
        QMap<QString, QList<PhraseEntity > >::iterator it = mTempItemsMap.find(key);
        bool find = false;
        if (it != mTempItemsMap.end())
        {
            find = true;
            list = it.value();
        }

        if (!find)
        {
            bool haveFind = false;
            //从用户词典中检索
            list = XYDB->findData(key + "%", QString::number(i + 1), "userPinyin", haveFind, max);
            //第一个字进行全单字检索
            if (i == 0)
            {
                QList<PhraseEntity > single = XYDB->findData(key + "%", "", "singlePinyin", haveFind, max);

                for (int i = 0; i < single.size(); ++i)
                {
                    PhraseEntity singleItem = single.at(i);
                    QStringList singles = singleItem.mPhrase.split(" ", QString::SkipEmptyParts);
                    for (int j = 0; j < singles.size(); ++j)
                    {
                        if (list.size() > 200)
                        {
                            break;
                        }
                        list.append(PhraseEntity("singlePinyin", singles.at(j), singleItem.mCompletePinyin));
                    }
                }
            }
            //从词组表中进行检索
            list += XYDB->findData(key + "%", QString::number(i + 1), "basePinyin", haveFind, max);

            deDuplication(list, true);
            if (haveFind)
            {
                mTempItemsMap.insert(key, list);
            }
        }
        //查找的词从精准到粗略排序，越后面的越加精准
        if (!list.isEmpty())
        {
            results = list + results;
        }
    }
    return results;
}

/**
 * @brief XYInputSearchInterface::saveItem
 * 保存用户自定义词组
 * @param item
 */
void PinyinRetrievalModel::saveItem(PhraseEntity item)
{
    if (!item.mCompletePinyin.isEmpty()) // 保存用户词库
    {
        item.mTimes += 1;
        if (item.mSource.toLower().contains("english"))
        {
            XYDB->insertData(item, "userEnglishTable");
        }
        else
        {
            item.mExtra = QString::number(item.mPhrase.size());
            XYDB->insertData(item, "userPinyin");
        }
    }
}

void PinyinRetrievalModel::clearTemp()
{
    QMap<QString, QList<PhraseEntity > >::iterator it = mTempItemsMap.begin();
    while (mTempItemsMap.end() != it)
    {
        it++;
    }
    mTempItemsMap.clear();
}

QStringList PinyinRetrievalModel::getVowelsByInitial(const QChar &initial)
{
    QStringList vowels;
    switch (initial.toLatin1()) // 单独为每一个声母指定可匹配的韵母
    {
    case 'b':
        vowels = QString("a o ai ei ao an en ang eng i ie iao ian in ing u").split(" ", QString::SkipEmptyParts);
        break;
    case 'p':
        vowels = QString("a o ai ei ao ou an en ang eng i ie iao ian in ing u").split(" ", QString::SkipEmptyParts);
        break;
    case 'm':
        vowels = QString("a e o ai ei ao an en ang eng i ie iao iu ian in ing u").split(" ", QString::SkipEmptyParts);
        break;
    case 'f':
        vowels = QString("a o ei ou an en ang eng u").split(" ", QString::SkipEmptyParts);
        break;
    case 'd':
        vowels = QString("a o ai ei ao ou an en ang eng i ia ie iao ian iu ian ing u uo ui uan un ong").split(" ", QString::SkipEmptyParts);
        break;
    case 't':
        vowels = QString("a e ai ei ao ou an ang eng i ie iao ian ing u uo ui uan un ong").split(" ", QString::SkipEmptyParts);
        break;
    case 'n':
    case 'l':
        vowels = QString("a e o ai ei ao ou an en ang eng i ia ie iao ian iu ian in ing u uo ui uan un ong v ve").split(" ", QString::SkipEmptyParts);
        break;
    case 'g':
    case 'k':
    case 'h':
        vowels = QString("a e ai ei ao ou an en ang eng u ua uo uai ui uan un uang ong").split(" ", QString::SkipEmptyParts);
        break;
    case 'j':
    case 'q':
    case 'x':
        vowels = QString("i ia ie iao iu ian in iang ing v u ue ve van uan un vn iong").split(" ", QString::SkipEmptyParts);
        break;
    case 'z':
        vowels = QString("a e i ai ei ao ou an en ang eng u ua uo uai ui uan un uang ong").split(" ", QString::SkipEmptyParts);
        break;
    case 'c':
        vowels = QString("a e i ai ao ou an en ang eng u ua uo uai ui uan un uang ong").split(" ", QString::SkipEmptyParts);
        break;
    case 's':
        vowels = QString("a e i ai ei ao ou an en ang eng u ua uo uai ui uan un uang ong").split(" ", QString::SkipEmptyParts);
        break;
    case 'r':
        vowels = QString("e i ao ou an en ang eng u ua uo ui uan un uang ong").split(" ", QString::SkipEmptyParts);
        break;
    case 'y':
        vowels = QString("a e i o ao ou an in ang ing u ue uan un ong").split(" ", QString::SkipEmptyParts);
        break;
    case 'w':
        vowels = QString("a o ai ei an en ang eng u").split(" ", QString::SkipEmptyParts);
        break;
    default:
        break;
    }

    return vowels;
}

QList<PhraseEntity > &PinyinRetrievalModel::completeInput(const QString &text, int index, QString &showText)
{
    if (index < mSearchResults.size())
    {
        completeInput(text, showText, mSearchResults.at(index));
    }
    else
    {
        mSearchResults.clear();
    }
    return mSearchResults;
}

/**
 * @brief XYInputSearchInterface::completeInput
 *
 * @param text  输入的词
 * @param showText 更新后的候选字母
 * @param item
 * @return
 */
QList<PhraseEntity > &PinyinRetrievalModel::completeInput(const QString &text, QString &showText, PhraseEntity item)
{
    if (!text.isEmpty()) // 如果为空直接退出
    {
        if (!mEnglish)
        {
            if (!mCompleteItem.mCompletePinyin.isEmpty())
            {
                mCompleteItem.mCompletePinyin += "\'";
            }
            mCompleteItem.mCompletePinyin += item.mCompletePinyin;
            mCompleteItem.mPhrase += item.mPhrase;
            QStringList all = mCurrentKeyWords.split("%\'", QString::SkipEmptyParts);
            int com = mCompleteItem.mCompletePinyin.split("\'", QString::SkipEmptyParts).size();
            int remain = all.size() - com;
            if (remain > 0)
            {
                //重新获取待检索拼音
                QString key;
                for (int i = com; i < all.size(); ++i)
                {
                    if (!key.isEmpty())
                    {
                        key += "%\'";
                    }
                    key += all.at(i);
                }
                //保存用户词组
                saveItem(item);
                //检索词组
                mSearchResults = findPossibleMust(key);
                //更新候选字母
                showText = mCompleteItem.mPhrase + key.replace("%", "");
            }
            else
            {
                //更新词组使用频次
                if (mCompleteItem.mPhrase == item.mPhrase)
                {
                    mCompleteItem.mTimes = item.mTimes + 1;
                }
                else
                {
                    saveItem(item);
                }

                mCompleteItem.mExtra = QString::number(mCompleteItem.mPhrase.size());
                XYDB->insertData(mCompleteItem, "userPinyin");
                mSearchResults.clear();
            }
        }
        else
        {
            saveItem(item);
            if (mEnglish)
            {
                PhraseEntity temp;
                temp.mCompletePinyin = text;
                XYDB->insertData(temp, "userEnglishTable");
            }
            mSearchResults.clear();
        }
    }
    return mSearchResults;
}

QList<PhraseEntity> PinyinRetrievalModel::autoAssociational(const QString &text)
{
    QList<PhraseEntity> items;
    QString pinyin;
    if (!XYDB->findPinyinByChinese("%"+text+"%", pinyin)) {
            return items;
    }

    QString initial = pinyin.at(0);
    items.append(XYDB->findAssociational("userPinyin", text+"%"));
    QString table = QString("basePinyin_%1").arg(initial.toUpper());
    items.append(XYDB->findAssociational(table, text+"%"));
    //过滤重复元素
    deDuplication(items);

    return items;
}

