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
    arraylist<pair<string, float>> temp = (*wordIndex)[word];
    unordered_map<string, float> newsearchValue;

    for (int j = 0; j < temp.length; j++)
    {
        string book = temp.get(j).first;
        if (searchValue->count(book))
        {
            newsearchValue[book] = (*searchValue)[book] + temp.get(j).second;
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
    arraylist<pair<string, float>> temp = (*wordIndex)[word];

    for (int j = 0; j < temp.length; j++)
    {
        string book = temp.get(j).first;
        if (searchValue->count(book))
        {
            (*searchValue)[book] += temp.get(j).second;
        }
        else {
            (*searchValue)[book] = temp.get(j).second;
        }
    }
}

void searchIndex::notFunc(string word, unordered_map<string, float> *searchValue, unordered_map<string, arraylist<pair<string, float>>> *wordIndex)
{
    if (!wordIndex->count(word))
    {
        return;
    }
    arraylist<pair<string, float>> temp = (*wordIndex)[word];

    for (int j = 0; j < temp.length; j++)
    {
        string book = temp.get(j).first;
        if (searchValue->count(book))
        {
            searchValue->erase(book);
        }
    }
}