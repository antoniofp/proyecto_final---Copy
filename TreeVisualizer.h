#ifndef TREE_VISUALIZER_H
#define TREE_VISUALIZER_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "Colors.h"

class TreeVisualizer {
private:
    // Funcion para hacer una pausa entre visualizaciones
    void sleep() const {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

public:

    // Muestra el nodo actual y sus hijos
    // valor - valor del nodo actual
    // izq - valor del hijo izquierdo (o -1 si no existe)
    // der - valor del hijo derecho (o -1 si no existe)
    // profundidad - nivel actual en el arbol
    void mostrarNodo(int valor, int izq, int der, int profundidad, const std::string& mensaje = "") const {
        std::cout << mensaje << "\n";
        std::cout << YELLOW << "Profundidad actual: " << profundidad << RESET << "\n\n";
        
        // Muestra el nodo padre
        std::cout << "      " << RED << "[" << valor << "]" << RESET << "\n";
        std::cout << "      /  \\" << "\n";
        
        // Muestra los hijos (si existen)
        std::cout << "    ";
        if (izq != -1) {
            std::cout << GREEN << "[" << izq << "]" << RESET;
        } else {
            std::cout << "   ";
        }
        std::cout << "  ";
        if (der != -1) {
            std::cout << GREEN << "[" << der << "]" << RESET;
        } else {
            std::cout << "   ";
        }
        std::cout << "\n\n";
        
        sleep();
    }
};

#endif