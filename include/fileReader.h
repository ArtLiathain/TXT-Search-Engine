#ifndef FILEREADER_HPP
#define FILEREADER_HPP
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include "hashmap.h"
#include "arraylist.h"
using namespace std;

class fileReader
{
private:
    /* data */
public:
    fileReader(/* args */);
    ~fileReader();
    void readFile(string fileName, stringhashmap<arraylist<pair<string, float>>>* wordIndex);
    arraylist<string> getBooks();
};
#endif
