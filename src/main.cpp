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

    arraylist<pair<string, Value>> keyValuePairs = arraylist<pair<string, Value>>(10);
    keyValuePairs.insert(make_pair("Apple", Value{10, "Book A"}));
    keyValuePairs.insert(make_pair("Banana", Value{5, "Book B"}));
    keyValuePairs.insert(make_pair("Strawberry", Value{5, "Book C"}));
    keyValuePairs.insert(make_pair("Orange", Value{3, "Book D"}));
    keyValuePairs.insert(make_pair("Grapes", Value{7, "Book E"}));
    hashmap<string, Value> map = hashmap<string, Value>(keyValuePairs.length);
    map.createHashTable(keyValuePairs);
    std::cout << "Apple found in " << map.getValue("Apple").book << " " << map.getValue("Apple").count << " times" << endl;
    std::cout << "Dog found in " << map.getValue("Dog").book << " " << map.getValue("Dog").count << " times" << endl;
    
    arraylist<pair<string, int>> keyIntPairs = arraylist<pair<string, int>>(3);
    keyIntPairs.insert(make_pair("Apple", 12));
    keyIntPairs.insert(make_pair("Banana", 6));
    keyIntPairs.insert(make_pair("Strawberry", 5));
    keyIntPairs.insert(make_pair("Orange", 7));
    keyIntPairs.insert(make_pair("Grapes", 7));
    keyIntPairs.insert(make_pair("Strawberry", 12));
    hashmap<string, int> map2 = hashmap<string, int>(1);
    map2.createHashTable(keyIntPairs);
    std::cout << "Apple found " << map2.getValue("Apple") << " times" << endl;
    std::cout << "Dog found " << map2.getValue("Dog") << " times" << endl;

    // This currently throws a segmentation fault at the end of the run as it tries deleting map2 twice. Once when deleting doublemap and once when deleting map2
    // hashmap<string, hashmap<string, int>> doublemap = hashmap<string, hashmap<string, int>>(2);
    // doublemap.add("Apple", &map2);
    // std::cout << "Apple found in double layer map " << doublemap.getValue("Apple").getValue("Apple") << " times" << endl;
    // std::cout << "Dog found in double layer map " << doublemap.getValue("Dog").getValue("Dog") << " times" << endl;

    return 0;
}
