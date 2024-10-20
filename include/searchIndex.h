#ifndef SEARCHINDEX_HPP
#define SEARCHINDEX_HPP
#include <unordered_map>

#include <iostream>
#include "arraylist.h"
#include "fileReader.h"

using namespace std;

class searchIndex
{
private:
    /* data */
public:
    searchIndex(/* args */);
    ~searchIndex();
    void orFunc(unordered_map<string, float>* searchIndex, arraylist<pair<string, float>> *booksContainingWordArray);
    void andFunc(unordered_map<string, float>* searchIndex, arraylist<pair<string, float>> *booksContainingWordArray);
    arraylist<pair<string, float>> notFunc(arraylist<pair<string, float>> *booksContainingWordArray);
};
#endif
