#ifndef INITIALISER_HPP
#define INITIALISER_HPP
#include "./hashmap.h"
#include "./arraylist.h"
#include "./trie.h"
#include "./fileReader.h"
using namespace std;

class initialiser{
    private:

    public:
        initialiser();
        static void getIndex(stringhashmap<arraylist<pair<string, float>>>* wordIndex, trie* autocomplete);
};

#endif