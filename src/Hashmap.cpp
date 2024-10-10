#include <Hashmap.h>


/* function to fill hash table with dummy values for initialisation */
void Hashmap::initTable() {
    hashtable = new KeyValue*[ver];  // Allocate rows for 'ver' tables
    for (int i = 0; i < ver; i++) {
        hashtable[i] = new KeyValue[MAXN];  // Allocate columns based on MAXN
        for (int j = 0; j < MAXN; j++) {
            hashtable[i][j].value = Value();  // Initialize to default Value (-1 for count, "" for book)
        }
    }
}


/* Simple hash function for strings 
    * function: Which version of the hash function we want to use
    * &key: Reference to the keyword being hashed*/
// TODO: Check if these hash functions are sufficient
int Hashmap::hashKey(int function, const string &key) {
    int hashValue = 0;
    if (function == 1) {
        for (char c : key) {
            hashValue += c; // Simple character sum
        }
        return hashValue % MAXN;
    } else if (function == 2) {
        for (size_t i = 0; i < key.length(); i++) {
            hashValue += (i + 1) * key[i]; // Weighted character sum
        }
        return hashValue % MAXN;
    }
    return -1; // Error case
}

/* function to place a key-value pair in one of its possible positions 
    * &key: Keyword being hashed
    * &value: Value object containing the amount of ocurrences and the book title
    * tableID: Which version of the table the key is being inserted into
    * cnt: Number of displacements
    * n: Amount of elements */
void Hashmap::place(const string &key, const Value &value, int tableID, int cnt, int n) {
    if (cnt == n) {
        printf("%s unpositioned\n", key.c_str());
        printf("Cycle present. REHASH.\n");
        return;
    }

    for (int i = 0; i < ver; i++) {
        pos[i] = hashKey(i + 1, key);
        if (hashtable[i][pos[i]].key == key) {
            hashtable[i][pos[i]].value.count += value.count;  // Add occurrence count
            hashtable[i][pos[i]].value.book += ", " + value.book;  // Append book title
            return;
        }
    }

    if (hashtable[tableID][pos[tableID]].value.count != -1) {
        string displacedKey = hashtable[tableID][pos[tableID]].key;
        Value displacedValue = hashtable[tableID][pos[tableID]].value;

        hashtable[tableID][pos[tableID]].key = key;
        hashtable[tableID][pos[tableID]].value = value;

        place(displacedKey, displacedValue, (tableID + 1) % ver, cnt + 1, n);
    } else {
        hashtable[tableID][pos[tableID]].key = key;
        hashtable[tableID][pos[tableID]].value = value;
    }
}


/* Function to retrieve the value associated with a key 
    * key: Which key's value we want to retrieve */
// TODO: This should return an AVL tree in future. Then need to decide whether the values are ranked here or in a different function
Value Hashmap::getValue(const string &key) {
    for (int i = 0; i < ver; i++) {
        int index = hashKey(i + 1, key);
        if (hashtable[i][index].key == key) {
            return hashtable[i][index].value;  // Return the Value struct
        }
    }
    return Value();  // Return default Value if not found
}



/* function to print hash table contents */
// TODO: Probably remove this in final project
void Hashmap::printTable() {
    printf("Final hash tables:\n");
    for (int i = 0; i < ver; i++, printf("\n")) {
        for (int j = 0; j < MAXN; j++) {
            if (hashtable[i][j].value.count == -1)
                printf("- ");
            else
                printf("%s:%d ", hashtable[i][j].key.c_str(), hashtable[i][j].value.count);
        }
    }
    printf("\n");
}

/* entry function for cuckoo hash table 
    * &keyValuePairs: Vector of key value pairs received from text rank to take in as input*/
void Hashmap::createHashTable(const vector<pair<string, Value>> &keyValuePairs) {
    int n = keyValuePairs.size();
    MAXN = 2 * n;  // Set size of hash table to 2 times input size
    initTable();

    for (const auto &pair : keyValuePairs) {
        place(pair.first, pair.second, 0, 0, n);
    }

    printTable();
}