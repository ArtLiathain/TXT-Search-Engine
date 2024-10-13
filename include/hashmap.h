#ifndef HASHMAP_H
#define HASHMAP_H

#include <bits/stdc++.h>
#include "./arraylist.h"
#include <optional>

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

    bool operator!=(const Value &other) const {
        return count != other.count || book != other.book;
    }

    bool operator==(const Value &other) const {
        return count == other.count && book == other.book;
    }

    friend std::ostream& operator<<(std::ostream &os, const Value &v) {
        os << "{count: " << v.count << ", book: \"" << v.book << "\"}";
        return os;
    }
};

// Structure to hold key-value pairs
template <typename K, typename V>
struct KeyValue
{
    K key;
    optional<V> value;

    KeyValue() : key(""), value(nullopt) {}
};

template <typename K, typename V>
class hashmap
{
private:
    // Global variable for max number of buckets to be dynamically set based on the size of the input
    int MAXN;
    // Amount of versions of the hash function. Standard for cuckoo hashing is 2
    int ver; 
    // Array to store possible positions for a key
    int *pos;

    void rehash();
    int hashKey(int function, const K &key);

public:
    KeyValue<K, V> **hashtable;
    hashmap();
    hashmap(int n);
    ~hashmap();
    void initTable();
    void add(const K &key, const V &value, int tableID, int cnt, int n);
    void add(const K &key, const V &value);
    V getValue(const K &key);
    void printTable();
    void createHashTable(arraylist<pair<K, V>> &keyValuePairs);
};


template <typename K, typename V>
hashmap<K, V>::hashmap(int n)
{
    static_assert(std::is_convertible<K, std::string>::value, 
            "Key type K must be derived from or convertible to std::string");
    MAXN = n;
    ver = 2;
    pos = new int[ver];
    hashtable = new KeyValue<K, V>*();
    initTable();
}

template <typename K, typename V>
hashmap<K, V>::hashmap()
{
    static_assert(std::is_convertible<K, std::string>::value, 
            "Key type K must be derived from or convertible to std::string");
    MAXN = 1;
    ver = 2;
    pos = new int[ver];
    hashtable = new KeyValue<K, V>*();
    initTable();
}

/* Function to retrieve the value associated with a key
 * key: Which key's value we want to retrieve */
template <typename K, typename V>
V hashmap<K, V>::getValue(const K &key)
{
    for (int i = 0; i < ver; i++)
    {
        int index = hashKey(i + 1, key);
        if (hashtable[i][index].key == key)
        {
            return hashtable[i][index].value.value();
        }
    }
    return V();
}

/* function to place a key-value pair in one of its possible positions
 * &key: Keyword being hashed
 * &value: Value object containing the amount of ocurrences and the book title
 * tableID: Which version of the table the key is being inserted into
 * cnt: Number of displacements
 * n: Amount of elements */
template <typename K, typename V>
void hashmap<K, V>::add(const K &key, const V &value, int tableID, int cnt, int n)
{
    if (cnt == n)
    {
        printf("%s unpositioned\n", key.c_str());
        printf("Cycle present. REHASH.\n");
        rehash();
        add(key, value, tableID, cnt, n*2);
        return;
    }

    for (int i = 0; i < ver; i++)
    {
        pos[i] = hashKey(i + 1, key);
        if (hashtable[i][pos[i]].key == key)
        {
            hashtable[i][pos[i]].value = value;
            return;
        }
    }

    if (hashtable[tableID][pos[tableID]].value.has_value())
    {
        K displacedKey = hashtable[tableID][pos[tableID]].key;
        V displacedValue = hashtable[tableID][pos[tableID]].value.value();

        hashtable[tableID][pos[tableID]].key = key;
        hashtable[tableID][pos[tableID]].value = value;

        add(displacedKey, displacedValue, (tableID + 1) % ver, cnt + 1, n);
    }
    else
    {
        hashtable[tableID][pos[tableID]].key = key;
        hashtable[tableID][pos[tableID]].value = value;
    }
}

