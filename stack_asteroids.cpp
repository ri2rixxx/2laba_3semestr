#include "stack_asteroids.h"
#include <iostream>
#include <vector>

using namespace std;

Stack::Stack() : top(nullptr) {}

void Stack::push(const Asteroid& ast) {
    StackNode* newNode = new StackNode{ast, top};
    top = newNode;
}

Asteroid Stack::pop() {
    if (isEmpty()) {
        return Asteroid{0, ' '};
    }
    StackNode* temp = top;
    Asteroid data = temp->data;
    top = top->next;
    delete temp;
    return data;
}

Asteroid Stack::peek() const {
    if (isEmpty()) {
        return Asteroid{0, ' '};
    }
    return top->data;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

int Stack::getSize() const {
    int count = 0;
    StackNode* current = top;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

vector<Asteroid> processAsteroids(const vector<Asteroid>& asteroids) {
    Stack st;
    
    cout << "\nПРОЦЕСС СТОЛКНОВЕНИЙ:" << endl;
    
    for (const auto& ast : asteroids) {
        cout << "Обрабатываем астероид: {" << ast.size << ", '" << ast.direction << "'}" << endl;
        
        if (st.isEmpty()) {
            st.push(ast);
            cout << "  → Добавлен в стек (стек был пуст)" << endl;
            continue;
        }
        
        bool shouldAdd = true;
        
        while (!st.isEmpty()) {
            Asteroid topAst = st.peek();
            cout << "  Сравниваем с верхним астероидом стека: {" << topAst.size << ", '" << topAst.direction << "'}" << endl;
            
            // Столкновение происходит только при встречном движении
            if (topAst.direction == 'R' && ast.direction == 'L') {
                cout << "  → СТОЛКНОВЕНИЕ! (" << topAst.size << " vs " << ast.size << ")" << endl;
                
                if (topAst.size > ast.size) {
                    // Верхний астероид больше - текущий уничтожается
                    cout << "  → Астероид {" << ast.size << ", '" << ast.direction << "'} уничтожен!" << endl;
                    shouldAdd = false;
                    break;
                } else if (topAst.size < ast.size) {
                    // Текущий астероид больше - верхний уничтожается
                    cout << "  → Астероид {" << topAst.size << ", '" << topAst.direction << "'} уничтожен!" << endl;
                    st.pop();
                    // Продолжаем проверять следующий астероид в стеке
                } else {
                    // Одинаковый размер - оба уничтожаются
                    cout << "  → ОБА астероида уничтожены!" << endl;
                    st.pop();
                    shouldAdd = false;
                    break;
                }
            } else {
                // Нет столкновения - одинаковые направления или L-R
                cout << "  → Нет столкновения (направления " << topAst.direction << " и " << ast.direction << ")" << endl;
                break;
            }
        }
        
        if (shouldAdd) {
            st.push(ast);
            cout << "  → Астероид добавлен в стек" << endl;
        }
        
        // Покажем текущее состояние стека
        cout << "  Текущий стек: ";
        Stack temp;
        vector<Asteroid> currentState;
        while (!st.isEmpty()) {
            Asteroid a = st.pop();
            currentState.insert(currentState.begin(), a);
            temp.push(a);
        }
        while (!temp.isEmpty()) {
            st.push(temp.pop());
        }
        for (const auto& a : currentState) {
            cout << "{" << a.size << ",'" << a.direction << "'} ";
        }
        cout << endl;
    }
    
    // Собираем результат из стека
    vector<Asteroid> result;
    Stack temp;
    while (!st.isEmpty()) {
        temp.push(st.pop());
    }
    while (!temp.isEmpty()) {
        result.push_back(temp.pop());
    }
    
    return result;
}

void printAsteroids(const vector<Asteroid>& asteroids) {
    if (asteroids.empty()) {
        cout << "Все астероиды уничтожены!" << endl;
        return;
    }
    
    cout << "ОСТАВШИЕСЯ АСТЕРОИДЫ: ";
    for (const auto& ast : asteroids) {
        cout << "{" << ast.size << ", '" << ast.direction << "'} ";
    }
    cout << endl;
}

void interactiveAsteroids() {
    cout << "\n=== ЗАДАНИЕ 1: ОБРАБОТКА АСТЕРОИДОВ ===" << endl;
    cout << "Введите астероиды в формате: размер направление" << endl;
    cout << "Направление: R (вправо) или L (влево)" << endl;
    cout << "Для завершения ввода введите: 0 X" << endl;
    
    vector<Asteroid> asteroids;
    int size;
    char direction;
    
    while (true) {
        cout << "Астероид " << asteroids.size() + 1 << ": ";
        cin >> size;
        if (size == 0) break;
        cin >> direction;
        
        if (direction != 'R' && direction != 'L' && direction != 'r' && direction != 'l') {
            cout << "Ошибка: направление должно быть R или L!" << endl;
            continue;
        }
        
        direction = toupper(direction);
        asteroids.push_back({size, direction});
    }
    
    if (asteroids.empty()) {
        cout << "Не введено ни одного астероида!" << endl;
        return;
    }
    
    cout << "\nИСХОДНЫЕ АСТЕРОИДЫ: ";
    printAsteroids(asteroids);
    
    vector<Asteroid> result = processAsteroids(asteroids);
    
    cout << "ФИНАЛЬНЫЙ РЕЗУЛЬТАТ:" << endl;
    printAsteroids(result);
}
