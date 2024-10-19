#ifndef HASHMAP_H
#define HASHMAP_H

#include <bits/stdc++.h>
#include "./arraylist.h"
#include <optional>

#include <vector>
#include <utility> // For std::pair
#include <string>  // For std::string

#include <mutex>

using namespace std;

// Structure to hold key-value pairs
template <typename K, typename V>
struct KeyValue
{
    K key;
    optional<V> value;

    KeyValue() : key(""), value(nullopt) {}
};

template <typename V>
class stringhashmap
{
private:
    mutex mtx;
    // Amount of versions of the hash function. Standard for cuckoo hashing is 2
    int ver; 
    // Array to store possible positions for a key
    int *pos;

    void rehash();
    int hashKey(int function, const string &key);

public:
    // Global variable for max number of buckets to be dynamically set based on the size of the input
    int MAXN;
    KeyValue<string, V> **hashtable;
    stringhashmap();
    stringhashmap(int n);
    ~stringhashmap();
    void initTable();
    void insert(const string &key, const V &value, int tableID, int cnt, int n);
    void insert(const string &key, const V &value);
    void remove(const string &key);
    V getValue(const string &key);
    arraylist<string> getAllKeys();
    void printTable();
    void createHashTable(arraylist<pair<string, V>> &keyValuePairs);
};


template <typename V>
stringhashmap<V>::stringhashmap(int n)
{
    MAXN = n;
    ver = 2;
    pos = new int[ver];
    hashtable = new KeyValue<string, V>*();
    initTable();
}

template <typename V>
stringhashmap<V>::stringhashmap()
{
    MAXN = 1;
    ver = 2;
    pos = new int[ver];
    hashtable = new KeyValue<string, V>*();
    initTable();
}

/* Function to retrieve the value associated with a key
 * key: Which key's value we want to retrieve */
template <typename V>
V stringhashmap<V>::getValue(const string &key)
{
    std::lock_guard<std::mutex> lock(mtx);
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
template <typename V>
void stringhashmap<V>::insert(const string &key, const V &value, int tableID, int cnt, int n)
{
    string curKey = key;
    V curValue = value;
    
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        if (cnt == n)
        {
            printf("%s unpositioned\n", curKey.c_str());
            printf("Cycle present. REHASH.\n");
            lock.unlock(); // Unlock and lock mutex before and after rehash to avoid deadlock
            rehash();
            printf("Rehashed\n");
            lock.lock();
            cnt = 0;  // Reset the count and tableID after rehash
            continue; // Start the insertion again
        }

        // Check if either of the two possible locations have the key
        for (int i = 0; i < ver; i++)
        {
            pos[i] = hashKey(i + 1, curKey);
            if (hashtable[i][pos[i]].key == curKey)
            {
                hashtable[i][pos[i]].value = curValue;
                return;
            }
        }

        // Check if the current position is occupied
        if (hashtable[tableID][pos[tableID]].value.has_value())
        {
            // Displace the current key-value pair
            string displacedKey = hashtable[tableID][pos[tableID]].key;
            V displacedValue = hashtable[tableID][pos[tableID]].value.value();

            // Insert the new key-value pair
            hashtable[tableID][pos[tableID]].key = curKey;
            hashtable[tableID][pos[tableID]].value = curValue;

            // Move to the next table and repeat the process with the displaced pair
            curKey = displacedKey;
            curValue = displacedValue;
            tableID = (tableID + 1) % ver;
            cnt++;
        }
        else
        {
            // If the current position is free, insert the key-value pair
            hashtable[tableID][pos[tableID]].key = curKey;
            hashtable[tableID][pos[tableID]].value = curValue;
            return;
        }
    }
}

/* function to make insertion an easier interface for external classes or for when tableID, cnt and n are defaults
*/
template <typename V>
void stringhashmap<V>::insert(const string &key, const V &value){
    int tableID = 0;
    int cnt = 0;
    int n = MAXN / 2;
    insert(key, value, tableID, cnt, n);
}


