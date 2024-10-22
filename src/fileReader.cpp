#include "../include/fileReader.h"
#include <thread>
using namespace std;

stringhashmap<int> skippedWords;

fileReader::fileReader(/* args */)
{
    // list of words that should be skipped as thay are not worth counting
    std::string skipWords[] = {
        "the", "and", "is", "in", "at", "of", "on", "a", "an", "by", "to", "with",
        "for", "from", "that", "this", "it", "as", "but", "or", "if", "so", "not",
        "are", "were", "be", "been", "was", "can", "will", "shall", "may", "must", "I"};
    for (int i = 0; i < skipWords->size(); i++)
    {
        skippedWords.insert(skipWords[i], 0);
    }
}

fileReader::~fileReader()
{
}

void fileReader::indexBook(string fileName, stringhashmap<arraylist<pair<string, float>>> *wordIndex, trie *autocomplete)
{
    string mystring;
    ifstream file;
    // Open book by name
    file.open("../../archive/" + fileName);

    stringhashmap<int> wordFrequencyMap;
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
            if (skippedWords.keyExists(mystring))
            {

                continue;
            }

            // Can ignore the need for initialisation as all ints are 0 while null which can be incremented
            if (wordFrequencyMap.keyExists(mystring))
            {

                wordFrequencyMap.insert(mystring, wordFrequencyMap.getValue(mystring) + 1);
            }
            else
            {
                wordFrequencyMap.insert(mystring, 0);
            }

            bookWordCount++;
        }
        arraylist<string> keys = wordFrequencyMap.getAllKeys();

        // Loop over every word add to the frequency map
        for (int j = 0; j < keys.length; j++)
        {

            string word = keys.get(j);
            // If value is in the word index add to the arraylist
            if (wordIndex->keyExists(word))
            {
                (*wordIndex).getValue(word).insert(make_pair(fileName, (float)wordFrequencyMap.getValue(word) / bookWordCount));
            }
            // Add a new array to the index otherwise
            else
            {
                autocomplete->insert(word);
                arraylist<pair<string, float>> tempArrList(200);
                tempArrList.insert(make_pair(fileName, (float)wordFrequencyMap.getValue(word) / bookWordCount));
                (*wordIndex).insert(word, tempArrList);
            }
        }
    }
    else
    {
        cout << "fileNotFound";
    }
}

void fileReader::indexBooks(stringhashmap<arraylist<pair<string, float>>> *wordIndex, trie *autocomplete)
{
    arraylist<string> books = getBooks();
    arraylist<thread> threads = arraylist<thread>();
    
    for (int i = 0; i < books.length; i++)
    {
        thread th1(indexBook, books.get(i), wordIndex, autocomplete);
        threads.insert(std::move(th1));
        cout << "ADDING THREAD" << endl;
        // indexBook(books.get(i), wordIndex, autocomplete);
    }
    cout << "THREAD " << threads.length << endl;
    for (int j = 0; j < threads.length; j++)
    {
        cout << "Joining thread " << books.get(j) << endl;
        if (threads.get(j).joinable())
        {
            threads.get(j).join();
        }
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
