#include "../include/fileReader.h"
#include <iostream>
#include "../include/Arraylist.h"
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
    cout<<"../../archive/" + fileName << "\n";
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

            if (wordMap.count(mystring))
            {
                wordMap[mystring] += 1;
            }
            else
            {
                wordMap[mystring] = 1;
            }
            count++;
        }
        for (auto x : wordMap)
        {
            if (x.second < 1000)
            {
                continue;
            }
            cout << x.first << " " << (float)x.second << "\n";
        }
    }
    else
    {
        cout << "fileNotFound";
    }
}

void fileReader::getDirectories()
{

    struct dirent *entry = nullptr;
    DIR *dp = nullptr;

    dp = opendir("../../archive/");
    if (dp != nullptr)
    {
        while ((entry = readdir(dp)))
        {
            string filePath = "";
            filePath += entry->d_name;
            readFile(filePath);
        }
    }

    closedir(dp);
}
