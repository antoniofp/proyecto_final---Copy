#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "TreeVisualizer.h"

// Estructura para los nodos del arbol AVL
struct AVLNode {
    int valor;
    AVLNode* izq;
    AVLNode* der;
    int altura;
    int profundidad;
    
    AVLNode(int val) : valor(val), izq(nullptr), der(nullptr), altura(1), profundidad(1) {}
};

class AVLTree {
private:
    AVLNode* raiz;
    TreeVisualizer visualizer;
    
    int altura(AVLNode* nodo) {
        return nodo ? nodo->altura : 0;
    }
    
    int obtenerBalance(AVLNode* nodo) {
        return nodo ? altura(nodo->izq) - altura(nodo->der) : 0;
    }
    
    AVLNode* rotacionDerecha(AVLNode* y) {
        AVLNode* x = y->izq;
        AVLNode* T2 = x->der;
        
        // Mostrar la rotación
        std::cout << BLUE << "\nRealizando rotacion derecha:" << RESET << "\n";
        std::cout << "Nodo pivote: " << RED << y->valor << RESET << "\n";
        std::cout << "Nuevo padre: " << GREEN << x->valor << RESET << "\n";
        
        // Realizar la rotación
        x->der = y;
        y->izq = T2;
        
        // Actualizar alturas
        y->altura = std::max(altura(y->izq), altura(y->der)) + 1;
        x->altura = std::max(altura(x->izq), altura(x->der)) + 1;
        
        // Mostrar resultado
        visualizer.mostrarNodo(x->valor, 
                             x->izq ? x->izq->valor : -1,
                             x->der ? x->der->valor : -1,
                             1,
                             "Estado despues de rotacion derecha");
        
        return x;
    }

    AVLNode* rotacionIzquierda(AVLNode* x) {
        AVLNode* y = x->der;
        AVLNode* T2 = y->izq;
        
        // Mostrar la rotación
        std::cout << BLUE << "\nRealizando rotacion izquierda:" << RESET << "\n";
        std::cout << "Nodo pivote: " << RED << x->valor << RESET << "\n";
        std::cout << "Nuevo padre: " << GREEN << y->valor << RESET << "\n";
        
        // Realizar la rotación
        y->izq = x;
        x->der = T2;
        
        // Actualizar alturas
        x->altura = std::max(altura(x->izq), altura(x->der)) + 1;
        y->altura = std::max(altura(y->izq), altura(y->der)) + 1;
        
        // Mostrar resultado
        visualizer.mostrarNodo(y->valor, 
                             y->izq ? y->izq->valor : -1,
                             y->der ? y->der->valor : -1,
                             1,
                             "Estado despues de rotacion izquierda");
        
        return y;
    }

    AVLNode* insertarRec(AVLNode* nodo, int valor, int profundidad) {
        // Si el nodo es nulo, crear un nuevo nodo
        if (nodo == nullptr) {
            return new AVLNode(valor);
        }
        
        // Mostrar estado actual antes de insertar
        int izq = nodo->izq ? nodo->izq->valor : -1;
        int der = nodo->der ? nodo->der->valor : -1;
        visualizer.mostrarNodo(nodo->valor, izq, der, profundidad, 
                            "AVL: Buscando donde insertar " + std::to_string(valor));
        
        // Insertar de forma recursiva
        if (valor < nodo->valor) {
            nodo->izq = insertarRec(nodo->izq, valor, profundidad + 1);
        } else if (valor > nodo->valor) {
            nodo->der = insertarRec(nodo->der, valor, profundidad + 1);
        } else {
            return nodo; // Valor duplicado
        }
        
        // Actualizar la altura del nodo actual
        nodo->altura = 1 + std::max(altura(nodo->izq), altura(nodo->der));
        
        // Obtener el factor de balance
        int balance = obtenerBalance(nodo);

        // Casos de rotación (el resto del código que ya tienes)
        if (balance > 1 && valor < nodo->izq->valor) {
            std::cout << YELLOW << "\nDetectado caso Izquierda-Izquierda" << RESET << "\n";
            return rotacionDerecha(nodo);
        }

        if (balance < -1 && valor > nodo->der->valor) {
            std::cout << YELLOW << "\nDetectado caso Derecha-Derecha" << RESET << "\n";
            return rotacionIzquierda(nodo);
        }

        if (balance > 1 && valor > nodo->izq->valor) {
            std::cout << YELLOW << "\nDetectado caso Izquierda-Derecha" << RESET << "\n";
            std::cout << "Realizando rotacion doble...\n";
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }

        if (balance < -1 && valor < nodo->der->valor) {
            std::cout << YELLOW << "\nDetectado caso Derecha-Izquierda" << RESET << "\n";
            std::cout << "Realizando rotacion doble...\n";
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }
        
    AVLNode* buscarRec(AVLNode* nodo, int valor, int profundidad) {
        if (nodo == nullptr || nodo->valor == valor) {
            return nodo;
        }
        
        // Mostrar estado actual durante la busqueda
        int izq = nodo->izq ? nodo->izq->valor : -1;
        int der = nodo->der ? nodo->der->valor : -1;
        visualizer.mostrarNodo(nodo->valor, izq, der, profundidad, "AVL: Buscando " + std::to_string(valor));
        
        if (valor < nodo->valor) {
            return buscarRec(nodo->izq, valor, profundidad + 1);
        }
        return buscarRec(nodo->der, valor, profundidad + 1);
    }
    
    int profundidadMaxRec(AVLNode* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + std::max(profundidadMaxRec(nodo->izq), profundidadMaxRec(nodo->der));
    }

public:
    AVLTree() : raiz(nullptr) {}
    
    void insertar(int valor) {
        raiz = insertarRec(raiz, valor, 1);
    }
    
    bool buscar(int valor) {
        return buscarRec(raiz, valor, 1) != nullptr;
    }
    
    int obtenerProfundidadMax() {
        return profundidadMaxRec(raiz);
    }
};

#endif