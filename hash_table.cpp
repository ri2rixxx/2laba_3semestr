#include "hash_table.h"
#include <iostream>
#include <vector>

using namespace std;

ChainNode::ChainNode(const string& k, int v) : key(k), value(v), next(nullptr) {}

HashTableChaining::HashTableChaining(int tableSize) : size(tableSize) {
    table = new ChainNode*[size];
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

int HashTableChaining::hashFunction(const string& key) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % size;
    }
    return hash;
}

void HashTableChaining::insert(const string& key, int value) {
    int index = hashFunction(key);
    cout << "  Хеш '" << key << "' = " << index << endl;
    
    ChainNode* newNode = new ChainNode(key, value);
    
    if (table[index] == nullptr) {
        table[index] = newNode;
        cout << "  → Добавлен в ячейку [" << index << "]" << endl;
    } else {
        cout << "  → КОЛЛИЗИЯ! Ячейка [" << index << "] занята" << endl;
        ChainNode* current = table[index];
        while (current->next != nullptr) {
            if (current->key == key) {
                cout << "  → Ключ уже существует, обновляем значение" << endl;
                current->value = value;
                delete newNode;
                return;
            }
            current = current->next;
        }
        if (current->key == key) {
            cout << "  → Ключ уже существует, обновляем значение" << endl;
            current->value = value;
            delete newNode;
        } else {
            current->next = newNode;
            cout << "  → Добавлен в конец цепочки ячейки [" << index << "]" << endl;
        }
    }
}

int HashTableChaining::search(const string& key) const {
    int index = hashFunction(key);
    cout << "  Поиск '" << key << "' в ячейке [" << index << "]" << endl;
    
    ChainNode* current = table[index];
    int steps = 0;
    
    while (current != nullptr) {
        steps++;
        if (current->key == key) {
            cout << "  → Найден за " << steps << " шагов: " << current->value << endl;
            return current->value;
        }
        current = current->next;
    }
    
    cout << "  → Не найден" << endl;
    return -1;
}

void HashTableChaining::remove(const string& key) {
    int index = hashFunction(key);
    cout << "  Удаление '" << key << "' из ячейки [" << index << "]" << endl;
    
    if (table[index] == nullptr) {
        cout << "  → Ключ не найден" << endl;
        return;
    }
    
    if (table[index]->key == key) {
        ChainNode* temp = table[index];
        table[index] = table[index]->next;
        delete temp;
        cout << "  → Удален из начала цепочки" << endl;
        return;
    }
    
    ChainNode* current = table[index];
    while (current->next != nullptr) {
        if (current->next->key == key) {
            ChainNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "  → Удален из цепочки" << endl;
            return;
        }
        current = current->next;
    }
    
    cout << "  → Ключ не найден" << endl;
}

void HashTableChaining::print() const {
    cout << "  МЕТОД ЦЕПОЧЕК:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "  [" << i << "]: ";
        ChainNode* current = table[i];
        if (current == nullptr) {
            cout << "пусто";
        } else {
            while (current != nullptr) {
                cout << current->key << "→" << current->value;
                if (current->next != nullptr) {
                    cout << " → ";
                }
                current = current->next;
            }
        }
        cout << endl;
    }
}

HashTableChaining::~HashTableChaining() {
    for (int i = 0; i < size; ++i) {
        ChainNode* current = table[i];
        while (current != nullptr) {
            ChainNode* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}

HashTableOpenAddressing::Entry::Entry() : key(""), value(0), occupied(false) {}

HashTableOpenAddressing::HashTableOpenAddressing(int tableSize) : size(tableSize) {
    table = new Entry[size];
}

int HashTableOpenAddressing::hashFunction(const string& key) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % size;
    }
    return hash;
}

void HashTableOpenAddressing::insert(const string& key, int value) {
    int index = hashFunction(key);
    int originalIndex = index;
    int probes = 0;
    
    cout << "  Хеш '" << key << "' = " << index << endl;
    
    do {
        probes++;
        cout << "  Проба " << probes << ": ячейка [" << index << "] - ";
        
        if (!table[index].occupied || table[index].key == key) {
            table[index].key = key;
            table[index].value = value;
            table[index].occupied = true;
            cout << "размещено" << endl;
            return;
        }
        
        cout << "занята, ищем дальше" << endl;
        index = (index + 1) % size;
    } while (index != originalIndex);
    
    cout << "  → Таблица переполнена!" << endl;
}

int HashTableOpenAddressing::search(const string& key) const {
    int index = hashFunction(key);
    int originalIndex = index;
    int probes = 0;
    
    cout << "  Поиск '" << key << "' с начальным индексом [" << index << "]" << endl;
    
    do {
        probes++;
        cout << "  Проба " << probes << ": ячейка [" << index << "] - ";
        
        if (table[index].occupied && table[index].key == key) {
            cout << "найден: " << table[index].value << endl;
            return table[index].value;
        }
        
        if (!table[index].occupied) {
            cout << "пусто, прекращаем поиск" << endl;
            break;
        }
        
        cout << "занята другим ключом" << endl;
        index = (index + 1) % size;
    } while (index != originalIndex);
    
    cout << "  → Не найден" << endl;
    return -1;
}

void HashTableOpenAddressing::remove(const string& key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int probes = 0;
    
    cout << "  Удаление '" << key << "' с начальным индексом [" << index << "]" << endl;
    
    do {
        probes++;
        cout << "  Проба " << probes << ": ячейка [" << index << "] - ";
        
        if (table[index].occupied && table[index].key == key) {
            table[index].occupied = false;
            cout << "удален" << endl;
            return;
        }
        
        if (!table[index].occupied) {
            cout << "пусто, прекращаем поиск" << endl;
            break;
        }
        
        cout << "занята другим ключом" << endl;
        index = (index + 1) % size;
    } while (index != originalIndex);
    
    cout << "  → Ключ не найден" << endl;
}

