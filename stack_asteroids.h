#ifndef STACK_ASTEROIDS_H
#define STACK_ASTEROIDS_H

struct Asteroid {
    int size;
    char direction;
};

struct StackNode {
    Asteroid data;
    StackNode* next;
};

struct Stack {
    StackNode* top;
    
    Stack();
    void push(const Asteroid& ast);
    Asteroid pop();
    Asteroid peek() const;
    bool isEmpty() const;
    int getSize() const;
    ~Stack();
};

void interactiveAsteroids();

#endif
