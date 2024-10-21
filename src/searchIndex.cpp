#include "../include/searchIndex.h"

searchIndex::searchIndex(/* args */)
{
}

searchIndex::~searchIndex()
{
}

void searchIndex::andFunc(stringhashmap<float> *searchIndex, arraylist<pair<string, float>> *booksContainingWordArray)
{
    // if the array is empty clear the search index as nothing can and
    if (booksContainingWordArray->length == 0)
    {
        arraylist<string> keys = searchIndex->getAllKeys();
        for (int j = 0; j < keys.length; j++)
        {
            (*searchIndex).remove(keys.get(j));
        }
        return;
    }
    // create a new map for And values
    stringhashmap<float> newSearchIndex;
    // Loop over all the books containing the word searched
    for (int j = 0; j < booksContainingWordArray->length; j++)
    {
        // get book name
        string book = booksContainingWordArray->get(j).first;
        // if book is in the index from before add to new index
        if (searchIndex->keyExists(book))
        {
            newSearchIndex.insert(book, (*searchIndex).getValue(book) + booksContainingWordArray->get(j).second);
        }
    }
    // Overwrite old index with new one
    *searchIndex = newSearchIndex;
}

void searchIndex::orFunc(stringhashmap<float> *searchIndex, arraylist<pair<string, float>> *booksContainingWordArray)
{
    // If the array is empty do nothing, as it has no change in preference
    if (booksContainingWordArray->length == 0)
    {
        return;
    }

    for (int j = 0; j < booksContainingWordArray->length; j++)
    {
        string book = booksContainingWordArray->get(j).first;
        // If books is in the index already increment value else add the value
        if (searchIndex->keyExists(book))
        {
            (*searchIndex).insert(book, (*searchIndex).getValue(book) + booksContainingWordArray->get(j).second);
        }
        else
        {
            (*searchIndex).insert(book, booksContainingWordArray->get(j).second);
        }
    }
}

arraylist<pair<string, float>> searchIndex::notFunc(arraylist<pair<string, float>> *booksContainingWordArray)
{
    fileReader reader = fileReader();
    // get all books in directory
    arraylist<string> books = reader.getBooks();
    // Make an new hashmap to put all the values into
    stringhashmap<float> booksWithoutTheWord;
    // Add every book to the map
    for (int i = 0; i < books.length; i++)
    {
        booksWithoutTheWord.insert(books.get(i), 0.0);
    }
    // Remove all books that are in the booksContainingWordArray from the map
    for (int j = 0; j < booksContainingWordArray->length; j++)
    {
        booksWithoutTheWord.remove(booksContainingWordArray->get(j).first);
    }

    arraylist<string> keys = booksWithoutTheWord.getAllKeys();
    // Convert the map to an arraylist to make the next operations easier6
    arraylist<pair<string, float>> arrayBooksWithoutTheWord;
    for (int k = 0; k < keys.length; k++)
    {
        arrayBooksWithoutTheWord.insert(pair(keys.get(k), 0));
    }
    return arrayBooksWithoutTheWord;
}