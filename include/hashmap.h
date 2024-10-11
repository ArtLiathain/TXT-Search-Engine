#ifndef HASHMAP_H
#define HASHMAP_H

#include <bits/stdc++.h>

#include <vector>
#include <utility> // For std::pair
#include <string>  // For std::string

using namespace std;

struct Value
{
    int count;
    string book;

    Value() : count(-1), book("") {}

    Value(int n, const string &t) : count(n), book(t) {}
};

// Structure to hold key-value pairs
struct KeyValue
{
    string key;
    Value value;

    KeyValue() : key(""), value() {} // Default constructor, value set to -1 to indicate empty
};

// Amount of versions of the hash function we want to use, most common amount in cuckoo hashing is 2
#define ver 2

class Hashmap
{
private:
    int hashKey(int function, const string &key);
    // Global variable for max number of buckets to be dynamically set based on the size of the input
    int MAXN;
    KeyValue **hashtable;

    // Array to store possible positions for a key
    int pos[ver];

public:
    void initTable();
    void place(const string &key, const Value &value, int tableID, int cnt, int n);
    Value getValue(const string &key);
    void printTable();
    void createHashTable(const vector<pair<string, Value>> &keyValuePairs);
};

#endif