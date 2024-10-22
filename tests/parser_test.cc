#include <gtest/gtest.h>
#include "../include/Parser.h"
#include "../include/trie.h"

// create test wordIndex
stringhashmap<arraylist<pair<string, float>>> getWordIndex()
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex;
    for (int i = 0; i < 5; i++)
    {
        arraylist<pair<string, float>> wordValues;
        for (int j = 0; j < 5; j++)
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

trie getAutocomplete()
{
    trie autoComplete;

    autoComplete.insert("word1");
    autoComplete.insert("word2");
    autoComplete.insert("word3");
    autoComplete.insert("word4");
    autoComplete.insert("word5");
    autoComplete.insert("word6");

    return autoComplete;
}
TEST(parser_test, full_test)
{
    Parser parser;
    const char *args[] = {"./program", "-search", "word1", "AND", "word1"};
    int arglen = 5;

    stringhashmap<arraylist<pair<string, float>>> wordIndex = getWordIndex();

    parser.parserSetup();
    parser.parse(arglen, args);

    arraylist<pair<string, float>> orderedBooks = parser.searchBook(&wordIndex);
    cout << orderedBooks.length << endl;
    for (int i = 1; i < orderedBooks.length; i++)
    {
        ASSERT_TRUE(orderedBooks.get(i - 1).second >= orderedBooks.get(i).second);
    }
}
