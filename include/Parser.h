#ifndef PARSER_H
#define PARSER_H
#include "../include/arraylist.h"
#include "./hashmap.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

class Parser {
public:
    Parser(); // Constructor

    bool checkOption(const string& name);

    // Add an option with a default value
    void addOption(const string& name, const string& description, arraylist<string> defaultValue);

    // Add a flag (boolean option)
    void addFlag(const string& name, const string& description);

    // Add a new book to the data structure
    void addBook();

    // Parse arguments
    void parse(int argc, const char* argv[]);

    // Parser Setup
    void parserSetup();

    // Print help/usage information
    void printHelp();

    // List books
    void listBooks(); 

    // Search for a book
    void searchBook();

    //autocomplete prefix
    string autoComplete();

    // Get the value of an option
    arraylist<string> getOption(const string& name);


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
    
    // Store options and positional arguments
    stringhashmap<Option> options = stringhashmap<Option>(20);
};


#endif // PARSER_H