#ifndef BS_TREE_H
#define BS_TREE_H

#include "TreeVisualizer.h"

// Estructura para los nodos del arbol binario normal
struct BSTNode {
    int valor;
    BSTNode* izq;
    BSTNode* der;
    int profundidad;  // Guardamos la profundidad de cada nodo
    
    BSTNode(int val) : valor(val), izq(nullptr), der(nullptr), profundidad(1) {}
};

class BSTree {
private:
    BSTNode* raiz;
    TreeVisualizer visualizer;
    
    // Funcion auxiliar para insertar recursivamente
    BSTNode* insertarRec(BSTNode* nodo, int valor, int profundidad) {
        if (nodo == nullptr) {
            return new BSTNode(valor);
        }
        
        // Mostrar el estado actual antes de insertar
        int izq = nodo->izq ? nodo->izq->valor : -1;
        int der = nodo->der ? nodo->der->valor : -1;
        visualizer.mostrarNodo(nodo->valor, izq, der, profundidad, "BST: Buscando donde insertar " + std::to_string(valor));
        
        if (valor < nodo->valor) {
            nodo->izq = insertarRec(nodo->izq, valor, profundidad + 1);
        } else if (valor > nodo->valor) {
            nodo->der = insertarRec(nodo->der, valor, profundidad + 1);
        }
        
        return nodo;
    }
    
    // Funcion auxiliar para buscar recursivamente
    BSTNode* buscarRec(BSTNode* nodo, int valor, int profundidad) {
        if (nodo == nullptr || nodo->valor == valor) {
            return nodo;
        }
        
        // Mostrar el estado actual durante la busqueda
        int izq = nodo->izq ? nodo->izq->valor : -1;
        int der = nodo->der ? nodo->der->valor : -1;
        visualizer.mostrarNodo(nodo->valor, izq, der, profundidad, "BST: Buscando " + std::to_string(valor));
        
        if (valor < nodo->valor) {
            return buscarRec(nodo->izq, valor, profundidad + 1);
        }
        return buscarRec(nodo->der, valor, profundidad + 1);
    }
    
    // Funcion para calcular la profundidad maxima
    int profundidadMaxRec(BSTNode* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + std::max(profundidadMaxRec(nodo->izq), profundidadMaxRec(nodo->der));
    }

public:
    BSTree() : raiz(nullptr) {}
    
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