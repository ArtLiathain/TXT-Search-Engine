#include <iostream>
#include "../include/trie.h"
#include "../include/Arraylist.h"
using namespace std;
#include "../include/LinkedList.h"
#include "../include/Parser.h"

int main(int argc, char const *argv[])
{
    trie autoComplete;
    
    autoComplete.insert("Kiki");
    autoComplete.insert("Kiiiiiiidi");
    autoComplete.insert("Cookie");

    // Arraylist<string> trieValues = autoComplete.getArrayList();

    // for(int i = 0; i < trieValues.length; i++){
    //     cout << trieValues.get(i) << "\n";
    // }

    // Arraylist<string> trieValuess = autoComplete.getArrayList_withPrefix("Ki");

    // for(int i = 0; i < trieValuess.length; i++){
    //     cout << trieValuess.get(i) << "\n";
    // }

    // LinkedList<int>  temp;
    // temp.add(5);
    // std::cout << temp.get(0) << "\n";
    // std::cout << "Hello World" << "\n";

    Parser parser;

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
        Arraylist<string> results = autoComplete.getArrayList_withPrefix(parser.autoComplete());
        for (int i = 0; i < results.length; i++) {
            cout << results.get(i) << endl;
        }
    }
    // Continue with your program logic
    return 0;
}
