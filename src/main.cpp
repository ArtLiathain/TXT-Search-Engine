#include <iostream>
#include "../include/arraylist.h"
#include "../include/fileReader.h"
#include "../include/hashmap.h"
using namespace std;
#include "../include/trie.h"
#include "../include/arraylist.h"
using namespace std;
#include "../include/LinkedList.h"
#include "../include/Parser.h"

int main(int argc, char const *argv[])
{
    auto startread = std::chrono::high_resolution_clock::now();
    fileReader reader = fileReader();
    arraylist<string> books = reader.getBooks();

    // for (int i = 0; i < books.length; i++){
    //     reader.readFile(books.get(i));
    // }
    auto endread = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationread = endread - startread;
    std::cout << "File indexing took " << durationread.count() << " seconds" << std::endl;
    

    auto start = std::chrono::high_resolution_clock::now();
    arraylist<pair<string, Value>> keyValuePairs = arraylist<pair<string, Value>>(10);
    keyValuePairs.insert(make_pair("Apple", Value{10, "Book A"}));
    keyValuePairs.insert(make_pair("Banana", Value{5, "Book B"}));
    keyValuePairs.insert(make_pair("Strawberry", Value{5, "Book C"}));
    keyValuePairs.insert(make_pair("Orange", Value{3, "Book D"}));
    keyValuePairs.insert(make_pair("Grapes", Value{7, "Book E"}));
    stringhashmap<Value> map = stringhashmap<Value>(keyValuePairs.length);
    map.createHashTable(keyValuePairs);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Hashtable creation took " << duration.count() << " seconds" << std::endl;
    
    std::cout << "Apple found in " << map.getValue("Apple").book << " " << map.getValue("Apple").count << " times" << endl;
    std::cout << "Dog found in " << map.getValue("Dog").book << " " << map.getValue("Dog").count << " times" << endl;
    
    
    auto start2 = std::chrono::high_resolution_clock::now();
    arraylist<pair<string, int>> keyIntPairs = arraylist<pair<string, int>>(3);
    keyIntPairs.insert(make_pair("Apple", 12));
    keyIntPairs.insert(make_pair("Banana", 6));
    keyIntPairs.insert(make_pair("Strawberry", 5));
    keyIntPairs.insert(make_pair("Orange", 7));
    keyIntPairs.insert(make_pair("Grapes", 7));
    keyIntPairs.insert(make_pair("Strawberry", 12));
    stringhashmap<int> map2 = stringhashmap<int>(1);
    map2.createHashTable(keyIntPairs);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << "Hashtable creation took " << duration2.count() << " seconds" << std::endl;
    
    std::cout << "Apple found " << map2.getValue("Apple") << " times" << endl;
    std::cout << "Dog found " << map2.getValue("Dog") << " times" << endl;

    arraylist<string> keys = map2.getAllKeys();
    for(int i = 0; i < keys.length; i++){
        std::cout << keys.get(i) << endl;
    }

    map2.remove("Apple");
    map2.printTable();

    // EANNA TESTING


    Parser parser;
    trie autoComplete;
    
    autoComplete.insert("Kiki");
    autoComplete.insert("Kiiiiiiidi");
    autoComplete.insert("Cookie");

    // Add flags (boolean options)
    parser.parserSetup();

    // Parse command line arguments
    parser.parse(argc, argv);

    // Check the flags and output their status
    if (parser.checkOption("verbose")) {
        cout << "Verbose mode is enabled." << endl;
    }
    if (parser.checkOption("help")) {
        parser.printHelp(); // Display help
    }
    if (parser.checkOption("list")) {
        parser.listBooks(); // List books
    }
    if (parser.checkOption("search")) {
        parser.searchBook(); // Search for a book
    }
    if (parser.checkOption("autocomplete")) {
        arraylist<string> results = autoComplete.getArrayList_withPrefix(parser.autoComplete());
        for (int i = 0; i < results.length; i++) {
            cout << results.get(i) << endl;
        }
    }
    // Continue with your program logic
    return 0;
}
