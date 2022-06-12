#include "phraseentity.h"

PhraseEntity::PhraseEntity(const QString &source,
                                 const QString &translate,
                                 const QString &complete,
                                 const QString &extra,
                                 int id,
                                 int   times,
                                 bool stick)
    : mSource(source),
      mPhrase(translate),
      mCompletePinyin(complete),
      mExtra(extra),
      mID(id),
      mTimes(times),
      mStick(stick)
{

}

PhraseEntity::~PhraseEntity()
{

}

void PhraseEntity::clear()
{
    mSource.clear();
    mPhrase.clear();
    mCompletePinyin.clear();
    mExtra.clear();
    mID = -1;
    mTimes = 1;
    mStick = false;
}

