#include "../include/initialiser.h"

initialiser::initialiser()
{
}

void initialiser::getIndex(stringhashmap<arraylist<pair<string, float>>> *wordIndex, trie *autocomplete){
    try{
        *wordIndex = *stringhashmap<arraylist<pair<string, float>>>::deserialize("wordIndex.dat");
        *autocomplete = *trie::deserialize("autocomplete.dat");
    } catch(runtime_error e){
        fileReader reader = fileReader();
        reader.indexBooks(wordIndex, autocomplete);
    }
}