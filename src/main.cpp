#include <iostream>
#include "../include/LinkedList.h"
#include "../include/Hashmap.h"

int main(int argc, char const *argv[])
{
    LinkedList<int>  temp;
    temp.add(5);
    std::cout << temp.get(0) << "\n";
    std::cout << "Hello World" << "\n";
    Hashmap hashmap;
    vector<pair<string, Value>> keyValuePairs = {
        make_pair("Apple", Value{10, "Book A"}),
        make_pair("Banana", Value{5, "Book B"}),
        make_pair("Strawberry", Value{5, "Book C"}),
        make_pair("Orange", Value{3, "Book D"}),
        make_pair("Grapes", Value{7, "Book E"})
    };
    hashmap.createHashTable(keyValuePairs);
    std::cout << "Apple found in " << hashmap.getValue("Apple").book << " " << hashmap.getValue("Apple").count << " times" << endl;
    return 0;
}
