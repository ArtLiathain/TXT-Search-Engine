#include "../include/trie.h"
#include <iostream>
#include <unordered_map>
using namespace std;

trie::trie()
{
    unordered_map<string, Node *> children;
    root = new Node{"", false, children};
}

trie::~trie()
{
}

void trie::insert(string word)
{
    Node *cur = root;
    for (int j = 0; j < word.length(); j++){
        word[j] = tolower(word[j]);
    }
    for (int i = 0; i < word.length(); i++)
    {
        string frag = word.substr(0, i + 1);
        Node *node;
        if (cur->children.count(frag) == 0)
        {
            unordered_map<string, Node *> children;
            node = new Node{"", false, children};
            cur->children[frag] = node;
        }
        else
        {
            node = cur->children[frag];
        }
        cur = node;
    }
    cur->endOfWord = true;
}

arraylist<string> trie::getArrayList()
{
    arraylist<string> result = arraylist<string>(10);
    Node *cur = root;
    for (auto x : cur->children)
    {
        getArrayList_rec(x.second->children, "", &result);
    }
    return result;
}

arraylist<string> trie::getArrayList_withPrefix(string prefix)
{
    for (int j = 0; j < prefix.length(); j++){
        prefix[j] = tolower(prefix[j]);
    }
    arraylist<string> result = arraylist<string>(10);
    Node *cur = root;
    for (auto x : cur->children)
    {
        getArrayList_rec(x.second->children, prefix, &result);
    }
    return result;
}

void trie::getArrayList_rec(unordered_map<std::string, Node *> children, string prefix, arraylist<string> *result)
{
    for (auto x : children)
    {
        if (x.second->endOfWord)
        {
            result->insert(x.first);
        }

        if (x.first.substr(0, prefix.length()) == prefix || prefix.substr(0, x.first.length()) == x.first)
        {
            getArrayList_rec(x.second->children, prefix, result);
        }
    }
}