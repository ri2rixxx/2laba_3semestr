#include "set_operations.h"
#include <iostream>

using namespace std;

MySet::MySet() : first(nullptr) {}

void MySet::add(const string& element) {
    if (contains(element)) {
        cout << "Элемент '" << element << "' уже существует в множестве" << endl;
        return;
    }
    
    SetNode* newNode = new SetNode{element, first};
    first = newNode;
    cout << "Элемент '" << element << "' добавлен в множество" << endl;
}

void MySet::remove(const string& element) {
    if (first == nullptr) {
        cout << "Элемент '" << element << "' не найден (множество пусто)" << endl;
        return;
    }
    
    if (first->value == element) {
        SetNode* temp = first;
        first = first->next;
        delete temp;
        cout << "Элемент '" << element << "' удален из множества" << endl;
        return;
    }
    
    SetNode* current = first;
    while (current->next != nullptr) {
        if (current->next->value == element) {
            SetNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Элемент '" << element << "' удален из множества" << endl;
            return;
        }
        current = current->next;
    }
    
    cout << "Элемент '" << element << "' не найден в множестве" << endl;
}

bool MySet::contains(const string& element) const {
    SetNode* current = first;
    while (current != nullptr) {
        if (current->value == element) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void MySet::print() const {
    SetNode* current = first;
    if (current == nullptr) {
        cout << "Множество пусто" << endl;
        return;
    }
    
    cout << "Множество: { ";
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << "}" << endl;
}

void MySet::clear() {
    SetNode* current = first;
    while (current != nullptr) {
        SetNode* next = current->next;
        delete current;
        current = next;
    }
    first = nullptr;
}

MySet::~MySet() {
    clear();
}

GenomeSet::GenomeSet() : first(nullptr) {}

void GenomeSet::addPair(const string& pair) {
    if (containsPair(pair)) return;
    
    SetNode* newNode = new SetNode{pair, first};
    first = newNode;
}

bool GenomeSet::containsPair(const string& pair) const {
    SetNode* current = first;
    while (current != nullptr) {
        if (current->value == pair) {
            return true;
        }
        current = current->next;
    }
    return false;
}

GenomeSet::~GenomeSet() {
    SetNode* current = first;
    while (current != nullptr) {
        SetNode* next = current->next;
        delete current;
        current = next;
    }
}

int calculateGenomeCloseness(const string& genome1, const string& genome2) {
    GenomeSet pairsGenome2;
    
    for (size_t i = 0; i + 1 < genome2.length(); ++i) {
        string pair = genome2.substr(i, 2);
        pairsGenome2.addPair(pair);
    }
    
    int closeness = 0;
    for (size_t i = 0; i + 1 < genome1.length(); ++i) {
        string pair = genome1.substr(i, 2);
        if (pairsGenome2.containsPair(pair)) {
            closeness++;
        }
    }
    
    return closeness;
}

void interactiveSetOperations() {
    cout << "\n=== ЗАДАНИЕ 2: АТД МНОЖЕСТВО ===" << endl;
    cout << "Команды: ADD, REMOVE, CHECK, PRINT, CLEAR, EXIT" << endl;
    
    MySet set;
    string command, element;
    
    while (true) {
        cout << "\nВведите команду: ";
        cin >> command;
        
        if (command == "ADD" || command == "add") {
            cout << "Введите элемент для добавления: ";
            cin >> element;
            set.add(element);
        }
        else if (command == "REMOVE" || command == "remove") {
            cout << "Введите элемент для удаления: ";
            cin >> element;
            set.remove(element);
        }
        else if (command == "CHECK" || command == "check") {
            cout << "Введите элемент для проверки: ";
            cin >> element;
            if (set.contains(element)) {
                cout << "Элемент '" << element << "' присутствует в множестве" << endl;
            } else {
                cout << "Элемент '" << element << "' отсутствует в множестве" << endl;
            }
        }
        else if (command == "PRINT" || command == "print") {
            set.print();
        }
        else if (command == "CLEAR" || command == "clear") {
            set.clear();
            cout << "Множество очищено" << endl;
        }
        else if (command == "EXIT" || command == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда!" << endl;
        }
    }
}

void interactiveGenomeCloseness() {
    cout << "\n=== ЗАДАНИЕ 3: ИНОПЛАНЕТНЫЙ ГЕНОМ ===" << endl;
    
    string genome1, genome2;
    cout << "Введите первый геном: ";
    cin >> genome1;
    cout << "Введите второй геном: ";
    cin >> genome2;
    
    if (genome1.length() < 2 || genome2.length() < 2) {
        cout << "Ошибка: геномы должны содержать хотя бы 2 символа!" << endl;
        return;
    }
    
    int result = calculateGenomeCloseness(genome1, genome2);
    cout << "\nГеном 1: " << genome1 << endl;
    cout << "Геном 2: " << genome2 << endl;
    cout << "Степень близости: " << result << endl;
    
    // Детализация
    cout << "\nПары первого генома, найденные во втором:" << endl;
    GenomeSet pairsGenome2;
    for (size_t i = 0; i + 1 < genome2.length(); ++i) {
        string pair = genome2.substr(i, 2);
        pairsGenome2.addPair(pair);
    }
    
    for (size_t i = 0; i + 1 < genome1.length(); ++i) {
        string pair = genome1.substr(i, 2);
        if (pairsGenome2.containsPair(pair)) {
            cout << pair << " ";
        }
    }
    cout << endl;
}
