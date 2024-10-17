#ifndef FILEREADER_HPP
#define FILEREADER_HPP
#include <unordered_map>

#include <iostream>
#include "arraylist.h"
using namespace std;
class fileReader
{
private:
    /* data */
public:
    fileReader(/* args */);
    ~fileReader();
    void readFile(string fileName, unordered_map<string, arraylist<pair<string, float>>>* wordIndex);
    arraylist<string> getBooks();
};
#endif FILEREADER_HPP
