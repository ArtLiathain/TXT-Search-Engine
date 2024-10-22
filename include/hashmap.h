#ifndef HASHMAP_H
#define HASHMAP_H

#include <bits/stdc++.h>
#include "./arraylist.h"
#include "./serialiseArraylist.h"
#include <optional>

#include <vector>
#include <utility> 
#include <string>  

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
    mutex readMutex;
    mutex writeMutex;
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
    stringhashmap(const stringhashmap<V> &other);
    stringhashmap(stringhashmap<V> &&other) noexcept;
    ~stringhashmap() noexcept;
    void initTable();
    void insert(const string &key, const V value, int tableID, int cnt, int n);
    void insert(const string &key, const V value);
    void remove(const string &key);
    V& getValue(const string &key);
    bool keyExists(const string &key);
    arraylist<string> getAllKeys();
    void createHashTable(arraylist<pair<string, V>> keyValuePairs);
    void serialize(const string &filename);
    static stringhashmap<V>* deserialize(const string &filename);
    stringhashmap<V>& operator=(const stringhashmap<V> &other);
    stringhashmap<V>& operator=(stringhashmap<V> &&other) noexcept;
};

template <typename V>
stringhashmap<V>::stringhashmap()
{
    MAXN = 2;
    ver = 2;
    pos = new int[ver];
    hashtable = new KeyValue<string, V>*();
    initTable();
}

template <typename V>
stringhashmap<V>::stringhashmap(int n)
{
    // Ensure MAXN is always greater than 0 to allow for proper resizing
    if(n >= 1){
        MAXN = n;
    }else{
        MAXN = 1;
    }
    ver = 2;
    pos = new int[ver];
    hashtable = new KeyValue<string, V>*();
    initTable();
}

template <typename V>
stringhashmap<V>::stringhashmap(const stringhashmap<V> &other) {
    MAXN = other.MAXN;
    ver = other.ver;
    pos = new int[ver];  
    copy(other.pos, other.pos + ver, pos);  

    hashtable = new KeyValue<string, V>*[ver];  // Allocate new hashtable
    for (int i = 0; i < ver; ++i) {
        hashtable[i] = new KeyValue<string, V>[MAXN];  // Allocate each row
        for (int j = 0; j < MAXN; ++j) {
            hashtable[i][j] = other.hashtable[i][j];  // Copy each element
        }
    }
}

template <typename V>
stringhashmap<V>& stringhashmap<V>::operator=(const stringhashmap<V> &other) {
    if (this == &other) {
        return *this;  // Handle self-assignment
    }

    // Free existing resources
    for (int i = 0; i < ver; ++i) {
        delete[] hashtable[i];
    }
    delete[] hashtable;
    delete[] pos;

    // Copy new values
    MAXN = other.MAXN;
    ver = other.ver;
    pos = new int[ver];  
    copy(other.pos, other.pos + ver, pos);  

    hashtable = new KeyValue<string, V>*[ver];  // Allocate new hashtable
    for (int i = 0; i < ver; ++i) {
        hashtable[i] = new KeyValue<string, V>[MAXN];  // Allocate each row
        for (int j = 0; j < MAXN; ++j) {
            hashtable[i][j] = other.hashtable[i][j];  // Copy each element
        }
    }

    return *this;
}

// Move Constructor
template <typename V>
stringhashmap<V>::stringhashmap(stringhashmap<V> &&other) noexcept {
    MAXN = other.MAXN;
    ver = other.ver;
    pos = other.pos;  // Take ownership of other's pos array
    hashtable = other.hashtable;  // Take ownership of other's hashtable

    other.pos = nullptr;  // Nullify other's pointers
    other.hashtable = nullptr;
}

// Move Assignment Operator
template <typename V>
stringhashmap<V>& stringhashmap<V>::operator=(stringhashmap<V> &&other) noexcept {
    if (this == &other) {
        return *this;  // Handle self-assignment
    }

    // Free existing resources
    for (int i = 0; i < ver; ++i) {
        delete[] hashtable[i];
    }
    delete[] hashtable;
    delete[] pos;

    // Steal other's resources
    MAXN = other.MAXN;
    ver = other.ver;
    pos = other.pos;
    hashtable = other.hashtable;

    // Nullify other's pointers
    other.pos = nullptr;
    other.hashtable = nullptr;

    return *this;
}

/* Function to retrieve the value associated with a key
 * key: Which key's value we want to retrieve */
