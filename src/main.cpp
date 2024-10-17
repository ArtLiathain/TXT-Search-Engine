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

    for (int i = 0; i < books.length; i++){
        reader.readFile(books.get(i), &wordIndex);
        searchIndex[books.get(i)] = 0;
    }
    search.orFunc("shawl", &searchIndex, &wordIndex);
    search.andFunc("piece", &searchIndex, &wordIndex);
    for (auto x : searchIndex){
        cout << x.first << " " << x.second << "\n";
    }
    search.andFunc("doll", &searchIndex, &wordIndex);

    for (auto b : searchIndex){
        cout << b.first << " " << b.second << "\n";
    }
    return 0;
}
