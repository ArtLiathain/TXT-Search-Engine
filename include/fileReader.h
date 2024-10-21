#ifndef FILEREADER_HPP
#define FILEREADER_HPP
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include "hashmap.h"
#include "arraylist.h"
#include "trie.h"
using namespace std;

class fileReader
{
private:
    /* data */
public:
    fileReader(/* args */);
    ~fileReader();
    static void indexBook(string fileName, stringhashmap<arraylist<pair<string, float>>>* wordIndex, trie* autocomplete);
    static void indexBooks(stringhashmap<arraylist<pair<string, float>>>* wordIndex, trie* autocomplete);
    static arraylist<string> getBooks();
};
#endif
