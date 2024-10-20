#include <iostream>
#include "../include/arraylist.h"
#include "../include/fileReader.h"
#include "../include/hashmap.h"
using namespace std;

int main(int argc, char const *argv[])
{
    // auto startread = std::chrono::high_resolution_clock::now();
    // fileReader reader = fileReader();
    // arraylist<string> books = reader.getBooks();

    // // for (int i = 0; i < books.length; i++){
    // //     reader.readFile(books.get(i));
    // // }
    // auto endread = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> durationread = endread - startread;
    // std::cout << "File indexing took " << durationread.count() << " seconds" << std::endl;
    

    auto start = std::chrono::high_resolution_clock::now();
    arraylist<pair<string, Value>> keyValuePairs = arraylist<pair<string, Value>>(10);
    keyValuePairs.insert(make_pair("Apple", Value{10, "Book A"}));
    keyValuePairs.insert(make_pair("Banana", Value{5, "Book B"}));
    keyValuePairs.insert(make_pair("Strawberry", Value{5, "Book C"}));
    keyValuePairs.insert(make_pair("Orange", Value{3, "Book D"}));
    keyValuePairs.insert(make_pair("Grapes", Value{7, "Book E"}));
    stringhashmap<Value> map = stringhashmap<Value>(keyValuePairs.length);
    map.createHashTable(keyValuePairs);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Hashtable creation took " << duration.count() << " seconds" << std::endl;
    
    std::cout << "Apple found in " << map.getValue("Apple").book << " " << map.getValue("Apple").count << " times" << endl;
    std::cout << "Dog found in " << map.getValue("Dog").book << " " << map.getValue("Dog").count << " times" << endl;
    
    
    auto start2 = std::chrono::high_resolution_clock::now();
    arraylist<pair<string, arraylist<pair<string, float>>>> keyIntPairs = arraylist<pair<string, arraylist<pair<string, float>>>>(3);
    arraylist<pair<string, float>> Array1 = arraylist<pair<string, float>>(15);

    Array1.insert(pair("apple", 1.0f));
    Array1.insert(pair("banana", 0.8f));
    Array1.insert(pair("orange", 1.5f));
    keyIntPairs.insert(pair("key1", Array1));
    stringhashmap<arraylist<pair<string, float>>> map2 = stringhashmap<arraylist<pair<string, float>>>(1);
    map2.createHashTable(keyIntPairs);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << "Hashtable creation took " << duration2.count() << " seconds" << std::endl;
    
    std::cout << "Apple found " << map2.getValue("key1").get(0).second << " times" << endl;

    stringhashmap<arraylist<pair<string, float>>> restored = stringhashmap<arraylist<pair<string, float>>>::deserialize("hashmap.dat");

    std::cout << "Apple found in restored hashmap " << restored.getValue("key1").get(0).second << " times" << endl;

    arraylist<string> keys = map2.getAllKeys();
    for(int i = 0; i < keys.length; i++){
        std::cout << keys.get(i) << endl;
    }

    map2.remove("key1");
    arraylist<string> keys2 = map2.getAllKeys();
    for(int i = 0; i < keys2.length; i++){
        std::cout << keys2.get(i) << endl;
    }


    return 0;
}
