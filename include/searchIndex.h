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
    void orFunc(unordered_map<string, float>* searchValue, arraylist<pair<string, float>> *wordArray);
    void andFunc(unordered_map<string, float>* searchValue, arraylist<pair<string, float>> *wordArray);
    arraylist<pair<string, float>> notFunc(arraylist<pair<string, float>> *wordArray);
};
#endif SEARCHINDEX_HPP
