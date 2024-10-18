#include <iostream>
#include "../include/fileReader.h"
#include "../include/searchIndex.h"
#include <unordered_map>
using namespace std;
int main(int argc, char const *argv[])
{
    fileReader reader = fileReader();
    searchIndex search = searchIndex();
    arraylist<string> books = reader.getBooks();
    unordered_map<string, arraylist<pair<string, float>>> wordIndex;
    unordered_map<string, float> searchIndex;

    
    search.orFunc(&searchIndex, &wordIndex["piece"]);
    search.andFunc(&searchIndex, &wordIndex["piece"]);
    for (auto x : searchIndex){
        cout << x.first << " " << x.second << "\n";
    }
    search.andFunc(&searchIndex, &wordIndex["doll"]);

    for (auto b : searchIndex){
        cout << b.first << " " << b.second << "\n";
    }
    return 0;
}
