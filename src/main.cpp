#include <iostream>
#include "../include/fileReader.h"
#include "../include/hashmap.h"
using namespace std;
int main(int argc, char const *argv[])
{
    fileReader reader = fileReader();
    arraylist<string> books = reader.getDirectories();

    for (int i = 0; i < books.length; i++){
        reader.readFile(books.get(i));
    }

    Hashmap map;
    vector<pair<string, Value>> keyValuePairs = {
        make_pair("Apple", Value{10, "Book A"}),
        make_pair("Banana", Value{5, "Book B"}),
        make_pair("Strawberry", Value{5, "Book C"}),
        make_pair("Orange", Value{3, "Book D"}),
        make_pair("Grapes", Value{7, "Book E"})
    };
    map.createHashTable(keyValuePairs);
    std::cout << "Apple found in " << map.getValue("Apple").book << " " << map.getValue("Apple").count << " times" << endl;
    return 0;
}
