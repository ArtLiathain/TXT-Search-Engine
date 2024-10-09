#include <iostream>
#include "../include/trie.h"
#include "../include/Arraylist.h"
using namespace std;

int main(int argc, char const *argv[])
{
    trie autoComplete;
    
    autoComplete.insert("Kiki");
    autoComplete.insert("Kiiiiiiidi");
    autoComplete.insert("Cookie");

    Arraylist<string> trieValues = autoComplete.getArrayList();

    for(int i = 0; i < trieValues.length; i++){
        cout << trieValues.get(i) << "\n";
    }

    Arraylist<string> trieValuess = autoComplete.getArrayList_withPrefix("Ki");

    for(int i = 0; i < trieValuess.length; i++){
        cout << trieValuess.get(i) << "\n";
    }

    return 0;
}
