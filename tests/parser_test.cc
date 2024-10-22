#include <gtest/gtest.h>
#include "../include/Parser.h"
#include "../include/trie.h"

// create test wordIndex
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

trie getAutocomplete()
{
    trie autoComplete;
    
    autoComplete.insert("heat");
    autoComplete.insert("hello");
    autoComplete.insert("hell");
    autoComplete.insert("help");
    autoComplete.insert("heard");
    autoComplete.insert("heal");

    return autoComplete;

}
TEST(parser_test, full_test)
{
    Parser parser;
    const char* args[] = {"./program", "-search", "NOT", "cat", "AND", "dog", "fluffy"};
    int arglen = sizeof(args) / sizeof(args[0]);

    stringhashmap<arraylist<pair<string, float>>> wordIndex = getWordIndex();
    trie autocomplete = getAutocomplete();
    parser.parserSetup();
    parser.parse(arglen, args);

    ASSERT_EQ(parser.searchBook(&wordIndex), 6); // book2 = index 3 value 2 *3
}
