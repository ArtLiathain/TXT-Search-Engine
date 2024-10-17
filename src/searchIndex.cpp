#include "../include/searchIndex.h"

searchIndex::searchIndex(/* args */)
{
}

searchIndex::~searchIndex()
{
}

void searchIndex::andFunc(string word, unordered_map<string, float> *searchValue, unordered_map<string, arraylist<pair<string, float>>> *wordIndex)
{
    if (!wordIndex->count(word))
    {
        (*searchValue).clear();
        return;
    }
    arraylist<pair<string, float>> booksContainingWord = (*wordIndex)[word];
    unordered_map<string, float> newsearchValue;

    for (int j = 0; j < booksContainingWord.length; j++)
    {
        string book = booksContainingWord.get(j).first;
        if (searchValue->count(book))
        {
            newsearchValue[book] = (*searchValue)[book] + booksContainingWord.get(j).second;
        }
    }
    *searchValue = newsearchValue;
}

void searchIndex::orFunc(string word, unordered_map<string, float> *searchValue, unordered_map<string, arraylist<pair<string, float>>> *wordIndex)
{
    if (!wordIndex->count(word))
    {
        return;
    }
    arraylist<pair<string, float>> booksContainingWord = (*wordIndex)[word];

    for (int j = 0; j < booksContainingWord.length; j++)
    {
        string book = booksContainingWord.get(j).first;
        if (searchValue->count(book))
        {
            (*searchValue)[book] += booksContainingWord.get(j).second;
        }
        else {
            (*searchValue)[book] = booksContainingWord.get(j).second;
        }
    }
}

void searchIndex::notFunc(string word, unordered_map<string, float> *searchValue, unordered_map<string, arraylist<pair<string, float>>> *wordIndex)
{
    if (!wordIndex->count(word))
    {
        return;
    }
    

    arraylist<pair<string, float>> booksContainingWord = (*wordIndex)[word];

    for (int j = 0; j < booksContainingWord.length; j++)
    {
        string book = booksContainingWord.get(j).first;
        if (searchValue->count(book))
        {
            searchValue->erase(book);
        }
    }
}