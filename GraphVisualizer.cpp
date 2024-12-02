#include "GraphVisualizer.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <stack>
#include <queue>
#include <random>

GraphVisualizer::GraphVisualizer(int n, float densidad) : numNodos(n) {
    // Inicializar matriz de adyacencia con ceros
    matriz = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    generarConexionesAleatorias(densidad);
}

void GraphVisualizer::generarConexionesAleatorias(float densidad) {
    // Inicializamos el generador de numeros aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Distribucion uniforme entre 0.0 y 1.0 para decidir conexiones
    std::uniform_real_distribution<> probabilidad(0.0, 1.0);
    
    // Distribucion uniforme para pesos (1-9)
    std::uniform_int_distribution<> peso(1, 9);

    for (int i = 0; i < numNodos; i++) {
        for (int j = i + 1; j < numNodos; j++) {
            if (probabilidad(gen) < densidad) {
                int p = peso(gen);
                matriz[i][j] = p;
                matriz[j][i] = p;  // Grafo no dirigido
            }
        }
    }
}

void GraphVisualizer::pausa(int milliseconds) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void GraphVisualizer::mostrarMatriz(const std::vector<bool>& visitado) const {
    // Limpiamos la pantalla
    std::cout << "\033[2J\033[1;1H";
    
    // Mostrar encabezado de columnas
    std::cout << "\n    ";
    for (int i = 0; i < numNodos; i++) {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << "\n   ";
    
    // Linea superior
    for (int i = 0; i < numNodos; i++) {
        std::cout << "----";
    }
    std::cout << "-\n";

    // Mostrar matriz
    for (int i = 0; i < numNodos; i++) {
        std::cout << std::setw(2) << i << " |";
        for (int j = 0; j < numNodos; j++) {
            if (matriz[i][j] == 0) {
                std::cout << std::setw(3) << "." << " ";
            } else {
                // Colorear si ambos nodos han sido visitados
                if (visitado[i] && visitado[j]) {
                    std::cout << GREEN << std::setw(3) << matriz[i][j] << RESET << " ";
                } else {
                    std::cout << std::setw(3) << matriz[i][j] << " ";
                }
            }
        }
        std::cout << "|\n";
    }
    
    // Linea inferior
    std::cout << "   ";
    for (int i = 0; i < numNodos; i++) {
        std::cout << "----";
    }
    std::cout << "-\n";
}

void GraphVisualizer::dijkstra(int inicio, int fin) {
    std::vector<int> distancia(numNodos, std::numeric_limits<int>::max());
    std::vector<int> previo(numNodos, -1);
    std::vector<bool> visitado(numNodos, false);
    
    distancia[inicio] = 0;
    
    std::cout << "\n=== Algoritmo de Dijkstra ===\n";
    std::cout << "Buscando camino mas corto de " << inicio << " a " << fin << "\n";

    for (int i = 0; i < numNodos; i++) {
        // Encontrar el nodo no visitado con menor distancia
        int u = -1;
        int minDist = std::numeric_limits<int>::max();
        for (int j = 0; j < numNodos; j++) {
            if (!visitado[j] && distancia[j] < minDist) {
                minDist = distancia[j];
                u = j;
            }
        }
        
        if (u == -1 || u == fin) break;
        
        visitado[u] = true;
        
        // Actualizar distancias
        for (int v = 0; v < numNodos; v++) {
            if (!visitado[v] && matriz[u][v] > 0) {
                int alt = distancia[u] + matriz[u][v];
                if (alt < distancia[v]) {
                    distancia[v] = alt;
                    previo[v] = u;
                }
            }
        }
        
        // Mostrar estado actual
        std::vector<int> camino;
        int actual = fin;
        while (actual != -1 && previo[actual] != -1) {
            camino.insert(camino.begin(), actual);
            actual = previo[actual];
        }
        if (!camino.empty()) {
            camino.insert(camino.begin(), inicio);
        }
        
        // Visualizar estado actual
        mostrarMatriz(visitado);
        std::cout << "Procesando nodo: " << RED << u << RESET << "\n";
        if (!camino.empty()) {
            std::cout << "Camino actual: ";
            for (size_t k = 0; k < camino.size(); k++) {
                std::cout << YELLOW << camino[k] << RESET;
                if (k < camino.size() - 1) std::cout << " -> ";
            }
            std::cout << "\n";
        }
        pausa();
    }
    
    // Mostrar resultado final
    if (distancia[fin] == std::numeric_limits<int>::max()) {
        std::cout << "\nNo existe camino entre " << inicio << " y " << fin << "\n";
    } else {
        std::cout << "\nDistancia minima: " << distancia[fin] << "\n";
        std::cout << "Camino: ";
        std::vector<int> camino;
        int actual = fin;
        while (actual != -1) {
            camino.insert(camino.begin(), actual);
            actual = previo[actual];
        }
        for (size_t i = 0; i < camino.size(); i++) {
            std::cout << GREEN << camino[i] << RESET;
            if (i < camino.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    }
}

void GraphVisualizer::dfs(int inicio) {
    std::stack<int> pila;
    std::vector<bool> visitado(numNodos, false);
    
    pila.push(inicio);
    
    std::cout << "\n=== Busqueda en Profundidad (DFS) ===\n";
    std::cout << "Iniciando desde el nodo " << inicio << "\n";
    
    while (!pila.empty()) {
        int actual = pila.top();
        pila.pop();
        
        if (!visitado[actual]) {
            visitado[actual] = true;
            
            // Agregar vecinos no visitados a la pila
            for (int i = numNodos - 1; i >= 0; i--) {
                if (matriz[actual][i] > 0 && !visitado[i]) {
                    pila.push(i);
                }
            }
            
            // Visualizar estado actual
            mostrarMatriz(visitado);
            std::cout << "Nodo actual: " << RED << actual << RESET << "\n";
            pausa();
        }
    }
    
    // Mostrar estado final
    std::cout << "\nRecorrido DFS completado\n";
    std::cout << "Nodos visitados: ";
    for (int i = 0; i < numNodos; i++) {
        if (visitado[i]) {
            std::cout << GREEN << i << RESET;
            if (i < numNodos - 1) std::cout << " -> ";
        }
    }
    std::cout << "\n";
}

void GraphVisualizer::bfs(int inicio) {
    std::queue<int> cola;
    std::vector<bool> visitado(numNodos, false);
    
    cola.push(inicio);
    visitado[inicio] = true;
    
    std::cout << "\n=== Busqueda en Amplitud (BFS) ===\n";
    std::cout << "Iniciando desde el nodo " << inicio << "\n";
    
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        
        // Agregar vecinos no visitados a la cola
        for (int i = 0; i < numNodos; i++) {
            if (matriz[actual][i] > 0 && !visitado[i]) {
                cola.push(i);
                visitado[i] = true;
            }
        }
        
        // Visualizar estado actual
        mostrarMatriz(visitado);
        std::cout << "Nodo actual: " << RED << actual << RESET << "\n";
        pausa();
    }
    
    // Mostrar estado final
    std::cout << "\nRecorrido BFS completado\n";
    std::cout << "Nodos visitados: ";
    for (int i = 0; i < numNodos; i++) {
        if (visitado[i]) {
            std::cout << GREEN << i << RESET;
            if (i < numNodos - 1) std::cout << " -> ";
        }
    }
    std::cout << "\n";
}