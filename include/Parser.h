#ifndef PARSER_H
#define PARSER_H
#include "./arraylist.h"
#include "./trie.h"
#include "./searchIndex.h"
#include "./hashmap.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <fstream>
using namespace std;

class Parser {
public:
    Parser(); // Constructor

    bool checkOption(const string& name);

    // Add an option with a default value
    void addOption(const string& name, const string& description, arraylist<string> defaultValue);

    // Get the value of an option
    arraylist<string> getOption(const string& name);

    // Add a flag (boolean option)
    void addFlag(const string& name, const string& description);

    // Add a new book to the data structure
    void addBook(stringhashmap<arraylist<pair<string, float>>> *wordIndex, trie *autocomplete);

    // Parser Setup
    void parserSetup();

    // Parse arguments
    void parse(int argc, const char* argv[]);
    
    // Print help/usage information
    void printHelp();

    // Search for a book
    arraylist<pair<string, float>> searchBook(stringhashmap<arraylist<pair<string, float>>> *wordIndex);

    //autocomplete prefix
    string autoComplete();

private:
    // Internal Option structure
    struct Option {
        string description;
        arraylist<string> value; 
        bool inCLI = false;
        bool here;

        // Default constructor
        Option() : description(""), value(arraylist<string>(1)), here(false) {}

        // Parameterized constructor
        Option(const string& desc, const arraylist<string> val, bool here = false)
            : description(desc), value(val), here(here) {}
    };
    
    // Store options in hashmap
    stringhashmap<Option> options = stringhashmap<Option>(20);
};


#endif // PARSER_H