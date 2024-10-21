#include <gtest/gtest.h>
#include "../include/trie.h"


TEST(trie_test, InsertAndRetrieve)
{
    trie t;
    t.insert("hello");
    t.insert("world");
    t.insert("third");

    arraylist<std::string> words = t.getArrayList();

    
    ASSERT_EQ(words.length, 3);
}


TEST(trie_test, GetArrayListWithPrefix)
{
    trie t;
    t.insert("apple");
    t.insert("app");
    t.insert("apricot");
    t.insert("banana");

    arraylist<std::string> wordsWithPrefix = t.getArrayList_withPrefix("ap");

    
    ASSERT_EQ(wordsWithPrefix.length, 3);
    for (int i = 0; i < wordsWithPrefix.length; i++)
    {
        ASSERT_FALSE(wordsWithPrefix.get(i).compare("banana") == 0);
    }
}


TEST(trie_test, GetArrayListEmptyTrie)
{
    trie t;

    arraylist<std::string> words = t.getArrayList();

    
    ASSERT_EQ(words.length, 0);
}


TEST(trie_test, InsertDuplicateWords)
{
    trie t;
    t.insert("apple");
    t.insert("apple");

    arraylist<std::string> words = t.getArrayList();

    
    ASSERT_EQ(words.length, 1);
    EXPECT_EQ(words.get(0), "apple");
}


TEST(trie_test, CaseInsensitivity)
{
    trie t;
    t.insert("Apple");
    t.insert("apple");

    arraylist<std::string> words = t.getArrayList();

    
    ASSERT_EQ(words.length, 1);
    EXPECT_EQ(words.get(0), "apple");
}

TEST(trie_test, SerializeAndDeserialize)
{
    trie t;
    t.insert("hello");
    t.insert("world");
    t.insert("third");

    arraylist<std::string> words = t.getArrayList();

    t.serialize("trieTest.dat");

    trie restored = trie::deserialize("trieTest.dat");
    arraylist<std::string> restoredWords = restored.getArrayList();

    ASSERT_EQ(words.length, restoredWords.length);
}