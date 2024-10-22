#include <gtest/gtest.h>
#include "../include/Parser.h"
#include "../include/trie.h"
TEST(parser_test, full_test)
{
    Parser parser;
    const char* args[] = {"-search", "NOT", "cat", "AND", "dog", "fluffy"};
    int arglen = sizeof(args) / sizeof(args[0]);


    stringhashmap<arraylist<pair<string, float>>> wordIndex = stringhashmap<arraylist<pair<string, float>>>();
    trie autocomplete = trie();
    fileReader reader = fileReader();
    reader.indexBooks(&wordIndex, &autocomplete);
    parser.parserSetup();
    parser.parse(arglen, args);
}