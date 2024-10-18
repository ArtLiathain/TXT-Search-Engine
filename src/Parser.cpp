#include "../include/Parser.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>


Parser::Parser() = default;

bool Parser::checkOption(const std::string& name) {
    if (options.find(name) != options.end()) {
        return options[name].inCLI;
    } else {
        throw std::invalid_argument("Unknown option: " + name);
    }
}

// Add a flag (boolean option)
void Parser::addFlag(const std::string& name, const std::string& description) {
    options[name] = Option(description, "false", true);
}

// Parse arguments
void Parser::parse(int argc, const char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            // It's an option
            std::string name = arg.substr(1);
            if (options.find(name) != options.end()) {
                if (options[name].isFlag) {
                    options[name].value = "true"; // it's a flag, set to true
                } 
                else if (name == "search") {
                    // Capture all words after -search until the next option
                    std::string searchValue;
                    while (i + 1 < argc && argv[i + 1][0] != '-') {
                        searchValue += argv[++i];
                        searchValue += " ";
                        
                    }
                    options[name].value = Parser::toString(searchValue);
                }
                else if (i + 1 < argc && argv[i + 1][0] != '-') {
                    options[name].value = argv[++i]; // Set regular option value
                }
                options[name].inCLI = true;
            } else {
                std::cerr << "Unknown option: " << name << std::endl;
            }
        } else {
            // It's a positional argument
            positionalArgs.push_back(arg);
        }
    }
}

void Parser::parserSetup() {
    // Adding options
    addOption("list", "List top x books", 0); // int
    addOption("search", "Search for a book", "default"); // string

    // Adding flags
    addFlag("verbose", "Enable verbose output");
    addFlag("help", "Display help information");
}

void Parser::printHelp() const {
    std::cout << "Usage: program [options] [arguments]" << std::endl;
    std::cout << "Options:" << std::endl;
    for (const auto& pair : options) {
        std::cout << "  -" << pair.first << ": " << pair.second.description << std::endl;
    }
}

void Parser::listBooks() {
    std::cout << "Listing top " << Parser::getOption<int>("list") << " books" << std::endl;
}

void Parser::searchBook() {
    std::cout << "Searching for book: " << Parser::getOption<std::string>("search") << std::endl;
}


// Convert any type to string
template<typename T>
T Parser::fromString(const std::string& str) const {
    std::istringstream iss(str);
    T value;
    iss >> value; // For types like int, double, etc., this will work fine
    return value;
}

// Specialization for std::string
template<>
std::string Parser::fromString<std::string>(const std::string& str) const {
    return str; // Just return the full string as is
}