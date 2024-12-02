#include "SortVisualizer.h"
#include <iostream>
#include <thread>
#include <chrono>

// Colores para la visualización (los mismos que en SearchVisualizer)
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";     // Elemento actual
const std::string GREEN = "\033[32m";    // Elemento ordenado
const std::string YELLOW = "\033[33m";   // Elemento secundario
const std::string BLUE = "\033[34m";     // Elementos comparados

//el constructor recibe el vector a ordenar e inicializa el atributo arr
SortVisualizer::SortVisualizer(const std::vector<int>& input_array) 
    : arr(input_array) {}


//se define el tiempo de sleep
void SortVisualizer::sleep() const {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void SortVisualizer::displayArray(const std::vector<int>& arr, int current, int secondary) const {
    // Muestra el arreglo, resaltando los elementos importantes
    for (size_t i = 0; i < arr.size(); i++) {
        if (i == current) {
            std::cout << RED << "[" << arr[i] << "]" << RESET << " ";
        } else if (i == secondary) {
            std::cout << YELLOW << "[" << arr[i] << "]" << RESET << " ";
        } else {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << "\n";
}


//barra de progreso
void SortVisualizer::showProgress(int current, int total) const {
    std::cout << "[";
    for (int i = 0; i < total; i++) {
        if (i < current) std::cout << "=";
        else if (i == current) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << (current * 100 / total) << "%\n";
}

//funcion para intercambiar dos elementos
void SortVisualizer::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Implementación de Bubble Sort
void SortVisualizer::bubbleSort() {
    std::cout << "\n=== Bubble Sort ===\n";
    int n = arr.size();
    
    // Recorre todo el arreglo
    for (int i = 0; i < n-1; i++) {
        bool swapped = false;
        
        // Para cada elemento, lo compara con el siguiente
        for (int j = 0; j < n-i-1; j++) {
            std::cout << "Comparando: ";
            displayArray(arr, j, j+1);  // Muestra los elementos que se están comparando
            
            // Si el elemento actual es mayor que el siguiente, los intercambia
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
            
            sleep();
        }
        
        // Si no hubo intercambios en esta pasada, el arreglo ya está ordenado
        if (!swapped)
            break;
            
        showProgress(i+1, n);
    }
    
    std::cout << GREEN << "Ordenamiento completado!" << RESET << "\n";
    displayArray(arr);
}

// Implementación de Selection Sort
void SortVisualizer::selectionSort() {
    std::cout << "\n=== Selection Sort ===\n";
    int n = arr.size();
    
    // Recorre el arreglo
    for (int i = 0; i < n-1; i++) {
        // Encuentra el elemento mínimo en el subarreglo desordenado
        int min_idx = i;
        std::cout << "Buscando el mínimo desde posicion " << i << ":\n";
        
        for (int j = i+1; j < n; j++) {
            displayArray(arr, min_idx, j);  // Muestra el mínimo actual y el elemento que se está comparando
            sleep();
            
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Intercambia el elemento mínimo encontrado con el primer elemento del subarreglo desordenado
        if (min_idx != i) {
            std::cout << "Intercambiando " << arr[i] << " con " << arr[min_idx] << "\n";
            swap(arr[i], arr[min_idx]);
            displayArray(arr, i);
            sleep();
        }
        
        showProgress(i+1, n);
    }
    
    std::cout << GREEN << "Ordenamiento completado!" << RESET << "\n";
    displayArray(arr);
}

// Implementación de Insertion Sort
void SortVisualizer::insertionSort() {
    std::cout << "\n=== Insertion Sort ===\n";
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Estado inicial - ROJO: elemento a insertar, VERDE: ya ordenados
        for (int k = 0; k < n; k++) {
            if (k == i) {
                std::cout << RED << "[" << arr[k] << "]" << RESET << " ";
            } else if (k < i) {
                std::cout << GREEN << arr[k] << RESET << " ";
            } else {
                std::cout << arr[k] << " ";
            }
        }
        std::cout << "\n";
        sleep();
        
        while (j >= 0) {
            // ROJO: elemento a insertar, AMARILLO: elemento comparando
            for (int k = 0; k < n; k++) {
                if (k == j) {
                    std::cout << YELLOW << "[" << arr[k] << "]" << RESET << " ";
                } else if (k == i) {
                    std::cout << RED << "[" << key << "]" << RESET << " ";
                } else if (k < i) {
                    std::cout << GREEN << arr[k] << RESET << " ";
                } else {
                    std::cout << arr[k] << " ";
                }
            }
            std::cout << "\n";
            sleep();
            
            if (arr[j] <= key) {
                break;
            }
            
            arr[j + 1] = arr[j];
            
            // AZUL: indica el movimiento/swap
            for (int k = 0; k < n; k++) {
                if (k == j) {
                    std::cout << BLUE << "[" << key << "]" << RESET << " ";
                } else if (k == j + 1) {
                    std::cout << BLUE << "[" << arr[k] << "]" << RESET << " ";
                } else if (k < i) {
                    std::cout << GREEN << arr[k] << RESET << " ";
                } else {
                    std::cout << arr[k] << " ";
                }
            }
            std::cout << "\n";
            sleep();
            
            j--;
        }
        
        arr[j + 1] = key;
        
        // Mostrar el resultado de la iteración - todo lo ordenado en VERDE
        for (int k = 0; k < n; k++) {
            if (k <= i) {
                std::cout << GREEN << arr[k] << RESET << " ";
            } else {
                std::cout << arr[k] << " ";
            }
        }
        std::cout << "\n\n";
        sleep();
    }
    
    // Estado final
    std::cout << GREEN;
    displayArray(arr);
    std::cout << RESET;
}

//parte recursiva de merge sort
void SortVisualizer::mergeSortHelper(int left, int right, int depth) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Mostrar división actual
        std::cout << "\nDividiendo seccion:\n";
        for (int i = 0; i < arr.size(); i++) {
            if (i < left || i > right) {
                // Secciones fuera del rango actual
                std::cout << GREEN << arr[i] << RESET << " ";
            }
            else if (i <= mid) {
                // Primera mitad
                std::cout << BLUE << arr[i] << RESET << " ";
            }
            else {
                // Segunda mitad
                std::cout << YELLOW << arr[i] << RESET << " ";
            }
        }
        std::cout << "\n";
        sleep();

        // Ordenar recursivamente
        mergeSortHelper(left, mid, depth + 1);
        mergeSortHelper(mid + 1, right, depth + 1);
        
        // Combinar las partes ordenadas
        merge(left, mid, right, depth);
        
        // Mostrar estado actual del arreglo completo
        std::cout << "\nEstado actual del arreglo:\n";
        for (int i = 0; i < arr.size(); i++) {
            if (i >= left && i <= right) {
                // Sección recién ordenada
                std::cout << GREEN << "[" << arr[i] << "]" << RESET << " ";
            } else {
                // Resto del arreglo
                std::cout << arr[i] << " ";
            }
        }
        std::cout << "\n";
        sleep();
    }
}

void SortVisualizer::merge(int left, int mid, int right, int depth) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    // Mostrar la sección que vamos a combinar
    std::cout << "\nCombinando secciones:\n";
    for (int x = 0; x < arr.size(); x++) {
        if (x < left || x > right) {
            // Elementos fuera de la sección actual (ya ordenados)
            std::cout << GREEN << arr[x] << RESET << " ";
        }
        else if (x <= mid) {
            // Subarray izquierdo
            std::cout << BLUE << "[" << arr[x] << "]" << RESET << " ";
        }
        else {
            // Subarray derecho
            std::cout << YELLOW << "[" << arr[x] << "]" << RESET << " ";
        }
    }
    std::cout << "\n";
    sleep();

    // Proceso de combinación
    std::cout << "Combinando...\n";
    while (i <= mid && j <= right) {
        // Mostrar estado actual con elementos siendo comparados en rojo
        for (int x = 0; x < arr.size(); x++) {
            if (x < left || x > right) {
                std::cout << GREEN << arr[x] << RESET << " ";
            }
            else if (x == i) {
                std::cout << RED << "[" << arr[x] << "]" << RESET << " ";
            }
            else if (x == j) {
                std::cout << RED << "[" << arr[x] << "]" << RESET << " ";
            }
            else if (x <= mid) {
                std::cout << BLUE << arr[x] << RESET << " ";
            }
            else {
                std::cout << YELLOW << arr[x] << RESET << " ";
            }
        }
        std::cout << "\n";
        
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
        sleep();
    }

    // Copiar elementos restantes
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copiar de vuelta al array original y mostrar resultado
    for (i = 0; i < k; i++) {
        arr[left + i] = temp[i];
    }

    // Mostrar resultado de la combinación
    std::cout << "Resultado:\n";
    for (int x = 0; x < arr.size(); x++) {
        if (x >= left && x <= right) {
            // Sección recién ordenada en verde brillante
            std::cout << GREEN << "[" << arr[x] << "]" << RESET << " ";
        } else {
            // Resto del arreglo sin cambios
            std::cout << arr[x] << " ";
        }
    }
    std::cout << "\n";
    sleep();
}

// Implementación de Merge Sort
void SortVisualizer::mergeSort() {
    std::cout << "\n=== Merge Sort ===\n";
    mergeSortHelper(0, arr.size() - 1, 0);  // Inicia con profundidad 0
    std::cout << GREEN << "¡Ordenamiento completado!" << RESET << "\n";
    displayArray(arr);
}


// Implementación de Quick Sort
void SortVisualizer::quickSort() {
    std::cout << "\n=== Quick Sort ===\n";
    quickSortHelper(0, arr.size() - 1, 0);  // Inicia con profundidad 0
    std::cout << GREEN << "Ordenamiento completado!" << RESET << "\n";
    displayArray(arr);
}

//lo hice igual que el merge sort, esta es la parte recursiva de quick sort
void SortVisualizer::quickSortHelper(int low, int high, int depth) {
    if (low < high) {
        // Particionar el arreglo
        int pi = partition(low, high, depth);
        
        // Mostrar el estado global después de cada partición completa
        std::cout << "\nEstado actual del arreglo:\n";
        for (int i = 0; i < arr.size(); i++) {
            if (i < low || i > high) {
                // Secciones ya ordenadas
                std::cout << GREEN << arr[i] << RESET << " ";
            } else if (i == pi) {
                // Pivote en su posición final
                std::cout << RED << "[" << arr[i] << "]" << RESET << " ";
            } else if (i < pi) {
                // Sección izquierda por ordenar
                std::cout << BLUE << arr[i] << RESET << " ";
            } else {
                // Sección derecha por ordenar
                std::cout << YELLOW << arr[i] << RESET << " ";
            }
        }
        std::cout << "\n";
        sleep();
        
        // Ordenar recursivamente las subpartes
        quickSortHelper(low, pi - 1, depth + 1);
        quickSortHelper(pi + 1, high, depth + 1);
    }
}

int SortVisualizer::partition(int low, int high, int depth) {
    int pivot = arr[high];
    int i = low - 1;
    
    // Mostrar sección actual que estamos particionando
    std::cout << "\nParticionando seccion:\n";
    for (int x = 0; x < arr.size(); x++) {
        if (x < low || x > high) {
            // Elementos fuera de la sección actual en verde (ya ordenados)
            std::cout << GREEN << arr[x] << RESET << " ";
        } else if (x == high) {
            // Pivote en rojo
            std::cout << RED << "[" << arr[x] << "]" << RESET << " ";
        } else {
            // Elementos actuales en blanco
            std::cout << arr[x] << " ";
        }
    }
    std::cout << "\n";
    sleep();
    
    // Proceso de partición (sin mostrar intercambios intermedios)
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            if (i != j) {
                swap(arr[i], arr[j]);
            }
        }
    }
    
    // Colocar el pivote en su posición final
    swap(arr[i + 1], arr[high]);
    
    // Mostrar el resultado final de esta partición
    std::cout << "Resultado de particion:\n";
    for (int x = 0; x < arr.size(); x++) {
        if (x < low || x > high) {
            // Secciones ya ordenadas
            std::cout << GREEN << arr[x] << RESET << " ";
        } else if (x == i + 1) {
            // Pivote en su posición final
            std::cout << RED << "[" << arr[x] << "]" << RESET << " ";
        } else if (x <= i) {
            // Elementos menores que el pivote
            std::cout << BLUE << arr[x] << RESET << " ";
        } else {
            // Elementos mayores que el pivote
            std::cout << YELLOW << arr[x] << RESET << " ";
        }
    }
    std::cout << "\n";
    sleep();
    
    return i + 1;
}