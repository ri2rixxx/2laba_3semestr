#include "array_stress.h"
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

Dictionary::Dictionary() : first(nullptr) {}

void Dictionary::addWord(const string& word) {
    DictNode* newNode = new DictNode{word, first};
    first = newNode;
}

bool Dictionary::containsWord(const string& word) const {
    DictNode* current = first;
    while (current != nullptr) {
        if (current->word == word) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void Dictionary::print() const {
    DictNode* current = first;
    if (current == nullptr) {
        cout << "Словарь пуст" << endl;
        return;
    }
    
    cout << "Словарь: ";
    while (current != nullptr) {
        cout << current->word << " ";
        current = current->next;
    }
    cout << endl;
}

void Dictionary::clear() {
    DictNode* current = first;
    while (current != nullptr) {
        DictNode* next = current->next;
        delete current;
        current = next;
    }
    first = nullptr;
}

Dictionary::~Dictionary() {
    clear();
}

int countStresses(const string& word) {
    int count = 0;
    for (char c : word) {
        if (isupper(c)) {
            count++;
        }
    }
    return count;
}

bool isWordCorrect(const Dictionary& dict, const string& word) {
    if (dict.containsWord(word)) {
        return true;
    }
    
    int stressCount = countStresses(word);
    return stressCount == 1;
}

void checkText(const Dictionary& dict, const string& text) {
    cout << "\nПроверка текста: \"" << text << "\"" << endl;
    
    stringstream ss(text);
    string word;
    int errorCount = 0;
    
    while (ss >> word) {
        bool correct = isWordCorrect(dict, word);
        cout << "Слово '" << word << "': " << (correct ? "ПРАВИЛЬНО" : "ОШИБКА");
        if (!correct) {
            errorCount++;
            int stresses = countStresses(word);
            if (stresses == 0) {
                cout << " (нет ударения)";
            } else if (stresses > 1) {
                cout << " (" << stresses << " ударения)";
            } else if (!dict.containsWord(word)) {
                cout << " (слово отсутствует в словаре)";
            }
        }
        cout << endl;
    }
    
    cout << "\nВсего ошибок: " << errorCount << endl;
}

void interactiveStressCheck() {
    cout << "\n=== ЗАДАНИЕ 4: КОНТРОЛЬНАЯ ПО УДАРЕНИЯМ ===" << endl;
    
    Dictionary dict;
    string command, word, text;
    
    cout << "Сначала заполните словарь правильных слов." << endl;
    cout << "Команды: ADD, PRINT, CLEAR, CHECK, EXIT" << endl;
    
    while (true) {
        cout << "\nВведите команду: ";
        cin >> command;
        
        if (command == "ADD" || command == "add") {
            cout << "Введите слово для добавления в словарь: ";
            cin >> word;
            dict.addWord(word);
        }
        else if (command == "PRINT" || command == "print") {
            dict.print();
        }
        else if (command == "CLEAR" || command == "clear") {
            dict.clear();
            cout << "Словарь очищен" << endl;
        }
        else if (command == "CHECK" || command == "check") {
            cout << "Введите текст для проверки: ";
            cin.ignore();
            getline(cin, text);
            checkText(dict, text);
        }
        else if (command == "EXIT" || command == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда!" << endl;
        }
    }
}
