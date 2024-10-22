#include "../include/initialiser.h"

initialiser::initialiser()
{
}

void initialiser::getIndex(stringhashmap<arraylist<pair<string, float>>> *wordIndex, trie *autocomplete){
    // If hashmap and trie data files already exist then deserialize them and use them as the index and autocomplete
    try{
        *wordIndex = *stringhashmap<arraylist<pair<string, float>>>::deserialize("wordIndex.dat");
        *autocomplete = *trie::deserialize("autocomplete.dat");
    } catch(runtime_error e){
        // Otherwise, index all the books
        fileReader reader = fileReader();
        reader.indexBooks(wordIndex, autocomplete);
    }
}