#include "../include/Parser.h"
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

void Parser::addBook(stringhashmap<arraylist<pair<string, float>>> *wordIndex, trie *autocomplete) {
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
    fileReader reader = fileReader();
    reader.indexBook(filename, wordIndex, autocomplete);
    cout << "Book added to archive: " << newFilePath << endl;
}

// Parse arguments
void Parser::parse(int num_args, const char* arg_array[]) {
    // reset all option values
    arraylist<string> keys = options.getAllKeys();
    for (int i = 0; i < keys.length; i++) {   
        options.getValue(keys.get(i)).value = arraylist<string>(1);
        options.getValue(keys.get(i)).inCLI = false;
    }
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
    addOption("search", "Search for a book", arraylist<string>(1)); // string
    addOption("autocomplete", "returns a list of words starting with a given prefix", arraylist<string>(1)); // string
    addOption("addBook", "Add a book to the archive", arraylist<string>(2)); // string

    // Adding flags
    addFlag("help", "Display help information");
    addFlag("exit", "Exit the program");
}

void Parser::printHelp() {
    arraylist<string> keys = options.getAllKeys();
    cout << "Below is a list of valid options and their functions:" << endl;
    for (int i = 0; i < keys.length; i++) {
        string key = keys.get(i);
        Option opt = options.getValue(key);
        cout << "  -" << key << ": " << opt.description << endl;
    }
}


arraylist<pair<string, float>> Parser::searchBook(stringhashmap<arraylist<pair<string, float>>> *wordIndex) {
    searchIndex search = searchIndex();
    stringhashmap<float> searchWordIndex;
    arraylist<string> searchWords = getOption("search");
    arraylist<pair<string, float>> emptySearch = arraylist<pair<string, float>>(); 
    int i = 0;
    while (i < searchWords.length) {
        if (searchWords.get(i) == "OR") {
            i++;
            if (searchWords.get(i) == "NOT") {
                i++;
                if (wordIndex->keyExists(searchWords.get(i))) {
                    arraylist<pair<string, float>> notSearch = search.notFunc(&wordIndex->getValue(searchWords.get(i)));
                    search.orFunc(&searchWordIndex, &notSearch);
                } else {
                    arraylist<pair<string, float>> notSearch = search.notFunc(&emptySearch);             
                    search.orFunc(&searchWordIndex, &notSearch);       
                }
                
            } else {
                if (wordIndex->keyExists(searchWords.get(i))) {
                    search.orFunc(&searchWordIndex, &wordIndex->getValue(searchWords.get(i)));
                } else {
                    search.orFunc(&searchWordIndex, &emptySearch);                    
                }
            }
        } else if (searchWords.get(i) == "AND") {
            i++;
            if (searchWords.get(i) == "NOT") {
                i++;                
                if (wordIndex->keyExists(searchWords.get(i))) {
                    arraylist<pair<string, float>> notSearch = search.notFunc(&wordIndex->getValue(searchWords.get(i)));
                    search.andFunc(&searchWordIndex, &notSearch);
                } else {
                    arraylist<pair<string, float>> notSearch = search.notFunc(&emptySearch);                
                    search.andFunc(&searchWordIndex, &notSearch);    
                }
                
            } else {
                if (wordIndex->keyExists(searchWords.get(i))) {
                    search.andFunc(&searchWordIndex, &wordIndex->getValue(searchWords.get(i)));
                } else {
                    search.andFunc(&searchWordIndex, &emptySearch);                    
                }
            }
        } else {
            if (searchWords.get(i) == "NOT") {
                i++;
                if (wordIndex->keyExists(searchWords.get(i))) {
                    arraylist<pair<string, float>> notSearch = search.notFunc(&wordIndex->getValue(searchWords.get(i)));
                    search.orFunc(&searchWordIndex, &notSearch);
                } else {
                    arraylist<pair<string, float>> notSearch = search.notFunc(&emptySearch);           
                    search.orFunc(&searchWordIndex, &notSearch);         
                }
                
            } else {
                if (wordIndex->keyExists(searchWords.get(i))) {
                    search.orFunc(&searchWordIndex, &wordIndex->getValue(searchWords.get(i)));
                } else {
                    search.orFunc(&searchWordIndex, &emptySearch);                    
                }
            }
        }
        i++;
    }

    return search.getBookList(&searchWordIndex);
}

string Parser::autoComplete() {
    return getOption("autocomplete").get(0);
}

