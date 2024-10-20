#ifndef FILEREADER_HPP
#define FILEREADER_HPP
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include "arraylist.h"
using namespace std;

struct Value
{
    int count;
    string book;

    Value() : count(-1), book("") {}

    Value(int n, const string &t) : count(n), book(t) {}

    bool operator!=(const Value &other) const {
        return count != other.count || book != other.book;
    }

    bool operator==(const Value &other) const {
        return count == other.count && book == other.book;
    }

    friend std::ostream& operator<<(std::ostream &os, const Value &v) {
        os << "{count: " << v.count << ", book: \"" << v.book << "\"}";
        return os;
    }
};

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
#endif