template <typename K, typename V>
void hashmap<K, V>::add(const K &key, const V &value)
{
    int tableID = 0;
    int cnt = 0;
    int n = MAXN / 2;
    if (cnt == n)
    {
        printf("%s unpositioned\n", key.c_str());
        printf("Cycle present. REHASH.\n");
        rehash();
        add(key, value);
        return;
    }

    for (int i = 0; i < ver; i++)
    {
        pos[i] = hashKey(i + 1, key);
        if (hashtable[i][pos[i]].key == key)
        {
            hashtable[i][pos[i]].value = value;
            return;
        }
    }

    if (hashtable[tableID][pos[tableID]].value.has_value())
    {
        K displacedKey = hashtable[tableID][pos[tableID]].key;
        V displacedValue = hashtable[tableID][pos[tableID]].value.value();

        hashtable[tableID][pos[tableID]].key = key;
        hashtable[tableID][pos[tableID]].value = value;

        add(displacedKey, displacedValue, (tableID + 1) % ver, cnt + 1, n);
    }
    else
    {
        hashtable[tableID][pos[tableID]].key = key;
        hashtable[tableID][pos[tableID]].value = value;
    }
}

/* function to create a hashtable from an array list
 * &keyValuePairs: Vector of key value pairs received from text rank to take in as input*/
template <typename K, typename V>
void hashmap<K, V>::createHashTable(arraylist<pair<K, V>> &keyValuePairs)
{
    int n = keyValuePairs.length;

    for (int i = 0; i < n; i++)
    {
        add(keyValuePairs.get(i).first, keyValuePairs.get(i).second, 0, 0, n);
    }

    printTable();
}

/* function to print hash table contents */
template <typename K, typename V>
void hashmap<K, V>::printTable()
{
    printf("Final hash tables:\n");
    for (int i = 0; i < ver; i++, printf("\n"))
    {
        for (int j = 0; j < MAXN; j++)
        {
            if (hashtable[i][j].value.has_value())
                std::cout << hashtable[i][j].key.c_str() << ":" << hashtable[i][j].value.value() << " ";
            else
                printf("- ");
        }
    }
    printf("\n");
}

/* function to fill hash table with dummy values for initialisation */
template <typename K, typename V>
void hashmap<K, V>::initTable()
{
    hashtable = new KeyValue<K, V>*[ver]; // Allocate rows for 'ver' tables
    for (int i = 0; i < ver; i++)
    {
        hashtable[i] = new KeyValue<K, V>[MAXN]; // Allocate columns based on MAXN
        for (int j = 0; j < MAXN; j++)
        {
            hashtable[i][j].value = nullopt; // Initialize to default
        }
    }
}

/* Simple hash function for strings
 * function: Which version of the hash function we want to use
 * &key: Reference to the keyword being hashed*/
template <typename K, typename V>
int hashmap<K, V>::hashKey(int function, const K &key)
{
    int hashValue = 0;
    if (function == 1)
    {
        for (char c : key)
        {
            hashValue += c; // Simple character sum
        }
        return hashValue % MAXN;
    }
    else if (function == 2)
    {
        for (size_t i = 0; i < key.length(); i++)
        {
            hashValue += (i + 1) * key[i]; // Weighted character sum
        }
        return hashValue % MAXN;
    }
    else
    {
        throw std::invalid_argument("Invalid hash function version");
    }
}

template <typename K, typename V>
void hashmap<K, V>::rehash() {
    int oldMAXN = MAXN; // Save the old size
    MAXN *= 2; // Double the size
    KeyValue<K, V>** oldTable = hashtable; // Keep reference to old table

    // Initialize new hashtable
    hashtable = new KeyValue<K, V>*[ver];
    for (int i = 0; i < ver; i++) {
        hashtable[i] = new KeyValue<K, V>[MAXN];
        for (int j = 0; j < MAXN; j++) {
            hashtable[i][j].value = nullopt; // Initialize to nullopt
        }
    }

    // Rehash existing elements
    for (int i = 0; i < ver; i++) {
        for (int j = 0; j < oldMAXN; j++) {
            if (oldTable[i][j].value.has_value()) { // Only rehash if there is a value
                const K &key = oldTable[i][j].key;
                const V &value = oldTable[i][j].value.value();

                // Use the add function to insert the key-value pair into the new table
                add(key, value, i, 0, oldMAXN); // Insert into the new hashtable
            }
        }
        delete[] oldTable[i]; // Clean up old table row
    }
    delete[] oldTable; // Clean up old table
}

template <typename K, typename V>
hashmap<K, V>::~hashmap() {
    for (int i = 0; i < ver; i++) {
        delete[] hashtable[i]; // Delete each row
    }
    delete[] hashtable; // Delete the array of row pointers
    delete[] pos; // Delete the pos array
}


#endif