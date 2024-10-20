#ifndef PARSER_H
#define PARSER_H
#include "../include/arraylist.h"
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

    // Parse arguments
    void parse(int argc, const char* argv[]);

    // Parser Setup
    void parserSetup();

    // Print help/usage information
    void printHelp() const;

    // List books
    void listBooks(); 

    // Search for a book
    void searchBook();

    //autocomplete prefix
    string autoComplete();

    // Get the value of an option
    arraylist<string> getOption(const string& name) const;


private:
    // Internal Option structure
    struct Option {
        string description;
        arraylist<string> value; 
        bool inCLI = false;
        bool isFlag;

        // Default constructor
        Option() : description(""), value(arraylist<string>(1)), isFlag(false) {}

        // Parameterized constructor
        Option(const string& desc, const arraylist<string> val, bool flag = false)
            : description(desc), value(val), isFlag(flag) {}
    };
    
    // Store options and positional arguments
    map<string, Option> options;
};


#endif // PARSER_H