template <typename V>
V& stringhashmap<V>::getValue(const string &key)
{
    writeMutex.lock();
    for (int i = 0; i < ver; i++)
    {
        int index = hashKey(i + 1, key);
        if (hashtable[i][index].key == key)
        {
            writeMutex.unlock();
            return hashtable[i][index].value.value();
        }
    }
    writeMutex.unlock();
    throw out_of_range("Key not found in the hash table.");
}

/* function to see if a key exists in the table
 * &key: Keyword to check*/
template <typename V>
bool stringhashmap<V>::keyExists(const string &key)
{
    writeMutex.lock();
    for (int i = 0; i < ver; i++)
    {
        int index = hashKey(i + 1, key);
        if (hashtable[i][index].key == key)
        {
            writeMutex.unlock();
            return true;
        }
    }
    writeMutex.unlock();
    return false;
}


/* function to place a key-value pair in one of its possible positions
 * &key: Keyword being hashed
 * value: Value object containing the amount of ocurrences and the book title
 * tableID: Which version of the table the key is being inserted into
 * cnt: Number of displacements
 * n: Amount of elements */
template <typename V>
void stringhashmap<V>::insert(const string &key, const V value, int tableID, int cnt, int n)
{
    readMutex.lock();
    writeMutex.lock();
    string curKey = key;
    V curValue = value;
    
    while (true)
    {
        if (cnt == n)
        {
            rehash();
            cnt = 0;  // Reset the count and tableID after rehash
            continue; // Start the insertion again
        }

        // Check if either of the two possible locations have the key
        for (int i = 0; i < ver; i++)
        {
            pos[i] = hashKey(i + 1, curKey);
            if (hashtable[i][pos[i]].key == curKey)
            {
                hashtable[i][pos[i]].value = move(curValue);
                readMutex.unlock();
                writeMutex.unlock();
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
            hashtable[tableID][pos[tableID]].key = move(curKey);
            hashtable[tableID][pos[tableID]].value = move(curValue);

            // Move to the next table and repeat the process with the displaced pair
            curKey = displacedKey;
            curValue = displacedValue;
            tableID = (tableID + 1) % ver;
            cnt++;
        }
        else
        {
            // If the current position is free, insert the key-value pair
            hashtable[tableID][pos[tableID]].key = move(curKey);
            hashtable[tableID][pos[tableID]].value = move(curValue);
            readMutex.unlock();
            writeMutex.unlock();
            return;
        }
    }
}

/* function to make insertion an easier interface for external classes or for when tableID, cnt and n are defaults
*/
template <typename V>
void stringhashmap<V>::insert(const string &key, const V value){
    int tableID = 0;
    int cnt = 0;
    int n = 1 + (MAXN / 2); // Add 1 to handle when MAXN = 1
    insert(key, value, tableID, cnt, n);
}


/* function to create a hashtable from an array list
 * &keyValuePairs: Vector of key value pairs received from text rank to take in as input*/
template <typename V>
void stringhashmap<V>::createHashTable(arraylist<pair<string, V>> keyValuePairs)
{
    readMutex.lock();
    writeMutex.lock();
    int n = keyValuePairs.length;

    for (int i = 0; i < n; i++)
    {
        readMutex.unlock();
        writeMutex.unlock();
        insert(keyValuePairs.get(i).first, keyValuePairs.get(i).second, 0, 0, n);
        readMutex.lock();
        writeMutex.lock();
    }
    readMutex.unlock();
    writeMutex.unlock();
}


/* function to return a list of all the keys in the hashtable*/
template <typename V>
arraylist<string> stringhashmap<V>::getAllKeys(){
    writeMutex.lock();
    arraylist<string> allKeys = arraylist<string>(MAXN);
    for (int i = 0; i < ver; i++){
        for(int j = 0; j < MAXN; j++){
            if (hashtable[i][j].value.has_value()){
                allKeys.insert(hashtable[i][j].key);
            }
        }
    }
    writeMutex.unlock();
    return allKeys;
}

template <typename V>
void stringhashmap<V>::remove(const string &key){
    readMutex.lock();
    writeMutex.lock();
    for (int i = 0; i < ver; i++)
    {
        int index = hashKey(i + 1, key);
        if (hashtable[i][index].key == key)
        {
            hashtable[i][index].value = nullopt;
            hashtable[i][index].key = "";
            readMutex.unlock();
            writeMutex.unlock();
            return;
        }
    }
    readMutex.unlock();
    writeMutex.unlock();
}

/* function to fill hash table with dummy values for initialisation */
template <typename V>
void stringhashmap<V>::initTable()
{
    readMutex.lock();
    writeMutex.lock();
    hashtable = new KeyValue<string, V>*[ver]; // Allocate rows for 'ver' tables
    for (int i = 0; i < ver; i++)
    {
        hashtable[i] = new KeyValue<string, V>[MAXN]; // Allocate columns based on MAXN
        for (int j = 0; j < MAXN; j++)
        {
            hashtable[i][j].key = "";
            hashtable[i][j].value = nullopt; // Initialize to null
        }
    }
    readMutex.unlock();
    writeMutex.unlock();
}

/* Simple hash function for strings
 * function: Which version of the hash function we want to use
 * &key: Reference to the keyword being hashed*/
template <typename V>
int stringhashmap<V>::hashKey(int function, const string &key) {
    size_t hashValue = 0;  // Use size_t for intermediate result to avoid overflow

    if (function == 1) {
        // Polynomial rolling hash with a small prime number base (e.g., 31)
        const int base = 31;
        for (char c : key) {
            hashValue = (hashValue * base + c) % MAXN;
        }
        return static_cast<int>(hashValue);  // Convert to int at the end
    }
    else if (function == 2) {
        // Similar to the first but with different weighting to reduce collisions
        const int base = 37;  // Different base to ensure varied hash functions
        for (size_t i = 0; i < key.length(); i++) {
            hashValue = (hashValue * base + key[i]) % MAXN;
        }
        return static_cast<int>(hashValue);  // Convert to int at the end
    }
    else {
        throw invalid_argument("Invalid hash function version");
    }
}

/*Function to double the size of the hashtable and rehash the current elements to properly populate the new table*/
template <typename V>
void stringhashmap<V>::rehash() {
    int oldMAXN = MAXN; // Save the old size
    MAXN *= 2; // Double the size
    KeyValue<string, V>** oldTable = hashtable; // Keep reference to old table

    // Initialize new hashtable
    hashtable = new KeyValue<string, V>*[ver];
    for (int i = 0; i < ver; i++) {
        hashtable[i] = new KeyValue<string, V>[MAXN];
        for (int j = 0; j < MAXN; j++) {
            hashtable[i][j].key = "";
            hashtable[i][j].value = nullopt; // Initialize to nullopt
        }
    }

    // Rehash existing elements
    for (int i = 0; i < ver; i++) {
        for (int j = 0; j < oldMAXN; j++) {
            if (oldTable[i][j].value.has_value()) { // Only rehash if there is a value
                string key = oldTable[i][j].key;
                V value = oldTable[i][j].value.value();
                bool inserting = true;
                int tableID = i;
                while(inserting){
                    // Check if either of the two possible locations have the key
                    for (int k = 0; k < ver; k++)
                    {
                        pos[k] = hashKey(k + 1, key);
                        if (hashtable[k][pos[k]].key == key)
                        {
                            hashtable[k][pos[k]].value = move(value);
                            inserting = false;
                        }
                    }
                
                    // Check if the current position is occupied
                    if (hashtable[tableID][pos[tableID]].value.has_value())
                    {
                        // Displace the current key-value pair
                        string displacedKey = hashtable[tableID][pos[tableID]].key;
                        V displacedValue = hashtable[tableID][pos[tableID]].value.value();

                        // Insert the new key-value pair
                        hashtable[tableID][pos[tableID]].key = move(key);
                        hashtable[tableID][pos[tableID]].value = move(value);

                        // Move to the next table and repeat the process with the displaced pair
                        key = displacedKey;
                        value = displacedValue;
                        tableID = (tableID + 1) % ver;
                    }
                    else
                    {
                        // If the current position is free, insert the key-value pair
                        hashtable[tableID][pos[tableID]].key = move(key);
                        hashtable[tableID][pos[tableID]].value = move(value);
                        inserting = false;
                    }
                }
            
        }
        }
        delete[] oldTable[i]; // Clean up old table row
    }
    delete[] oldTable; // Clean up old table
}

template <typename V>
void stringhashmap<V>::serialize(const string& filename) {
    readMutex.lock();
    writeMutex.lock();
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        readMutex.unlock();
        writeMutex.unlock();
        throw runtime_error("Error: Failed to open file for writing.");
    }

    // Write the basic metadata
    file.write(reinterpret_cast<const char*>(&MAXN), sizeof(MAXN));
    file.write(reinterpret_cast<const char*>(&ver), sizeof(ver));

    // Write the pos array
    file.write(reinterpret_cast<const char*>(pos), sizeof(int) * ver);

    // Write the hashtable contents
    // Loop through the cuckoo versions
    for (int i = 0; i < ver; i++) {
        // Loop through all columns
        for (int j = 0; j < MAXN; j++) {
            // Serialize the size of the key string
            size_t key_size = hashtable[i][j].key.size();
            file.write(reinterpret_cast<const char*>(&key_size), sizeof(key_size));
            // Serialize the key
            file.write(hashtable[i][j].key.c_str(), key_size);

            // Serialize whether the value is null or not
            bool has_value = hashtable[i][j].value.has_value();
            file.write(reinterpret_cast<const char*>(&has_value), sizeof(bool));
            if (has_value) {
                // If the value isnt null then retrieve the arraylist value from the hashtable
                V value = hashtable[i][j].value.value();
                // Serialize the arraylist to a string for ease of binary serialisation
                serialiseArraylist serialiser = serialiseArraylist();
                string serializedValue = serialiser.serialiseArraylistIntoString(value);
                
                // Serialize the size of the value string
                size_t value_size = serializedValue.size();
                file.write(reinterpret_cast<const char*>(&value_size), sizeof(value_size));
                
                // Serialize the value
                file.write(serializedValue.c_str(), value_size);
            }
        }
    }

    file.close();
    readMutex.unlock();
    writeMutex.unlock();

}



