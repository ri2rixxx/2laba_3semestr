#include <iostream>
#include "stack_asteroids.h"
#include "set_operations.h"
#include "array_stress.h"
#include "tree_traversal.h"
#include "hash_table.h"
#include "lru_cache.h"

using namespace std;

void showMainMenu() {
    cout << "1. Задание 1: Стек - Обработка астероидов" << endl;
    cout << "2. Задание 2: АТД Множество - Базовые операции" << endl;
    cout << "3. Задание 3: Множество - Инопланетный геном" << endl;
    cout << "4. Задание 4: Массив - Контрольная по ударениям" << endl;
    cout << "5. Задание 5: Двоичное дерево - Центрированный обход" << endl;
    cout << "6. Задание 6: Хеш-таблицы" << endl;
    cout << "7. Задание 7: LRU кэш" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите задание: ";
}

int main() {
    int choice;
    
    do {
        showMainMenu();
        cin >> choice;
        cin.ignore(); // Очистка буфера
        
        switch(choice) {
            case 1:
                interactiveAsteroids();
                break;
            case 2:
                interactiveSetOperations();
                break;
            case 3:
                interactiveGenomeCloseness();
                break;
            case 4:
                interactiveStressCheck();
                break;
            case 5:
                interactiveTreeTraversal();
                break;
            case 6:
                interactiveHashTables();
                break;
            case 7:
                interactiveLRUCache();
                break;
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);
    
    return 0;
}
