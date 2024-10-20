#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

class Parser {
public:
    Parser(); // Constructor

    bool checkOption(const std::string& name);

    // Add an option with a default value
    template<typename T>
    void addOption(const std::string& name, const std::string& description, T defaultValue);

    // Add a flag (boolean option)
    void addFlag(const std::string& name, const std::string& description);

    // Parse arguments
    void parse(int argc, const char* argv[]);

    // Parser Setup
    void parserSetup();

    // Get the value of an option
    template<typename T>
    T getOption(const std::string& name) const;

    // Print help/usage information
    void printHelp() const;

    // List books
    void listBooks(); 

    // Search for a book
    void searchBook();

    //autocomplete prefix
    std::string autoComplete();


private:
    // Internal Option structure
    struct Option {
        std::string description;
        std::string value;
        bool inCLI = false;
        bool isFlag;

        // Default constructor
        Option() : description(""), value(""), isFlag(false) {}

        // Parameterized constructor
        Option(const std::string& desc, const std::string& val, bool flag = false)
            : description(desc), value(val), isFlag(flag) {}
    };
    
    // Store options and positional arguments
    std::map<std::string, Option> options;
    std::vector<std::string> positionalArgs;

    // Convert any type to string
    template<typename T>
    std::string toString(const T& value) const;

    // Convert string to any type
    template<typename T>
    T fromString(const std::string& str) const;
};

// Template method implementations must be in the header file (as they are generated at compile-time)

template<typename T>
void Parser::addOption(const std::string& name, const std::string& description, T defaultValue) {
    options[name] = Option(description, toString(defaultValue), false);
}

template<typename T>
T Parser::getOption(const std::string& name) const {
    return fromString<T>(options.at(name).value);
}

template<typename T>
std::string Parser::toString(const T& value) const {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}


#endif // PARSER_H