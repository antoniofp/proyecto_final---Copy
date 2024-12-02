#include "LinkedList.h"
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
LinkedList::LinkedList() : head(nullptr) {}

// Destructor
LinkedList::~LinkedList() {
    clear();
}

// Funcion de pausa para animaciones
void LinkedList::sleep() const {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// Mostrar mensaje de operacion
void LinkedList::showOperation(const std::string& operation, int value) const {
    std::cout << "\n" << GREEN << operation << ": " << RED << value << RESET << "\n";
}

// Mostrar el estado actual de la lista
void LinkedList::displayList() const {
    std::cout << "\nLista actual:\n";
    if (isEmpty()) {
        std::cout << YELLOW << "[ Lista vacia ]" << RESET << "\n";
        return;
    }

    ListNode* current = head;
    while (current != nullptr) {
        std::cout << BLUE << "[ " << current->data << " ]" << RESET;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << "\n";
}

// Insertar al inicio de la lista
void LinkedList::insertAtBegin(int value) {
    showOperation("Insertando al inicio", value);
    
    // Crear nuevo nodo
    ListNode* newNode = new ListNode(value);
    
    // Conectar el nuevo nodo al inicio actual
    newNode->next = head;
    
    // Actualizar el inicio
    head = newNode;
    
    displayList();
    sleep();
}

// Eliminar del inicio de la lista
void LinkedList::deleteAtBegin() {
    if (isEmpty()) {
        std::cout << RED << "Error: La lista esta vacia" << RESET << "\n";
        return;
    }

    showOperation("Eliminando del inicio", head->data);
    
    // Guardar el nodo a eliminar
    ListNode* temp = head;
    
    // Actualizar el inicio
    head = head->next;
    
    // Liberar memoria
    delete temp;
    
    displayList();
    sleep();
}

// Buscar un valor en la lista
bool LinkedList::find(int value) {
    if (isEmpty()) {
        std::cout << RED << "Error: La lista esta vacia" << RESET << "\n";
        return false;
    }

    std::cout << "\n" << GREEN << "Buscando " << value << " en la lista:" << RESET << "\n";
    
    ListNode* current = head;
    int position = 0;
    
    while (current != nullptr) {
        // Mostrar la lista con el elemento actual resaltado
        ListNode* temp = head;
        int pos = 0;
        while (temp != nullptr) {
            if (pos == position) {
                std::cout << RED << "[ " << temp->data << " ]" << RESET;
            } else {
                std::cout << BLUE << "[ " << temp->data << " ]" << RESET;
            }
            if (temp->next != nullptr) {
                std::cout << " -> ";
            }
            temp = temp->next;
            pos++;
        }
        std::cout << "\n";
        sleep();
        
        if (current->data == value) {
            std::cout << GREEN << "Elemento encontrado!" << RESET << "\n";
            return true;
        }
        
        current = current->next;
        position++;
    }
    
    std::cout << YELLOW << "Elemento no encontrado" << RESET << "\n";
    return false;
}

// Eliminar un nodo por su valor
void LinkedList::deleteByValue(int value) {
    if (isEmpty()) {
        std::cout << RED << "Error: La lista esta vacia" << RESET << "\n";
        return;
    }

    showOperation("Buscando para eliminar", value);
    
    // Si el elemento a eliminar está al inicio
    if (head->data == value) {
        deleteAtBegin();
        return;
    }
    
    ListNode* current = head;
    ListNode* prev = nullptr;
    int position = 0;
    bool found = false;
    
    // Buscar el elemento a eliminar
    while (current != nullptr && !found) {
        // Mostrar la búsqueda
        ListNode* temp = head;
        int pos = 0;
        while (temp != nullptr) {
            if (pos == position) {
                std::cout << YELLOW << "[ " << temp->data << " ]" << RESET;
            } else {
                std::cout << BLUE << "[ " << temp->data << " ]" << RESET;
            }
            if (temp->next != nullptr) {
                std::cout << " -> ";
            }
            temp = temp->next;
            pos++;
        }
        std::cout << "\n";
        sleep();
        
        if (current->data == value) {
            found = true;
        } else {
            prev = current;
            current = current->next;
            position++;
        }
    }
    
    if (found) {
        // Eliminar el nodo
        prev->next = current->next;
        delete current;
        std::cout << GREEN << "Elemento eliminado exitosamente" << RESET << "\n";
        displayList();
    } else {
        std::cout << RED << "Elemento no encontrado" << RESET << "\n";
    }
    
    sleep();
}

// Verificar si la lista está vacía
bool LinkedList::isEmpty() const {
    return head == nullptr;
}

// Vaciar la lista
void LinkedList::clear() {
    while (!isEmpty()) {
        deleteAtBegin();
    }
}