void HashTableOpenAddressing::print() const {
    cout << "  ОТКРЫТАЯ АДРЕСАЦИЯ:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "  [" << i << "]: ";
        if (table[i].occupied) {
            cout << table[i].key << "→" << table[i].value;
        } else {
            cout << "пусто";
        }
        cout << endl;
    }
}

HashTableOpenAddressing::~HashTableOpenAddressing() {
    delete[] table;
}

string findLongestUniqueSubstring(const string& s) {
    if (s.empty()) return "";
    
    cout << "\nПОИСК САМОЙ ДЛИННОЙ ПОДСТРОКИ БЕЗ ПОВТОРЕНИЙ:" << endl;
    cout << "Строка: \"" << s << "\" (длина: " << s.length() << ")" << endl;
    
    HashTableChaining lastSeen(256);
    int maxLength = 0;
    int start = 0;
    int maxStart = 0;
    
    cout << "\nПРОЦЕСС ПОИСКА:" << endl;
    
    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        int lastPos = lastSeen.search(string(1, c));
        
        cout << "Позиция " << i << ": символ '" << c << "'";
        
        if (lastPos != -1 && lastPos >= start) {
            cout << " → повтор! Начинаем новую подстроку с позиции " << lastPos + 1 << endl;
            start = lastPos + 1;
        } else {
            cout << " → уникален, продолжаем текущую подстроку" << endl;
        }
        
        lastSeen.insert(string(1, c), i);
        
        int currentLength = i - start + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
            maxStart = start;
            cout << "  → НОВАЯ МАКСИМАЛЬНАЯ ПОДСТРОКА: \"" 
                 << s.substr(maxStart, maxLength) << "\" (длина: " << maxLength << ")" << endl;
        }
    }
    
    string result = s.substr(maxStart, maxLength);
    
    cout << "\nРЕЗУЛЬТАТ:" << endl;
    cout << "Самая длинная подстрока: \"" << result << "\"" << endl;
    cout << "Начальная позиция: " << maxStart << endl;
    cout << "Длина: " << maxLength << endl;
    
    return result;
}

void interactiveHashTables() {
    cout << "\n=== ЗАДАНИЕ 6: ХЕШ-ТАБЛИЦЫ ===" << endl;
    cout << "1. Работа с хеш-таблицами" << endl;
    cout << "2. Найти самую длинную подстроку без повторений" << endl;
    cout << "Выберите режим: ";
    
    int mode;
    cin >> mode;
    cin.ignore();
    
    if (mode == 1) {
        cout << "Размер хеш-таблицы: ";
        int size;
        cin >> size;
        cin.ignore();
        
        HashTableChaining chainTable(size);
        HashTableOpenAddressing openTable(size);
        
        cout << "\nКоманды: INSERT key value, SEARCH key, REMOVE key, PRINT, EXIT" << endl;
        
        string command;
        while (true) {
            cout << "\nВведите команду: ";
            getline(cin, command);
            
            if (command == "EXIT" || command == "exit") {
                break;
            }
            else if (command.find("INSERT") == 0) {
                string key, valueStr;
                size_t pos = command.find(' ');
                if (pos != string::npos) {
                    size_t pos2 = command.find(' ', pos + 1);
                    if (pos2 != string::npos) {
                        key = command.substr(pos + 1, pos2 - pos - 1);
                        valueStr = command.substr(pos2 + 1);
                        int value = stoi(valueStr);
                        
                        cout << "\n--- МЕТОД ЦЕПОЧЕК ---" << endl;
                        chainTable.insert(key, value);
                        cout << "\n--- ОТКРЫТАЯ АДРЕСАЦИЯ ---" << endl;
                        openTable.insert(key, value);
                    }
                }
            }
            else if (command.find("SEARCH") == 0) {
                string key = command.substr(7);
                if (!key.empty()) {
                    cout << "\n--- МЕТОД ЦЕПОЧЕК ---" << endl;
                    int result1 = chainTable.search(key);
                    cout << "\n--- ОТКРЫТАЯ АДРЕСАЦИЯ ---" << endl;
                    int result2 = openTable.search(key);
                    
                    cout << "\nИТОГ ПОИСКА:" << endl;
                    cout << "Метод цепочек: " << (result1 != -1 ? to_string(result1) : "не найден") << endl;
                    cout << "Открытая адресация: " << (result2 != -1 ? to_string(result2) : "не найден") << endl;
                }
            }
            else if (command.find("REMOVE") == 0) {
                string key = command.substr(7);
                if (!key.empty()) {
                    cout << "\n--- МЕТОД ЦЕПОЧЕК ---" << endl;
                    chainTable.remove(key);
                    cout << "\n--- ОТКРЫТАЯ АДРЕСАЦИЯ ---" << endl;
                    openTable.remove(key);
                }
            }
            else if (command == "PRINT" || command == "print") {
                cout << "\n--- МЕТОД ЦЕПОЧЕК ---" << endl;
                chainTable.print();
                cout << "\n--- ОТКРЫТАЯ АДРЕСАЦИЯ ---" << endl;
                openTable.print();
            }
            else {
                cout << "Неизвестная команда!" << endl;
            }
        }
    }
    else if (mode == 2) {
        cout << "Введите строку: ";
        string s;
        getline(cin, s);
        
        findLongestUniqueSubstring(s);
    }
}
