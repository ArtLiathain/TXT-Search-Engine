#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <iostream>
#include "Arraylist.h"
using namespace std;
class fileReader
{
private:
    /* data */
public:
    fileReader(/* args */);
    ~fileReader();
    void readFile(string fileName);
    Arraylist<string> getDirectories();
};
#endif FILEREADER_HPP
