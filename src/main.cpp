#include <iostream>
#include "../include/LinkedList.h"
#include "../include/Parser.h"

int main(int argc, char const *argv[])
{
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
        std::cout << "Verbose mode is enabled." << std::endl;
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
    // Continue with your program logic
    return 0;
}
