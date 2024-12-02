#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H

#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <random>

#include "Colors.h"

class GraphVisualizer {
private:
    std::vector<std::vector<int>> matriz;  // Matriz de adyacencia
    int numNodos;
    
    // Metodo para generar conexiones aleatorias
    void generarConexionesAleatorias(float densidad);
    
    // Metodo auxiliar para visualizar la matriz
    void mostrarMatriz(const std::vector<bool>& visitado) const;
    
    // Metodo para pausar la visualizacion
    void pausa(int milliseconds = 500) const;

public:
    // Constructor: recibe numero de nodos y densidad de conexiones (0.0 a 1.0)
    GraphVisualizer(int n, float densidad = 0.3);
    
    // Algoritmos principales
    void dijkstra(int inicio, int fin);
    void dfs(int inicio);
    void bfs(int inicio);
};

#endif