#include "../include/fileReader.h"
#include <iostream>
#include "../include/arraylist.h"
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <dirent.h>
using namespace std;

unordered_set<string> stopWords;

fileReader::fileReader(/* args */)
{
    stopWords = {
        "the", "and", "is", "in", "at", "of", "on", "a", "an", "by", "to", "with",
        "for", "from", "that", "this", "it", "as", "but", "or", "if", "so", "not",
        "are", "were", "be", "been", "was", "can", "will", "shall", "may", "must", "I"};
}

fileReader::~fileReader()
{
}

void fileReader::readFile(string fileName)
{
    string mystring;
    ifstream file;
    file.open("../../archive/" + fileName);

    unordered_map<string, int> wordMap;
    int count = 0;

    if (file.is_open())
    {
        while (file)
        {
            file >> mystring;
            for (int i = 0, len = mystring.size(); i < len; i++)
            {
                if (ispunct(mystring[i]))
                {
                    mystring.erase(i--, 1);
                    len = mystring.size();
                }
                mystring[i] = tolower(mystring[i]);
            }
            if (stopWords.count(mystring))
            {
                continue;
            }
            wordMap[mystring] += 1;
            count++;
        }
    }
    else
    {
        cout << "fileNotFound";
    }
}

arraylist<string> fileReader::getDirectories()
{

    struct dirent *entry = nullptr;
    DIR *dp = nullptr;
    arraylist<string> books = arraylist<string>(200);
    dp = opendir("../../archive/");
    if (dp != nullptr)
    {
        while ((entry = readdir(dp)))
        {
            string filePath = "";
            filePath += entry->d_name;
            books.insert(filePath);
        }
    }

    closedir(dp);
    return books;
}
