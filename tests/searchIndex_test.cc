#include <gtest/gtest.h>
#include "../include/searchIndex.h"
using namespace std;

// Helper function to generate a wordIndex with specific sizes
stringhashmap<arraylist<pair<string, float>>> getCustomWordIndex(int wordCount, int bookCount)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex;
    for (int i = 0; i < wordCount; i++)
    {
        arraylist<pair<string, float>> wordValues;
        for (int j = 0; j < bookCount; j++)
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

// Test the OR functionality with empty search index and word array
TEST(searchIndex_test, orWithEmptySearchIndex)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getCustomWordIndex(3, 5);
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    search.orFunc(&searchIndex, &wordIndex.getValue("word0"));
    
    // Ensure searchIndex is correctly updated
    ASSERT_EQ(searchIndex.getValue("book0"), 0);
    ASSERT_EQ(searchIndex.getValue("book1"), 1);
    ASSERT_EQ(searchIndex.getValue("book4"), 4);
}

// Test the OR functionality with an empty booksContainingWordArray
TEST(searchIndex_test, orWithEmptyWordArray)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getCustomWordIndex(3, 5);
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    arraylist<pair<string, float>> emptyArray;
    search.orFunc(&searchIndex, &emptyArray);

    // Ensure searchIndex is unchanged (empty)
    ASSERT_EQ(searchIndex.getAllKeys().length, 0);
}

// Test AND functionality with an empty booksContainingWordArray
TEST(searchIndex_test, andWithEmptyWordArray)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getCustomWordIndex(3, 5);
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    search.orFunc(&searchIndex, &wordIndex.getValue("word0"));
    arraylist<pair<string, float>> emptyArray;
    search.andFunc(&searchIndex, &emptyArray);

    // Ensure searchIndex is cleared
    ASSERT_EQ(searchIndex.getAllKeys().length, 0);
}

// Test AND functionality when no common books are found
TEST(searchIndex_test, andWithNoCommonBooks)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getCustomWordIndex(3, 5);
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    // Modify the arrays so there is no common book between "word0" and "word1"
    wordIndex.getValue("word1").remove(0); // Removing book0 from word1's arraylist

    search.orFunc(&searchIndex, &wordIndex.getValue("word0"));
    search.andFunc(&searchIndex, &wordIndex.getValue("word1"));
    

    ASSERT_EQ(searchIndex.getAllKeys().length, 4);
}

// Test the NOT functionality
TEST(searchIndex_test, notFunc)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getCustomWordIndex(3, 5);
    searchIndex search = searchIndex();

    arraylist<pair<string, float>> booksContainingWord = wordIndex.getValue("word0");

    // Simulate a fileReader that returns all books
    arraylist<pair<string, float>> result = search.notFunc(&booksContainingWord);

    // Ensure the result contains books not in booksContainingWord
    //NOT is special as it always reads from the archive to get the not index so there are 101 books the lenght will be 101 as non contain word0
    ASSERT_EQ(result.length, 101); // Assuming fileReader.getBooks returns only 5 books as in wordIndex.
}

// Test AND functionality with larger index
TEST(searchIndex_test, andWithLargerIndex)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getCustomWordIndex(5, 10);
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    search.orFunc(&searchIndex, &wordIndex.getValue("word0"));
    search.andFunc(&searchIndex, &wordIndex.getValue("word1"));
    search.andFunc(&searchIndex, &wordIndex.getValue("word2"));

    ASSERT_EQ(searchIndex.getValue("book2"), 6); // book2 = 2 + 2 + 2
    ASSERT_EQ(searchIndex.getValue("book5"), 15); // book5 = 5 + 5 + 5
}

// Test OR functionality with duplicate calls and multiple words
TEST(searchIndex_test, orWithMultipleWords)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getCustomWordIndex(5, 10);
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    search.orFunc(&searchIndex, &wordIndex.getValue("word0"));
    search.orFunc(&searchIndex, &wordIndex.getValue("word1"));
    search.orFunc(&searchIndex, &wordIndex.getValue("word2"));

    ASSERT_EQ(searchIndex.getValue("book0"), 0 + 0 + 0);
    ASSERT_EQ(searchIndex.getValue("book1"), 1 + 1 + 1);
    ASSERT_EQ(searchIndex.getValue("book9"), 9 + 9 + 9);
}

// Test getting the book list from searchIndex
TEST(searchIndex_test, getBookList)
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = getCustomWordIndex(3, 5);
    searchIndex search = searchIndex();
    stringhashmap<float> searchIndex;

    search.orFunc(&searchIndex, &wordIndex.getValue("word0"));
    search.orFunc(&searchIndex, &wordIndex.getValue("word1"));

    arraylist<pair<string, float>> bookList = search.getBookList(&searchIndex);

    // Ensure books are sorted by the value in descending order
    ASSERT_EQ(bookList.get(0).second, 4 + 4);  // Largest value should be first
    ASSERT_EQ(bookList.get(bookList.length - 1).second, 0); // Smallest should be last
}