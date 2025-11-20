#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include <string>

using namespace std;

struct SetNode {
    string value;
    SetNode* next;
};

struct MySet {
    SetNode* first;
    
    MySet();
    void add(const string& element);
    void remove(const string& element);
    bool contains(const string& element) const;
    void print() const;
    void clear();
    ~MySet();
};

struct GenomeSet {
    SetNode* first;
    
    GenomeSet();
    void addPair(const string& pair);
    bool containsPair(const string& pair) const;
    ~GenomeSet();
};

void interactiveSetOperations();
void interactiveGenomeCloseness();
int calculateGenomeCloseness(const string& genome1, const string& genome2);

#endif
