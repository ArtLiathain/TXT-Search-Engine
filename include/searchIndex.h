#ifndef SEARCHINDEX_HPP
#define SEARCHINDEX_HPP
#include <unordered_map>

#include <iostream>
#include "arraylist.h"

using namespace std;

class searchIndex
{
private:
    /* data */
public:
    searchIndex(/* args */);
    ~searchIndex();
    void orFunc(string word, unordered_map<string, float>* searchValue, unordered_map<string, arraylist<pair<string, float>>> *wordIndex);
    void andFunc(string word, unordered_map<string, float>* searchValue, unordered_map<string, arraylist<pair<string, float>>> *wordIndex);
    void notFunc(string word, unordered_map<string, float>* searchValue, unordered_map<string, arraylist<pair<string, float>>> *wordIndex);
};
#endif SEARCHINDEX_HPP
