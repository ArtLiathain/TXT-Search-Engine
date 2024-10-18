#include "../include/searchIndex.h"

searchIndex::searchIndex(/* args */)
{
}

searchIndex::~searchIndex()
{
}

void searchIndex::andFunc(unordered_map<string, float>* searchValue, arraylist<pair<string, float>> *wordArray)
{
    if (wordArray->length == 0)
    {
        (*searchValue).clear();
        return;
    }
    unordered_map<string, float> newsearchValue;

    for (int j = 0; j < wordArray->length; j++)
    {
        string book = wordArray->get(j).first;
        if (searchValue->count(book))
        {
            newsearchValue[book] = (*searchValue)[book] + wordArray->get(j).second;
        }
    }
    *searchValue = newsearchValue;
}

void searchIndex::orFunc(unordered_map<string, float>* searchValue, arraylist<pair<string, float>> *wordArray)
{
    if (wordArray->length == 0)
    {
        return;
    }

    for (int j = 0; j < wordArray->length; j++)
    {
        string book = wordArray->get(j).first;
        if (searchValue->count(book))
        {
            (*searchValue)[book] += wordArray->get(j).second;
        }
        else {
            (*searchValue)[book] = wordArray->get(j).second;
        }
    }
}

arraylist<pair<string, float>> searchIndex::notFunc(arraylist<pair<string, float>> *wordArray)
{
    fileReader reader = fileReader();
    arraylist<string> books = reader.getBooks();
    unordered_map<string, float> booksWithoutTheWord;
    for (int i = 0; i < books.length; i++){
        booksWithoutTheWord[books.get(i)] = 0.0;
    }
    for (int j = 0; j < wordArray->length; j++){
        
        booksWithoutTheWord.erase(wordArray->get(j).first);
    }
    arraylist<pair<string,float>> arrayBooksWithoutTheWord;
    for (auto x : booksWithoutTheWord){
        arrayBooksWithoutTheWord.insert(pair(x.first, 0));
    }
    return arrayBooksWithoutTheWord;

    
}