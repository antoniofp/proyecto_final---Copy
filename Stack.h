#ifndef STACK_H
#define STACK_H

#include <string>

// Estructura del nodo para la pila
struct StackNode {
    int data;
    StackNode* next;
    StackNode(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    StackNode* top;  // Puntero al tope de la pila
    
    // Metodos auxiliares para visualizacion
    void sleep() const;
    void displayStack() const;
    void showOperation(const std::string& operation, int value) const;

public:
    // Constructor y destructor
    Stack();
    ~Stack();

    // Operaciones basicas
    void push(int value);
    void pop();
    int peek() const;  // Ver elemento del tope sin removerlo
    bool isEmpty() const;
    void clear();  // Vaciar la pila
};

#endif