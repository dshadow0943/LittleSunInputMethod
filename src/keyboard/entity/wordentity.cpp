#include "wordentity.h"

WordEntity::WordEntity()
{

}

/**
 * @brief cmpWordDist
 * @param word1
 * @param word2
 * @return
 * 比较两个词差异值大小
 */
bool WordEntity::cmpWordDist(const WordEntity& word1, const WordEntity& word2)
{
    return word1.dist < word2.dist;
}
