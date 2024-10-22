#include <iostream>
#include "../include/arraylist.h"
#include "../include/fileReader.h"
#include "../include/hashmap.h"
using namespace std;
#include "../include/trie.h"
#include "../include/Parser.h"


int main(int argc, char const *argv[])
{
    Parser parser;
    // Add flags (boolean options)
    parser.parserSetup();

    // Parse command line arguments
    parser.parse(argc, argv);

    // Check the flags and output their status
    if (parser.checkOption("help")) {
        parser.printHelp(); // Display help
    } else {
        // setup the word index and autocomplete
        stringhashmap<arraylist<pair<string, float>>> wordIndex = stringhashmap<arraylist<pair<string, float>>>();
        trie autocomplete = trie();
        fileReader reader = fileReader();
        reader.indexBooks(&wordIndex, &autocomplete);

        while (!parser.checkOption("exit")) {
            string divLine(100, '-');
            // run parse for search or autocomplete passed through CLI
            if (parser.checkOption("search")) {
                arraylist<pair<string, float>> results = parser.searchBook(&wordIndex); // Search for a book
                for (int i = 0; i < results.length; i++) {
                    if (i%5 == 0 and i != 0) {
                        cout << divLine << endl;
                        cout << "\nPress any key to display next page of results, press q to quit" << endl;
                        if (cin.get() == 'q') {
                            break;
                        }
                    }
                    cout << divLine << endl;
                    cout << i+1 << " | " + results.get(i).first << " " << results.get(i).second << endl;
                }
            }
            if (parser.checkOption("autocomplete")) {
                arraylist<string> results = autocomplete.getArrayList_withPrefix(parser.autoComplete());
                for (int i = 0; i < results.length; i++) {
                    if (i%5 == 0 and i != 0) {
                        cout << divLine << endl;
                        cout << "\nPress any key to display next page of results, press q to quit" << endl;
                        if (cin.get() == 'q') {
                            break;
                        }
                    }
                    cout << divLine << endl;
                    cout << i+1 << " | " + results.get(i) << endl;
                }
            }
            if (parser.checkOption("addBook")) {
                parser.addBook(&wordIndex, &autocomplete); // Add a book
            }


            cout << "\nProgram finished.\n\n" << endl;
            parser.printHelp();
            cout << "\n\nEnter new arguments: " << endl;
            // Clear the cin buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Read the new input
            string input;
            getline(cin, input);
            input = "./my_executable " + input;
            // Split input into arguments
            arraylist<string> args; 
            stringstream ss(input);
            string word;
            while (ss >> word) {
                args.insert(word);
            }

            // Create new argv array
            int new_argc = args.length;
            const char **new_argv = new const char*[new_argc];
            for (int i = 0; i < new_argc; ++i) {
                new_argv[i] = args.get(i).c_str();
            }

            // Re-parse with the new arguments
            parser.parse(new_argc, new_argv);

            // Clean up memory
            delete[] new_argv;
            
        }
        cout << "\nExiting program" << endl;
    }
    
    // Continue with your program logic
    return 0;
}