/* function to create a hashtable from an array list
 * &keyValuePairs: Vector of key value pairs received from text rank to take in as input*/
template <typename V>
void stringhashmap<V>::createHashTable(arraylist<pair<string, V>> &keyValuePairs)
{
    std::unique_lock<std::mutex> lock(mtx);
    int n = keyValuePairs.length;

    for (int i = 0; i < n; i++)
    {
        lock.unlock();
        insert(keyValuePairs.get(i).first, keyValuePairs.get(i).second, 0, 0, n);
        lock.lock();
    }

    lock.unlock();
    printTable();
}

/* function to print hash table contents */
template <typename V>
void stringhashmap<V>::printTable()
{
    std::lock_guard<std::mutex> lock(mtx);
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

/* function to return a list of all the keys in the hashtable*/
template <typename V>
arraylist<string> stringhashmap<V>::getAllKeys(){
    std::lock_guard<std::mutex> lock(mtx);
    arraylist<string> allKeys = arraylist<string>(MAXN);
    for (int i = 0; i < ver; i++){
        for(int j = 0; j < MAXN; j++){
            if (hashtable[i][j].value.has_value()){
                allKeys.insert(hashtable[i][j].key);
            }
        }
    }
    return allKeys;
}

template <typename V>
void stringhashmap<V>::remove(const string &key){
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < ver; i++)
    {
        int index = hashKey(i + 1, key);
        if (hashtable[i][index].key == key)
        {
            hashtable[i][index].value = nullopt;
            hashtable[i][index].key = "";
            return;
        }
    }
}

/* function to fill hash table with dummy values for initialisation */
template <typename V>
void stringhashmap<V>::initTable()
{
    std::lock_guard<std::mutex> lock(mtx);
    hashtable = new KeyValue<string, V>*[ver]; // Allocate rows for 'ver' tables
    for (int i = 0; i < ver; i++)
    {
        hashtable[i] = new KeyValue<string, V>[MAXN]; // Allocate columns based on MAXN
        for (int j = 0; j < MAXN; j++)
        {
            hashtable[i][j].value = nullopt; // Initialize to null
        }
    }
}

/* Simple hash function for strings
 * function: Which version of the hash function we want to use
 * &key: Reference to the keyword being hashed*/
template <typename V>
int stringhashmap<V>::hashKey(int function, const string &key)
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

/*Function to double the size of the hashtable and rehash the current elements to properly populate the new table*/
template <typename V>
void stringhashmap<V>::rehash() {
    std::unique_lock<std::mutex> lock(mtx);
    int oldMAXN = MAXN; // Save the old size
    MAXN *= 2; // Double the size
    KeyValue<string, V>** oldTable = hashtable; // Keep reference to old table

    // Initialize new hashtable
    hashtable = new KeyValue<string, V>*[ver];
    for (int i = 0; i < ver; i++) {
        hashtable[i] = new KeyValue<string, V>[MAXN];
        for (int j = 0; j < MAXN; j++) {
            hashtable[i][j].value = nullopt; // Initialize to nullopt
        }
    }

    // Rehash existing elements
    for (int i = 0; i < ver; i++) {
        for (int j = 0; j < oldMAXN; j++) {
            if (oldTable[i][j].value.has_value()) { // Only rehash if there is a value
                const string &key = oldTable[i][j].key;
                const V &value = oldTable[i][j].value.value();

                lock.unlock();
                // Use the insert function to insert the key-value pair into the new table
                insert(key, value, i, 0, oldMAXN); // Insert into the new hashtable
                lock.lock();
            }
        }
        delete[] oldTable[i]; // Clean up old table row
    }
    delete[] oldTable; // Clean up old table
}

template <typename V>
stringhashmap<V>::~stringhashmap() {
    for (int i = 0; i < ver; i++) {
        delete[] hashtable[i]; // Delete each row
    }
    delete[] hashtable; // Delete the array of row pointers
    delete[] pos; // Delete the pos array
}


#endif