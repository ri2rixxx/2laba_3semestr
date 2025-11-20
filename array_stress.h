#ifndef ARRAY_STRESS_H
#define ARRAY_STRESS_H

#include <string>

using namespace std;

struct DictNode {
    string word;
    DictNode* next;
};

struct Dictionary {
    DictNode* first;
    
    Dictionary();
    void addWord(const string& word);
    bool containsWord(const string& word) const;
    void print() const;
    void clear();
    ~Dictionary();
};

void interactiveStressCheck();

#endif
