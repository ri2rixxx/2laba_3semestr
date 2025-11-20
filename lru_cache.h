#ifndef LRU_CACHE_H
#define LRU_CACHE_H

struct LRUNode {
    int key;
    int value;
    LRUNode* prev;
    LRUNode* next;
    
    LRUNode(int k, int v);
};

struct LRUCache {
    LRUNode* head;
    LRUNode* tail;
    int capacity;
    int size;
    LRUNode** keyMap;
    int maxKey;
    
    LRUCache(int cap);
    void set(int key, int value);
    int get(int key);
    void printCache() const;
    ~LRUCache();
    
private:
    void removeNode(LRUNode* node);
    void addToFront(LRUNode* node);
    void moveToFront(LRUNode* node);
    void removeLast();
};

void interactiveLRUCache();

#endif
