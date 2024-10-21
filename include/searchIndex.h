#ifndef SEARCHINDEX_HPP
#define SEARCHINDEX_HPP
#include <iostream>
#include "arraylist.h"
#include "fileReader.h"
#include "hashmap.h"
using namespace std;

class searchIndex
{
private:
    /* data */
public:
    searchIndex(/* args */);
    ~searchIndex();
    void orFunc(stringhashmap<float>* searchIndex, arraylist<pair<string, float>> *booksContainingWordArray);
    void andFunc(stringhashmap<float>* searchIndex, arraylist<pair<string, float>> *booksContainingWordArray);
    arraylist<pair<string, float>> notFunc(arraylist<pair<string, float>> *booksContainingWordArray);
};
#endif
