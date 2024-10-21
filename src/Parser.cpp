#include "../include/Parser.h"
#include "../include/trie.h"
#include "../include/arraylist.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>

using namespace std;


Parser::Parser() = default;

bool Parser::checkOption(const string& name) {
    return options.getValue(name).inCLI;
}

void Parser::addOption(const string& name, const string& description, arraylist<string> defaultValue) {
    options.insert(name, Option(description, defaultValue, true));

}

arraylist<string> Parser::getOption(const string& name) {
    return options.getValue(name).value;
}

// Add a flag (boolean option)
void Parser::addFlag(const string& name, const string& description) {
    options.insert(name, Option(description, arraylist<string>(1), true));
}

void Parser::addBook() {
    string filename = getOption("addBook").get(0);
    string path = getOption("addBook").get(1);
    // Create the archive directory if it doesn't exist
    std::filesystem::create_directories("../../archive/");

    // Construct the full path for the new file in the archive
    std::string newFilePath = "../../archive/" + filename;

    // Open the source file
    std::ifstream src(path, std::ios::binary);
    if (!src) {
        cerr << "Error: Could not open source file " << path << endl;
        return;
    }

    // Open the destination file
    std::ofstream dst(newFilePath, std::ios::binary);
    if (!dst) {
        cerr << "Error: Could not create destination file " << newFilePath << endl;
        return;
    }

    // Copy the file contents
    dst << src.rdbuf();

    cout << "Book added to archive: " << newFilePath << endl;
}

// Parse arguments
void Parser::parse(int num_args, const char* arg_array[]) {
    for (int i = 1; i < num_args; ++i) {
        string arg = arg_array[i];
        if (arg[0] == '-') {
            // It's an option
            string name = arg.substr(1);
            if (options.getValue(name).here) {
                Option opt = options.getValue(name);
                if (name == "search" or name == "addBook") {
                    // Capture all words after -search until the next option
                    while (i + 1 < num_args && arg_array[i + 1][0] != '-') {
                        opt.value.insert(arg_array[++i]);
                    }
                }
                else if (i + 1 < num_args && arg_array[i + 1][0] != '-') {
                    opt.value.insert(arg_array[++i]); // Set regular option value
                } 
                opt.inCLI = true;
                options.insert(name, opt);
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
    addOption("addBook", "Add a book to the archive", arraylist<string>(2)); // string

    // Adding flags
    addFlag("verbose", "Enable verbose output");
    addFlag("help", "Display help information");
}

void Parser::printHelp() {
    arraylist<string> keys = options.getAllKeys();
    for (int i = 0; i < keys.getLength(); i++) {
        string key = keys.get(i);
        Option opt = options.getValue(key);
        cout << "  -" << key << ": " << opt.description << endl;
    }
}

void Parser::listBooks() {
    cout << "Listing top " << getOption("list").get(0) << " books" << endl;
}

void Parser::searchBook() {
    cout << "Searching for book with word: " << getOption("search").get(0) << endl;
}

string Parser::autoComplete() {
    return getOption("autocomplete").get(0);
}

