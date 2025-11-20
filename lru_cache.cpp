#include "lru_cache.h"
#include <iostream>
#include <sstream>

using namespace std;

LRUNode::LRUNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}

LRUCache::LRUCache(int cap) : capacity(cap), size(0) {
    head = new LRUNode(-1, -1);
    tail = new LRUNode(-1, -1);
    head->next = tail;
    tail->prev = head;
    
    maxKey = 10000;
    keyMap = new LRUNode*[maxKey + 1];
    for (int i = 0; i <= maxKey; ++i) {
        keyMap[i] = nullptr;
    }
}

void LRUCache::removeNode(LRUNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::addToFront(LRUNode* node) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

void LRUCache::moveToFront(LRUNode* node) {
    removeNode(node);
    addToFront(node);
}

void LRUCache::removeLast() {
    if (size == 0) return;
    
    LRUNode* last = tail->prev;
    removeNode(last);
    keyMap[last->key] = nullptr;
    delete last;
    size--;
}

void LRUCache::set(int key, int value) {
    if (key < 0 || key > maxKey) return;
    
    if (keyMap[key] != nullptr) {
        LRUNode* node = keyMap[key];
        node->value = value;
        moveToFront(node);
        cout << "Обновлен ключ " << key << " -> " << value << endl;
    } else {
        if (size == capacity) {
            cout << "Удален наименее используемый элемент: " << tail->prev->key << endl;
            removeLast();
        }
        
        LRUNode* newNode = new LRUNode(key, value);
        addToFront(newNode);
        keyMap[key] = newNode;
        size++;
        cout << "Добавлен ключ " << key << " -> " << value << endl;
    }
}

int LRUCache::get(int key) {
    if (key < 0 || key > maxKey) return -1;
    
    if (keyMap[key] != nullptr) {
        LRUNode* node = keyMap[key];
        moveToFront(node);
        cout << "Получен ключ " << key << " -> " << node->value << endl;
        return node->value;
    }
    
    cout << "Ключ " << key << " не найден" << endl;
    return -1;
}

void LRUCache::printCache() const {
    cout << "Текущий кэш (емкость " << capacity << ", размер " << size << "): ";
    LRUNode* current = head->next;
    while (current != tail) {
        cout << current->key << "->" << current->value << " ";
        current = current->next;
    }
    cout << endl;
}

LRUCache::~LRUCache() {
    LRUNode* current = head;
    while (current != nullptr) {
        LRUNode* next = current->next;
        delete current;
        current = next;
    }
    delete[] keyMap;
}

void interactiveLRUCache() {
    cout << "\n=== ЗАДАНИЕ 7: LRU КЭШ ===" << endl;
    
    int capacity;
    cout << "Введите емкость кэша: ";
    cin >> capacity;
    
    if (capacity <= 0) {
        cout << "Емкость должна быть положительной!" << endl;
        return;
    }
    
    LRUCache cache(capacity);
    string command;
    int key, value;
    
    cout << "Команды: SET key value, GET key, PRINT, EXIT" << endl;
    
    while (true) {
        cout << "\nВведите команду: ";
        cin >> command;
        
        if (command == "SET" || command == "set") {
            cin >> key >> value;
            cache.set(key, value);
        }
        else if (command == "GET" || command == "get") {
            cin >> key;
            cache.get(key);
        }
        else if (command == "PRINT" || command == "print") {
            cache.printCache();
        }
        else if (command == "EXIT" || command == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда!" << endl;
        }
    }
}
