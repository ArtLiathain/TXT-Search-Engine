#include "../include/searchIndex.h"

searchIndex::searchIndex(/* args */)
{
}

searchIndex::~searchIndex()
{
}

void searchIndex::andFunc(unordered_map<string, float>* searchIndex, arraylist<pair<string, float>> *booksContainingWordArray)
{
    // if the array is empty clear the search index as nothing can and 
    if (booksContainingWordArray->length == 0)
    {
        (*searchIndex).clear();
        return;
    }
    //create a new map for And values
    unordered_map<string, float> newSearchIndex;
    // Loop over all the books containing the word searched
    for (int j = 0; j < booksContainingWordArray->length; j++)
    {
        // get book name
        string book = booksContainingWordArray->get(j).first;
        // if book is in the index from before add to new index
        if (searchIndex->count(book))
        {
            newSearchIndex[book] = (*searchIndex)[book] + booksContainingWordArray->get(j).second;
        }
    }
    // Overwrite old index with new one
    *searchIndex = newSearchIndex;
}

void searchIndex::orFunc(unordered_map<string, float>* searchIndex, arraylist<pair<string, float>> *booksContainingWordArray)
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
        if (searchIndex->count(book))
        {
            (*searchIndex)[book] += booksContainingWordArray->get(j).second;
        }
        else {
            (*searchIndex)[book] = booksContainingWordArray->get(j).second;
        }
    }
}

arraylist<pair<string, float>> searchIndex::notFunc(arraylist<pair<string, float>> *booksContainingWordArray)
{
    fileReader reader = fileReader();
    //get all books in directory
    arraylist<string> books = reader.getBooks();
    // Make an new hashmap to put all the values into
    unordered_map<string, float> booksWithoutTheWord;
    // Add every book to the map
    for (int i = 0; i < books.length; i++){
        booksWithoutTheWord[books.get(i)] = 0.0;
    }
    // Remove all books that are in the booksContainingWordArray from the map
    for (int j = 0; j < booksContainingWordArray->length; j++){
        booksWithoutTheWord.erase(booksContainingWordArray->get(j).first);
    }
    // Convert the map to an arraylist to make the next operations easier
    arraylist<pair<string,float>> arrayBooksWithoutTheWord;
    for (auto x : booksWithoutTheWord){
        arrayBooksWithoutTheWord.insert(pair(x.first, 0));
    }
    return arrayBooksWithoutTheWord;

    
}