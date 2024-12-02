#include "SearchVisualizer.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <algorithm>

#include "Colors.h"



SearchVisualizer::SearchVisualizer(const std::vector<int>& input_array) 
    : originalArr(input_array), sortedArr(input_array) {
    // Ordenar el arreglo para binary search
    std::sort(sortedArr.begin(), sortedArr.end());
}


void SearchVisualizer::showProgress(int current, int total) const {
    std::cout << "\n";
    std::cout << "[";
    for (int i = 0; i < total; i++) {
        if (i < current) std::cout << "=";
        else if (i == current) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << (current * 100 / total) << "%";
}

void SearchVisualizer::displayArray(const std::vector<int>& arr, int current, const std::string& message) const {
    std::cout << message;
    for (size_t i = 0; i < arr.size(); i++) {
        if (i == current) {
            std::cout << RED << "[" << arr[i] << "]" << RESET << " ";
        } else {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << "\n";
}

void SearchVisualizer::linearSearch(int target) {
    std::cout << "\n=== Busqueda Lineal: buscando " << target << " ===\n";
    std::cout << "Arreglo original:\n";
    
    for (size_t i = 0; i < originalArr.size(); i++) {
        // Mostrar estado actual
        std::cout << "Paso " << i + 1 << ": ";
        for (size_t j = 0; j < originalArr.size(); j++) {
            if (j == i) {
                std::cout << RED << "[" << originalArr[j] << "]" << RESET << " ";
            } else if (j < i) {
                std::cout << BLUE << originalArr[j] << RESET << " ";
            } else {
                std::cout << originalArr[j] << " ";
            }
        }
        
        std::cout << " | ";
        showProgress(i, originalArr.size());
        std::cout << "\n";
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (originalArr[i] == target) {
            std::cout << GREEN << "Encontrado en posicion " << i << "!" << RESET << "\n";
            return;
        }
    }
    std::cout << RED << "Elemento no encontrado" << RESET << "\n";
}

void SearchVisualizer::binarySearch(int target) {
    std::cout << "\n=== Busqueda Binaria: buscando " << target << " ===\n";
    std::cout << "Arreglo ordenado para busqueda binaria:\n";
    displayArray(sortedArr, -1, "");
    
    int left = 0;
    int right = sortedArr.size() - 1;
    int iteration = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        iteration++;

        // Mostrar estado actual
        std::cout << "Iteracion " << iteration << ": ";
        for (size_t i = 0; i < sortedArr.size(); i++) {
            if (i == mid) {
                std::cout << RED << "[" << sortedArr[i] << "]" << RESET << " ";
            } else if (i >= left && i <= right) {
                std::cout << YELLOW << sortedArr[i] << RESET << " ";
            } else {
                std::cout << BLUE << sortedArr[i] << RESET << " ";
            }
        }
        
        std::cout << " | L:" << left << " M:" << mid << " R:" << right << "\n";
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (sortedArr[mid] == target) {
            std::cout << GREEN << "Encontrado en posicion " << mid << " del arreglo ordenado!" << RESET << "\n";
            return;
        }

        if (sortedArr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    std::cout << RED << "Elemento no encontrado" << RESET << "\n";
}