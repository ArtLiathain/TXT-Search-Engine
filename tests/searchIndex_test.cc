#include <gtest/gtest.h>
#include "../include/searchIndex.h"
using namespace std;

// Demonstrate some basic assertions.

stringhashmap<arraylist<pair<string, float>>> getWordIndex()
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex;
    for (int i = 0; i < 10; i++)
    {
        arraylist<pair<string, float>> wordValues;
        for (int j = 0; j < 10; j++)
        {
            std::string text = "book";
            text += std::to_string(j);
            wordValues.insert(pair(text, j));
        }
        std::string word = "word";
        word += std::to_string(i);
        wordIndex.insert(word, wordValues);
    }
    return wordIndex;
}

TEST(searchIndex_test, initialise)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getWordIndex();
    ASSERT_EQ(wordIndex.getValue("word1").length, 10);
}

TEST(searchIndex_test, or)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getWordIndex();
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    search.orFunc(&searchIndex, &wordIndex.getValue("word1"));
    search.orFunc(&searchIndex, &wordIndex.getValue("word1"));
    search.orFunc(&searchIndex, &wordIndex.getValue("word1"));

    ASSERT_EQ(searchIndex.getValue("word2"), 6); // book2 = index 3 value 2 *3
}

TEST(searchIndex_test, and)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getWordIndex();
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    search.orFunc(&searchIndex, &wordIndex.getValue("word1"));
    search.andFunc(&searchIndex, &wordIndex.getValue("word2"));
    search.andFunc(&searchIndex, &wordIndex.getValue("word3"));
    ASSERT_EQ(searchIndex.getValue("book2"), 6); // book2 = index 3 value 2 *3
    wordIndex.getValue("word3").remove(2);
    search.andFunc(&searchIndex, &wordIndex.getValue("word3"));
    ASSERT_EQ(searchIndex.getValue("book2"), 0); // book2 = index 3 value 2 *3 * 0
}
