#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>

// Estructura del nodo para la lista enlazada
struct ListNode {
    int data;
    ListNode* next;
    ListNode(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;  // Puntero al inicio de la lista
    
    // Metodos auxiliares para visualizacion
    void sleep() const;
    void displayList() const;
    void showOperation(const std::string& operation, int value) const;

public:
    // Constructor y destructor
    LinkedList();
    ~LinkedList();

    // Operaciones basicas
    void insertAtBegin(int value);    // Insertar al inicio
    void deleteAtBegin();             // Eliminar del inicio
    void deleteByValue(int value);    // Eliminar un nodo por su valor
    bool find(int value);             // Buscar un valor
    bool isEmpty() const;
    void clear();                     // Vaciar la lista
};

#endif