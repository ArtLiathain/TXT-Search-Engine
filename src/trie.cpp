#include "../include/trie.h"

using namespace std;

trie::trie()
{
    stringhashmap<Node *> children = stringhashmap<Node *>();
    // Root can't have value so its always ""
    root = new Node{"", false, children};
}

trie::trie(const trie &other){
    root = other.root;
}

trie::trie(trie &&other) noexcept{
    root = other.root;
    other.root = nullptr;
}

trie& trie::operator=(const trie &other){
    if (this == &other) {
        return *this;  // Handle self-assignment
    }

    root = other.root;
    
    return *this;
}

trie& trie::operator=(trie &&other) noexcept{
    if (this == &other) {
        return *this;  // Handle self-assignment
    }

    root = other.root;

    other.root = nullptr;
    
    return *this;
}

trie::~trie()
{}

void trie::insert(string word)
{
    try{
        Node *cur = root;
        // Only lowercase words
        for (int j = 0; j < word.length(); j++){
            word[j] = tolower(word[j]);
        }
        for (int i = 0; i < word.length(); i++)
        {
            // Get the current substring of length depth
            string frag = word.substr(0, i + 1);
            Node *node;
            // If node doesn't exist create a new one otherwise go to the matching child node
            if (cur->children.keyExists(frag) == false)
            {
                stringhashmap<Node *> children = stringhashmap<Node *>();
                node = new Node{frag, false, children};
                cur->children.insert(frag, node);
            }
            else
            {
                node = cur->children.getValue(frag);
            }
            cur = node;
        }
        // Know if this is an inputted word
        cur->endOfWord = true;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Key not found: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

arraylist<string> trie::getArrayList()
{
    try{
        arraylist<string> result = arraylist<string>(10);
        Node *cur = root;
        // Loop through and convert words to arraylist order is not deterministic
        arraylist<string> keys = cur->children.getAllKeys();
        for (int i = 0; i < keys.length; i++)
        {
            // Recursive search call
            Node* childNode = cur->children.getValue(keys.get(i));
            getArrayList_rec(childNode->children, "", &result);
        }
        return result;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Key not found: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Find words based of prefix order is deterministic 
arraylist<string> trie::getArrayList_withPrefix(string prefix)
{
    try{
        for (int j = 0; j < prefix.length(); j++){
            prefix[j] = tolower(prefix[j]);
        }
        arraylist<string> result = arraylist<string>(10);
        Node *cur = root;
        arraylist<string> keys = cur->children.getAllKeys();
        for (int i = 0; i < keys.length; i++)
        {
            // Recursive search call
            Node* childNode = cur->children.getValue(keys.get(i));
            getArrayList_rec(childNode->children, prefix, &result);
        }
        return result;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Key not found: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void trie::getArrayList_rec(stringhashmap<trie::Node *> children, string prefix, arraylist<string> * result)
{
    try{
        arraylist<string> keys = children.getAllKeys();
        // Loop through each child to check if prefix matches
        for (int i = 0; i < keys.length; i++)
        {
            Node* childNode = children.getValue(keys.get(i));

            // Only insert if it's a full word and matches the prefix
            if (childNode->endOfWord && childNode->key.substr(0, prefix.length()) == prefix) {
                result->insert(childNode->key);
            }

            // Continue the recursion if the key matches the prefix
            if (childNode->key.substr(0, prefix.length()) == prefix || 
                prefix.substr(0, childNode->key.length()) == childNode->key) {
                getArrayList_rec(childNode->children, prefix, result);
            }
        }
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Key not found: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void trie::serialize(const string &filename) {
    cout << "serializing " << filename << endl;
    ofstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Could not open file for writing");
    }

    // Start serializing from the root node
    serializeNode(file, root);

    file.close();
}

void trie::serializeNode(ofstream &file, Node *node){
    if (node == nullptr) return;

    size_t key_size = node->key.size();
    file.write(reinterpret_cast<const char *>(&key_size), sizeof(key_size));
    file.write(node->key.data(), key_size);

    file.write(reinterpret_cast<const char *>(&node->endOfWord), sizeof(bool));

    arraylist<string> childrenKeys = node->children.getAllKeys();
    size_t num_children = childrenKeys.length;
    file.write(reinterpret_cast<const char*>(&num_children), sizeof(num_children));

    for(int i = 0; i < num_children; i++){
        string childKey = childrenKeys.get(i);
        Node* childNode = node->children.getValue(childKey);
        serializeNode(file, childNode);
    }
}

trie trie::deserialize(const string &filename){
    cout << "deserializing " << filename << endl;

    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Failed to open file for reading.");
    }

    trie deserializedTrie;

    deserializedTrie.root = deserializeNode(file);

    file.close();

    return deserializedTrie;
}

trie::Node* trie::deserializeNode(ifstream &file){
    size_t key_size;
    file.read(reinterpret_cast<char*>(&key_size), sizeof(key_size));

    // Size the key string to the read size and initialise to all spaces
    string key(key_size, ' ');
    // Read the key from the file
    file.read(key.data(), key_size);

    bool endOfWord;
    file.read(reinterpret_cast<char*>(&endOfWord), sizeof(bool));

    // Deserialize the number of children
    size_t num_children;
    file.read(reinterpret_cast<char*>(&num_children), sizeof(num_children));

    // Create the node and deserialize its children
    stringhashmap<Node *> children = stringhashmap<Node *>();
    Node *node = new Node{key, endOfWord, children};

    // Recursively deserialize each child node
    for (size_t i = 0; i < num_children; ++i) {
        Node *child_node = deserializeNode(file);
        node->children.insert(child_node->key, child_node);
    }
    return node;
}