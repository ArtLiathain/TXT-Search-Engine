#ifndef TRIE_H
#define TRIE_H
#include <unordered_map>
#include <iostream>
#include "../include/arraylist.h"
using namespace std;

class trie
{
    struct Node
    {
        std::string key;
        bool endOfWord;
        unordered_map<string, Node *> children;
    };

private:
    Node *root;

public:
    void insert(std::string value);
    trie(/* args */);
    ~trie();
    arraylist<string> getArrayList();
    arraylist<string> getArrayList_withPrefix(string prefix);
    void getArrayList_rec(unordered_map<std::string, Node *> children,string prefix ,arraylist<string> * result);
};

#endif
