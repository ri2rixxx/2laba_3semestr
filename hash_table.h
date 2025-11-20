#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>

using namespace std;

struct ChainNode {
    string key;
    int value;
    ChainNode* next;
    
    ChainNode(const string& k, int v);
};

struct HashTableChaining {
    ChainNode** table;
    int size;
    
    HashTableChaining(int tableSize);
    int hashFunction(const string& key) const;
    void insert(const string& key, int value);
    int search(const string& key) const;
    void remove(const string& key);
    void print() const;
    ~HashTableChaining();
};

struct HashTableOpenAddressing {
    struct Entry {
        string key;
        int value;
        bool occupied;
        
        Entry();
    };
    
    Entry* table;
    int size;
    
    HashTableOpenAddressing(int tableSize);
    int hashFunction(const string& key) const;
    void insert(const string& key, int value);
    int search(const string& key) const;
    void remove(const string& key);
    void print() const;
    ~HashTableOpenAddressing();
};

void interactiveHashTables();
string findLongestUniqueSubstring(const string& s);

#endif
