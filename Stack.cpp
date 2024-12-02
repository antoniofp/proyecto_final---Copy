#include "Stack.h"
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
Stack::Stack() : top(nullptr) {}

// Destructor
Stack::~Stack() {
    clear();
}

// Funcion de pausa para animaciones
void Stack::sleep() const {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// Mostrar mensaje de operacion
void Stack::showOperation(const std::string& operation, int value) const {
    std::cout << "\n" << GREEN << operation << ": " << RED << value << RESET << "\n";
}

// Mostrar el estado actual de la pila
void Stack::displayStack() const {
    std::cout << "\nPila actual:\n";
    if (isEmpty()) {
        std::cout << YELLOW << "[ Pila vacia ]" << RESET << "\n";
        return;
    }

    // Mostrar elementos de arriba hacia abajo
    StackNode* current = top;
    while (current != nullptr) {
        std::cout << BLUE << "+---+" << RESET << "\n";
        std::cout << BLUE << "| " << current->data << " |" << RESET << "\n";
        std::cout << BLUE << "+---+" << RESET << "\n";
        current = current->next;
    }
}

// Insertar elemento en la pila
void Stack::push(int value) {
    showOperation("PUSH en la pila", value);
    
    // Crear nuevo nodo
    StackNode* newNode = new StackNode(value);
    
    // Conectar el nuevo nodo al tope actual
    newNode->next = top;
    
    // Actualizar el tope
    top = newNode;
    
    displayStack();
    sleep();
}

// Eliminar elemento del tope
void Stack::pop() {
    if (isEmpty()) {
        std::cout << RED << "Error: La pila esta vacia" << RESET << "\n";
        return;
    }

    showOperation("POP de la pila", top->data);
    
    // Guardar el nodo a eliminar
    StackNode* temp = top;
    
    // Actualizar el tope
    top = top->next;
    
    // Liberar memoria
    delete temp;
    
    displayStack();
    sleep();
}

// Ver elemento del tope sin removerlo
int Stack::peek() const {
    if (isEmpty()) {
        std::cout << RED << "Error: La pila esta vacia" << RESET << "\n";
        return -1;  // Valor de error
    }
    return top->data;
}

// Verificar si la pila está vacía
bool Stack::isEmpty() const {
    return top == nullptr;
}

// Vaciar la pila
void Stack::clear() {
    while (!isEmpty()) {
        pop();
    }
}