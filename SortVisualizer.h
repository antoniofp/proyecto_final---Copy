#ifndef SORT_VISUALIZER_H
#define SORT_VISUALIZER_H

#include <vector>
#include <string>

class SortVisualizer {
private:
    std::vector<int> arr;  // Vector que almacenará los números a ordenar
    
    // Métodos auxiliares para la visualización
    void displayArray(const std::vector<int>& arr, int current = -1, int secondary = -1) const;
    void showProgress(int current, int total) const;
    void sleep() const;  // Pausa para la animación
    
    // Métodos auxiliares para el ordenamiento
    void swap(int& a, int& b);  // Intercambia dos elementos
    
public:
    // Constructor que recibe el vector a ordenar
    SortVisualizer(const std::vector<int>& input_array);
    
    // Métodos de ordenamiento, para los recursivos este es el caso base
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void mergeSort();
    void quickSort();
    
private:
    // Métodos auxiliares para ordenamientos recursivos
    //son la parte recursiva de los algoritmos de ordenamiento
    void mergeSortHelper(int left, int right, int depth = 0);
    void merge(int left, int mid, int right, int depth);
    void quickSortHelper(int low, int high, int depth = 0);
    int partition(int low, int high, int depth);
};

#endif