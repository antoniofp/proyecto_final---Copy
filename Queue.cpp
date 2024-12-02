#include "Queue.h"
#include <iostream>
#include <thread>
#include <chrono>

// Colores para la visualizacion
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";     // Elemento actual/nuevo
const std::string GREEN = "\033[32m";    // Operacion exitosa
const std::string YELLOW = "\033[33m";   // Elemento a eliminar
const std::string BLUE = "\033[34m";     // Elementos en la estructura

// Constructor
Queue::Queue() : front(nullptr), rear(nullptr) {}

// Destructor
Queue::~Queue() {
    clear();
}

// Funcion de pausa para animaciones
void Queue::sleep() const {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// Mostrar mensaje de operacion
void Queue::showOperation(const std::string& operation, int value) const {
    std::cout << "\n" << GREEN << operation << ": " << RED << value << RESET << "\n";
}

// Mostrar el estado actual de la cola
void Queue::displayQueue() const {
    std::cout << "\nCola actual:\n";
    if (isEmpty()) {
        std::cout << YELLOW << "[ Cola vacia ]" << RESET << "\n";
        return;
    }

    // Mostrar todos los elementos con flechas
    QueueNode* current = front;
    std::cout << "FRENTE ";
    while (current != nullptr) {
        if (current == front) {
            std::cout << GREEN << "[ " << current->data << " ]" << RESET;
        } else if (current == rear) {
            std::cout << RED << "[ " << current->data << " ]" << RESET;
        } else {
            std::cout << BLUE << "[ " << current->data << " ]" << RESET;
        }
        
        if (current->next != nullptr) {
            std::cout << " <- ";
        }
        current = current->next;
    }
    std::cout << " FINAL\n";
}

// Insertar elemento al final de la cola
void Queue::enqueue(int value) {
    showOperation("ENQUEUE en la cola", value);
    
    // Crear nuevo nodo
    QueueNode* newNode = new QueueNode(value);
    
    // Si la cola esta vacia, el nuevo nodo es tanto el frente como el final
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        // Agregar el nuevo nodo al final
        rear->next = newNode;
        rear = newNode;
    }
    
    displayQueue();
    sleep();
}

// Eliminar elemento del frente de la cola
void Queue::dequeue() {
    if (isEmpty()) {
        std::cout << RED << "Error: La cola esta vacia" << RESET << "\n";
        return;
    }

    showOperation("DEQUEUE de la cola", front->data);
    
    // Guardar el nodo a eliminar
    QueueNode* temp = front;
    
    // Actualizar el frente
    front = front->next;
    
    // Si la cola queda vacia, actualizar también el final
    if (front == nullptr) {
        rear = nullptr;
    }
    
    // Liberar memoria
    delete temp;
    displayQueue();
    sleep();
}

// Ver elemento del frente sin removerlo
int Queue::getFront() const {
    if (isEmpty()) {
        std::cout << RED << "Error: La cola esta vacia" << RESET << "\n";
        return -1;  // Valio cake
    }
    return front->data;
}

// Verificar si la cola está vacía
bool Queue::isEmpty() const {
    return front == nullptr;
}

// Vaciar la cola
void Queue::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}