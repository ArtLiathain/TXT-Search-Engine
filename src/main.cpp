#include <iostream>
#include "../include/arraylist.h"
#include "../include/fileReader.h"
#include "../include/hashmap.h"
using namespace std;
#include "../include/trie.h"
#include "../include/Parser.h"


int main(int argc, char const *argv[])
{
    stringhashmap<arraylist<pair<string, float>>> wordIndex = stringhashmap<arraylist<pair<string, float>>>();
    trie autocomplete = trie();
    fileReader reader = fileReader();
    reader.indexBooks(&wordIndex, &autocomplete);
   
    Parser parser;
    
    // autocomplete.insert("Kiki");
    // autocomplete.insert("Kiiiiiiidi");
    // autocomplete.insert("Cookie");

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
        arraylist<pair<string, float>> results = parser.searchBook(wordIndex); // Search for a book
        for (int i = 0; i < results.length; i++) {
            cout << results.get(i).first << " " << results.get(i).second << endl;
        }
    }
    if (parser.checkOption("autocomplete")) {
        arraylist<string> results = autocomplete.getArrayList_withPrefix(parser.autoComplete());
        for (int i = 0; i < results.length; i++) {
            cout << results.get(i) << endl;
        }
    }
    if (parser.checkOption("addBook")) {
        parser.addBook(); // Add a book
    }
    // Continue with your program logic
    return 0;
}
