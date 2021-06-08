#include "wordentity.h"

WordEntity::WordEntity()
{

}

bool WordEntity::cmpWordDist(const WordEntity word1, const WordEntity word2)
{
    return word1.dist < word2.dist;
}