template <typename V>
stringhashmap<V>* stringhashmap<V>::deserialize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw runtime_error("Error: Failed to open file for reading.");
    }

    // Read the metadata (MAXN and ver)
    int MAXN_read, ver_read;
    file.read(reinterpret_cast<char*>(&MAXN_read), sizeof(MAXN_read));
    file.read(reinterpret_cast<char*>(&ver_read), sizeof(ver_read));
    // Create a new hashmap object with the read MAXN and assign the ver
    stringhashmap<V>* hashmap = new stringhashmap<V>(MAXN_read);
    hashmap->MAXN = MAXN_read;
    hashmap->ver = ver_read;


    // Read the pos array
    hashmap->pos = new int[ver_read];
    file.read(reinterpret_cast<char*>(hashmap->pos), sizeof(int) * ver_read);


    hashmap->hashtable = new KeyValue<string, V>*[ver_read];

    // Read the hashtable contents
    for (int i = 0; i < ver_read; i++) {
        hashmap->hashtable[i] = new KeyValue<string, V>[MAXN_read];  // Allocate memory for each row of the hashtable
        for (int j = 0; j < MAXN_read; j++) {
            // Read the size of the key string
            size_t key_size;
            file.read(reinterpret_cast<char*>(&key_size), sizeof(key_size));
            // Size the key string to the read size and initialise to all spaces
            string key(key_size, ' ');
            // Read the key from the file
            file.read(key.data(), key_size);

            // Read whether or not the associated value is null
            bool has_value;
            file.read(reinterpret_cast<char*>(&has_value), sizeof(bool));
            
            // Set the key in the hashtable
            hashmap->hashtable[i][j].key = key;
            if (has_value) {
                // If the value is not null then read the length of the value string
                size_t length;
                file.read(reinterpret_cast<char*>(&length), sizeof(length));
                // Resize the serializedValue string to the length and default to all spaces
                string serializedValue(length, ' ');
                // Read the serialized value from the file
                file.read(&serializedValue[0], length);
                
                // Convert the string to arraylist
                serialiseArraylist serialiser = serialiseArraylist();
                arraylist<pair<string, float>> value = serialiser.deserialiseintoArraylist(serializedValue);
                // Assign the value in the hashtable
                hashmap->hashtable[i][j].value = value;
            } else {
                hashmap->hashtable[i][j].value = nullopt;
            }
        }
    }
    file.close();

    return hashmap;
}

template <typename V>
stringhashmap<V>::~stringhashmap() noexcept{
    for (int i = 0; i < ver; i++) {
        delete[] hashtable[i]; // Delete each row
    }
    delete[] hashtable; // Delete the array of row pointers
    delete[] pos; // Delete the pos array
}


#endif