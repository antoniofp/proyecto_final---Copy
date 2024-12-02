#ifndef QUEUE_H
#define QUEUE_H

#include <string>

// Estructura del nodo para la cola
struct QueueNode {
    int data;
    QueueNode* next;
    QueueNode(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    QueueNode* front;  // Puntero al frente de la cola
    QueueNode* rear;   // Puntero al final de la cola
    
    // Metodos auxiliares para visualizacion
    void sleep() const;
    void displayQueue() const;
    void showOperation(const std::string& operation, int value) const;

public:
    // Constructor y destructor
    Queue();
    ~Queue();

    // Operaciones basicas
    void enqueue(int value);   // Insertar al final
    void dequeue();            // Eliminar del frente
    int getFront() const;      // Ver elemento del frente sin removerlo
    bool isEmpty() const;
    void clear();             // Vaciar la cola
};

#endif