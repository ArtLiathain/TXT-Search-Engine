#include "../include/fileReader.h"
#include <iostream>
#include "../include/Arraylist.h"
#include <fstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_set<string> stopWords;

fileReader::fileReader(/* args */)
{
    stopWords = {
        "the", "and", "is", "in", "at", "of", "on", "a", "an", "by", "to", "with",
        "for", "from", "that", "this", "it", "as", "but", "or", "if", "so", "not",
        "are", "were", "be", "been", "was", "can", "will", "shall", "may", "must"};
}

fileReader::~fileReader()
{
}

void fileReader::readFile(string path)
{
    int count = 0;
    ifstream myfile;
    unordered_map<string, int> wordMap;
    myfile.open("../../archive/AnnalsOfTheFourMasters.txt");
    string mystring;
    if (myfile.is_open())
    {
        while (myfile)
        {
            myfile >> mystring;
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
            if (x.second < 100)
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
