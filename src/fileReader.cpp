#include "../include/fileReader.h"

using namespace std;

unordered_set<string> skippedWords;

fileReader::fileReader(/* args */)
{
    // list of words that should be skipped as thay are not worth counting
    skippedWords = {
        "the", "and", "is", "in", "at", "of", "on", "a", "an", "by", "to", "with",
        "for", "from", "that", "this", "it", "as", "but", "or", "if", "so", "not",
        "are", "were", "be", "been", "was", "can", "will", "shall", "may", "must", "I"};
}

fileReader::~fileReader()
{
}

void fileReader::readFile(string fileName, unordered_map<string, arraylist<pair<string, float>>> *wordIndex)
{
    string mystring;
    ifstream file;
    //Open book by name
    file.open("../../archive/" + fileName);

    unordered_map<string, int> wordFrequencyMap;

    int bookWordCount = 0;

    if (file.is_open())
    {
        // continues while there are words left in the file
        while (file)
        {
            // grab a space seperated word from the book
            file >> mystring;
            for (int i = 0, len = mystring.size(); i < len; i++)
            {
                // Remove punctuation
                if (ispunct(mystring[i]))
                {
                    mystring.erase(i--, 1);
                    len = mystring.size();
                }
                // Lowercase the string
                mystring[i] = tolower(mystring[i]);
            }
            // If skipped word don't increment count
            if (skippedWords.count(mystring))
            {
                continue;
            }
            // Can ignore the need for initialisation as all ints are 0 while null which can be incremented
            wordFrequencyMap[mystring] += 1;
            bookWordCount++;
        }

        // Loop over every word add to the frequency map
        for (auto x : wordFrequencyMap)
        {
            // If value is in the word index add to the arraylist
            if (wordIndex->count(x.first))
            {
                (*wordIndex)[x.first].insert(make_pair(fileName, (float)x.second/bookWordCount));
            }
            // Add a new array to the index otherwise
            else
            {
                arraylist<pair<string, float>> tempArrList(200);
                tempArrList.insert(make_pair(fileName, (float)x.second/bookWordCount));
                (*wordIndex)[x.first] = std::move(tempArrList);
            }
        }
    }
    else
    {
        cout << "fileNotFound";
    }
}

arraylist<string> fileReader::getBooks()
{

    struct dirent *entry = nullptr;
    DIR *dp = nullptr;
    arraylist<string> books = arraylist<string>(200);
    // open directory and loop over each item within
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
