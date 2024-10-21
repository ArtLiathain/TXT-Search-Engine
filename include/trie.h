#ifndef TRIE_H
#define TRIE_H
#include <unordered_map>
#include <iostream>
#include "../include/arraylist.h"
#include "../include/hashmap.h"
using namespace std;

class trie
{
public:
    struct Node
    {
        std::string key;
        bool endOfWord;
        stringhashmap<Node*> children;

        Node& operator=(const Node& other) {
            // Check for self-assignment
            if (this == &other) {
                return *this;
            }

            // Copy each member individually
            this->key = other.key;
            this->endOfWord = other.endOfWord;
            
            // Deep copy for the children map
            this->children = other.children; 

            return *this;
        }
    };

    void insert(std::string value);
    trie(/* args */);
    trie(const trie &other);
    trie(trie &&other) noexcept;
    ~trie();
    arraylist<string> getArrayList();
    arraylist<string> getArrayList_withPrefix(string prefix);
    void getArrayList_rec(stringhashmap<trie::Node *> children, string prefix, arraylist<string> * result);
    void serialize(const string &filename);
    static trie deserialize(const string &filename);
    trie& operator=(const trie &other);
    trie& operator=(trie &&other) noexcept;

private:
    Node *root;

};

#endif
