#include "../include/Parser.h"
#include "../include/trie.h"
#include "../include/arraylist.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


Parser::Parser() = default;

bool Parser::checkOption(const string& name) {
    if (options.count(name) > 0) {
        return options[name].inCLI;
    } else {
        throw invalid_argument("Unknown option: " + name);
    }
}

void Parser::addOption(const string& name, const string& description, arraylist<string> defaultValue) {
    options[name] = Option(description, defaultValue, false);
}

arraylist<string> Parser::getOption(const string& name) const {
    return options.at(name).value;
}

// Add a flag (boolean option)
void Parser::addFlag(const string& name, const string& description) {
    options[name] = Option(description, arraylist<string>(1), true);
}

// Parse arguments
void Parser::parse(int num_args, const char* arg_array[]) {
    for (int i = 1; i < num_args; ++i) {
        string arg = arg_array[i];
        if (arg[0] == '-') {
            // It's an option
            string name = arg.substr(1);
            if (options.count(name) > 0) {
                if (name == "search") {
                    // Capture all words after -search until the next option
                    while (i + 1 < num_args && arg_array[i + 1][0] != '-') {
                        options[name].value.insert(arg_array[++i]);
                    }
                }
                else if (i + 1 < num_args && arg_array[i + 1][0] != '-') {
                    options[name].value.insert(arg_array[++i]); // Set regular option value
                } 
                options[name].inCLI = true;
            } else {
                cerr << "Unknown option: " << name << endl;
            }
        } 
    }
}

void Parser::parserSetup() {
    // Adding options
    addOption("list", "List top x books", arraylist<string>(1)); // int
    addOption("search", "Search for a book", arraylist<string>(1)); // string
    addOption("autocomplete", "returns a list of words starting with a given prefix", arraylist<string>(1)); // string

    // Adding flags
    addFlag("verbose", "Enable verbose output");
    addFlag("help", "Display help information");
}

void Parser::printHelp() const {
    cout << "Usage: program [options] [arguments]" << endl;
    cout << "Options:" << endl;
    for (const auto& pair : options) {
        cout << "  -" << pair.first << ": " << pair.second.description << endl;
    }
}

void Parser::listBooks() {
    cout << "Listing top " << getOption("list").get(0) << " books" << endl;
}

void Parser::searchBook() {
    cout << "Searching for book with word: " << getOption("search").get(1) << endl;
}

string Parser::autoComplete() {
    return getOption("autocomplete").get(0);
}

