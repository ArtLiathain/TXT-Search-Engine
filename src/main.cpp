#include <iostream>
#include "../include/arraylist.h"
#include "../include/fileReader.h"
#include "../include/hashmap.h"
using namespace std;
#include "../include/trie.h"
#include "../include/Parser.h"
#include <chrono>


int main(int argc, char const *argv[])
{

    auto start2 = chrono::high_resolution_clock::now();
    stringhashmap<arraylist<pair<string, float>>> wordIndex = stringhashmap<arraylist<pair<string, float>>>();
    trie autocomplete = trie();

    fileReader reader = fileReader();
    reader.indexBooks(&wordIndex, &autocomplete);
    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<chrono::microseconds>(stop2 - start2);

    std::cout << "Duration: " << duration2.count() << " microseconds" << std::endl;
    // Parser parser;
    // trie autoComplete;
    
    // autoComplete.insert("Kiki");
    // autoComplete.insert("Kiiiiiiidi");
    // autoComplete.insert("Cookie");

    // // Add flags (boolean options)
    // parser.parserSetup();

    // // Parse command line arguments
    // parser.parse(argc, argv);

    // // Check the flags and output their status
    // if (parser.checkOption("verbose")) {
    //     cout << "Verbose mode is enabled." << endl;
    // }
    // if (parser.checkOption("help")) {
    //     parser.printHelp(); // Display help
    // }
    // if (parser.checkOption("list")) {
    //     parser.listBooks(); // List books
    // }
    // if (parser.checkOption("search")) {
    //     parser.searchBook(); // Search for a book
    // }
    // if (parser.checkOption("autocomplete")) {
    //     arraylist<string> results = autoComplete.getArrayList_withPrefix(parser.autoComplete());
    //     for (int i = 0; i < results.length; i++) {
    //         cout << results.get(i) << endl;
    //     }
    // }
    // if (parser.checkOption("addBook")) {
    //     parser.addBook(); // Add a book
    // }
    // // Continue with your program logic
    return 0;
}
