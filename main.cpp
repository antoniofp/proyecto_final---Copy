#include <vector>   // Para usar vectores
#include <random>   // Para generar números aleatorios
#include <ctime>    
#include <algorithm> 

#include <iostream> 

#include "SearchVisualizer.h"
#include "SortVisualizer.h"

#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"

#include "GraphVisualizer.h"
#include "TreeVisualizer.h"
#include "BSTree.h"
#include "AVLTree.h"

#include "Colors.h"



std::vector<int> generarNumerosAleatorios(int cantidad, int numero) {
    // Crear un vector vacío del tamaño especificado
    std::vector<int> numeros(cantidad);
    
    // Inicializar el generador de números aleatorios con una semilla basada en el tiempo
    // Esto asegura que obtengamos diferentes números cada vez que ejecutemos el programa
    std::srand(std::time(nullptr));
    
    // Llenar el vector con números aleatorios
    // El ciclo for recorre cada posición del vector
    for (int i = 0; i < cantidad; i++) {
        // rand() % 100 genera números del 0 al 99
        numeros[i] = std::rand() % 100;
    }
    
    // Asegurar que el número especificado esté en el vector
    numeros[std::rand() % cantidad] = numero;
    
    // Devolver el vector lleno de números aleatorios
    return numeros;
}


void mostrarMenu() {
    std::cout << "Seleccione una opcion:\n";
    std::cout << "1. Algoritmos de busqueda\n";
    std::cout << "2. Algoritmos de ordenamiento\n";
    std::cout << "3. Estructuras lineales\n";
    std::cout << "4. Estructuras no lineales\n";
    std::cout << "5. Salir\n";
    std::cout << "Opcion: ";
}


int main() {
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                std::cout << "Algoritmos de búsqueda seleccionados.\n\n";
                
                std::vector<int> numeros = generarNumerosAleatorios(20, 8);
                std::cout << "Vector desordenado: \n";
                for (int num : numeros) {
                    std::cout << num << " ";
                }
                std::cout << "\n\n";
                SearchVisualizer busquedas(numeros);
                std::cout << "Que numero quieres buscar? ";
                int num;
                std::cin >> num;
                std::cout << "Quieres usar busqueda lineal o binaria? (1/2): ";
                int tipoBusqueda;
                std::cin >> tipoBusqueda;
                if (tipoBusqueda == 1) {
                    busquedas.linearSearch(num);
                } else if (tipoBusqueda == 2) {
                    busquedas.binarySearch(num);
                } else {
                    std::cout << "Opcion no válida. Intente de nuevo.\n";
                }
                std::cout << "\nPresione Enter para volver al menu principal...";
                std::cin.clear();
                std::cin.ignore();
                std::cin.get();
                break;
            }
            case 2: {
                std::cout << "Algoritmos de ordenamiento seleccionados.\n\n";                
                // Pregunta al usuario el tamaño del vector
                int tamano;
                std::cout << "Ingrese el size del vector a ordenar (recomendado: 10-20): ";
                std::cin >> tamano;
                
                // Genera el vector aleatorio
                std::vector<int> numeros = generarNumerosAleatorios(tamano, 8);
                
                // Muestra el vector inicial
                std::cout << "\nVector desordenado:\n";
                for (int num : numeros) {
                    std::cout << num << " ";
                }
                std::cout << "\n\n";
                
                // Menú de algoritmos de ordenamiento
                std::cout << "Seleccione el algoritmo de ordenamiento:\n";
                std::cout << "1. Bubble Sort \n";
                std::cout << "   - Compara elementos adyacentes e intercambia si están en orden incorrecto\n";
                std::cout << "2. Selection Sort\n";
                std::cout << "   - Busca el menor elemento y lo coloca al inicio\n";
                std::cout << "3. Insertion Sort \n";
                std::cout << "   - Construye el arreglo ordenado insertando un elemento a la vez\n";
                std::cout << "4. Merge Sort\n";
                std::cout << "   - Divide el arreglo en mitades, ordena recursivamente y combina\n";
                std::cout << "5. Quick Sort\n";
                std::cout << "   - Usa un pivote para dividir el arreglo y ordena recursivamente\n";
                std::cout << "Opcion: ";
                
                int algoritmo;
                std::cin >> algoritmo;
                
                // Crea el visualizador con el vector generado
                SortVisualizer ordenamiento(numeros);
                
                // Ejecuta el algoritmo seleccionado
                switch (algoritmo) {
                    case 1:
                        ordenamiento.bubbleSort();
                        std::cout << "Complejidad temporal: O(n^2), Complejidad espacial: O(1)\n";
                        break;
                    case 2:
                        ordenamiento.selectionSort();
                        std::cout << "Complejidad temporal: O(n^2), Complejidad espacial: O(1)\n";
                        break;
                    case 3:
                        ordenamiento.insertionSort();
                        std::cout << "Complejidad temporal: O(n^2), Complejidad espacial: O(1)\n";
                        break;
                    case 4:
                        ordenamiento.mergeSort();
                        std::cout << "Complejidad temporal: O(n log n), Complejidad espacial: O(n)\n";
                        break;
                    case 5:
                        ordenamiento.quickSort();
                        std::cout << "Complejidad temporal: O(n log n), Complejidad espacial: O(log n)\n";
                        break;
                    default:
                        std::cout << "Opcion no válida.\n";
                }
                
                // Espera a que el usuario presione Enter antes de volver al menú principal
                std::cout << "\nPresione Enter para volver al menu principal...";
                std::cin.clear();
                std::cin.ignore();
                std::cin.get();
                break;
            }
            case 3: {
    int opcionEstructura;
    do {
        std::cout << "Estructuras Lineales: \n\n";
        std::cout << "1. Pila (Stack)\n";
        std::cout << "2. Cola (Queue)\n";
        std::cout << "3. Lista Enlazada (Linked List)\n";
        std::cout << "4. Volver al menu principal\n";
        std::cout << "Opcion: ";
        std::cin >> opcionEstructura;

        switch (opcionEstructura) {
            case 1: {
                Stack pila;
                int opcionPila;
                do {
                    std::cout << "\nOperaciones de Pila:\n";
                    std::cout << "1. Push (Insertar)\n";
                    std::cout << "2. Pop (Eliminar)\n";
                    std::cout << "3. Ver tope\n";
                    std::cout << "4. Volver\n";
                    std::cout << "Opcion: ";
                    std::cin >> opcionPila;

                    switch (opcionPila) {
                        case 1: {
                            int valor;
                            std::cout << "Ingrese valor a insertar: ";
                            std::cin >> valor;
                            pila.push(valor);
                            break;
                        }
                        case 2:
                            pila.pop();
                            break;
                        case 3: {
                            int tope = pila.peek();
                            if (tope != -1) {
                                std::cout << "Elemento en el tope: " << tope << std::endl;
                            }
                            break;
                        }
                        case 4:
                            std::cout << "Volviendo al menu de estructuras...\n";
                            break;
                        default:
                            std::cout << "Opcion invalida\n";
                    }
                } while (opcionPila != 4);
                break;
            }
            case 2: {
                Queue cola;
                int opcionCola;
                do {
                    std::cout << "\nOperaciones de Cola:\n";
                    std::cout << "1. Enqueue (Insertar)\n";
                    std::cout << "2. Dequeue (Eliminar)\n";
                    std::cout << "3. Ver frente\n";
                    std::cout << "4. Volver\n";
                    std::cout << "Opcion: ";
                    std::cin >> opcionCola;

                    switch (opcionCola) {
                        case 1: {
                            int valor;
                            std::cout << "Ingrese valor a insertar: ";
                            std::cin >> valor;
                            cola.enqueue(valor);
                            break;
                        }
                        case 2:
                            cola.dequeue();
                            break;
                        case 3: {
                            int frente = cola.getFront();
                            if (frente != -1) {
                                std::cout << "Elemento en el frente: " << frente << std::endl;
                            }
                            break;
                        }
                        case 4:
                            std::cout << "Volviendo al menu de estructuras...\n";
                            break;
                        default:
                            std::cout << "Opcion invalida\n";
                    }
                } while (opcionCola != 4);
                break;
            }
            case 3: {
                LinkedList lista;
                int opcionLista;
                do {
                    std::cout << "\nOperaciones de Lista Enlazada:\n";
                    std::cout << "1. Insertar al inicio\n";
                    std::cout << "2. Eliminar al inicio\n";
                    std::cout << "3. Eliminar por valor\n";
                    std::cout << "4. Buscar elemento\n";
                    std::cout << "5. Volver\n";
                    std::cout << "Opcion: ";
                    std::cin >> opcionLista;

                    switch (opcionLista) {
                        case 1: {
                            int valor;
                            std::cout << "Ingrese valor a insertar: ";
                            std::cin >> valor;
                            lista.insertAtBegin(valor);
                            break;
                        }
                        case 2:
                            lista.deleteAtBegin();
                            break;
                        case 3: {
                            int valor;
                            std::cout << "Ingrese valor a eliminar: ";
                            std::cin >> valor;
                            lista.deleteByValue(valor);
                            break;
                        }
                        case 4: {
                            int valor;
                            std::cout << "Ingrese valor a buscar: ";
                            std::cin >> valor;
                            lista.find(valor);
                            break;
                        }
                        case 5:
                            std::cout << "Volviendo al menu de estructuras...\n";
                            break;
                        default:
                            std::cout << "Opcion invalida\n";
                    }
                } while (opcionLista != 5);
                break;
            }
            case 4:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion invalida\n";
        }
    } while (opcionEstructura != 4);
    break;
}
            case 4: {
    int opcionEstructura;
    do {
        std::cout << "\nEstructuras No Lineales:\n\n";
        std::cout << "1. Arboles (BST y AVL)\n";
        std::cout << "2. Grafos\n";
        std::cout << "3. Volver al menu principal\n";
        std::cout << "Opcion: ";
        std::cin >> opcionEstructura;

        switch (opcionEstructura) {
            case 1: {
                // Crear instancias de ambos arboles
                BSTree arbolNormal;
                AVLTree arbolAVL;
                int opcionArbol;
                
                do {
                    std::cout << "\nOperaciones con Arboles:\n";
                    std::cout << "1. Insertar numero en ambos arboles\n";
                    std::cout << "2. Buscar numero en ambos arboles\n";
                    std::cout << "3. Comparar profundidad de ambos arboles\n";
                    std::cout << "4. Volver\n";
                    std::cout << "Opcion: ";
                    std::cin >> opcionArbol;

                    switch (opcionArbol) {
                        case 1: {
                            int valor;
                            std::cout << "Ingrese el numero a insertar: ";
                            std::cin >> valor;
                            
                            // Insertar en BST normal
                            std::cout << "\n=== Insertando en Arbol Binario Normal ===\n";
                            arbolNormal.insertar(valor);
                            
                            // Insertar en AVL
                            std::cout << "\n=== Insertando en Arbol AVL ===\n";
                            arbolAVL.insertar(valor);
                            
                            // Mostrar profundidades actuales
                            std::cout << YELLOW << "\nProfundidad actual BST: " << arbolNormal.obtenerProfundidadMax() << RESET;
                            std::cout << YELLOW << "\nProfundidad actual AVL: " << arbolAVL.obtenerProfundidadMax() << RESET << "\n";
                            
                            std::cout << "\nPresione Enter para continuar...";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin.get();
                            break;
                        }
                        case 2: {
                            int valor;
                            std::cout << "Ingrese el numero a buscar: ";
                            std::cin >> valor;
                            
                            // Buscar en BST normal
                            std::cout << "\n=== Buscando en Arbol Binario Normal ===\n";
                            bool encontradoBST = arbolNormal.buscar(valor);
                            
                            // Buscar en AVL
                            std::cout << "\n=== Buscando en Arbol AVL ===\n";
                            bool encontradoAVL = arbolAVL.buscar(valor);
                            
                            // Mostrar resultados
                            std::cout << "\nResultados de la busqueda:\n";
                            std::cout << "BST: " << (encontradoBST ? (GREEN + "Encontrado") : (RED + "No encontrado")) << RESET << "\n";
                            std::cout << "AVL: " << (encontradoAVL ? (GREEN + "Encontrado") : (RED + "No encontrado")) << RESET << "\n";
                            
                            std::cout << "\nPresione Enter para continuar...";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin.get();
                            break;
                        }
                        case 3: {
                            // Comparar profundidades
                            int profBST = arbolNormal.obtenerProfundidadMax();
                            int profAVL = arbolAVL.obtenerProfundidadMax();
                            
                            std::cout << "\n=== Comparacion de Profundidades ===\n";
                            std::cout << "Arbol BST: " << YELLOW << profBST << RESET << " niveles\n";
                            std::cout << "Arbol AVL: " << YELLOW << profAVL << RESET << " niveles\n\n";
                            
                            if (profBST > profAVL) {
                                std::cout << GREEN << "El arbol AVL es mas eficiente con una diferencia de "
                                        << RED << (profBST - profAVL) << GREEN << " niveles\n" << RESET;
                            } else if (profBST < profAVL) {
                                std::cout << "Caso inusual: El BST tiene menor profundidad\n";
                            } else {
                                std::cout << "Ambos arboles tienen la misma profundidad\n";
                            }
                            
                            std::cout << "\nPresione Enter para continuar...";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin.get();
                            break;
                        }
                        case 4:
                            std::cout << "Volviendo al menu anterior...\n";
                            break;
                        default:
                            std::cout << "Opcion invalida\n";
                    }
                } while (opcionArbol != 4);
                break;
            }
            case 2: {
                int numNodos;
                float densidad;
                std::cout << "Ingrese el numero de nodos (recomendado: 5-10): ";
                std::cin >> numNodos;
                
                std::cout << "Ingrese la densidad del grafo (0.0 - 1.0): ";
                std::cin >> densidad;
                
                GraphVisualizer grafo(numNodos, densidad);
                
                int opcionGrafo;
                do {
                    std::cout << "\nOperaciones con Grafos:\n";
                    std::cout << "1. Busqueda en Profundidad (DFS)\n";
                    std::cout << "2. Busqueda en Amplitud (BFS)\n";
                    std::cout << "3. Algoritmo de Dijkstra\n";
                    std::cout << "4. Volver\n";
                    std::cout << "Opcion: ";
                    std::cin >> opcionGrafo;

                    switch (opcionGrafo) {
                        case 1: {
                            int nodoInicio;
                            std::cout << "Ingrese el nodo de inicio (0 a " << numNodos-1 << "): ";
                            std::cin >> nodoInicio;
                            if(nodoInicio >= 0 && nodoInicio < numNodos) {
                                grafo.dfs(nodoInicio);
                            } else {
                                std::cout << "Nodo invalido\n";
                            }
                            break;
                        }
                        case 2: {
                            int nodoInicio;
                            std::cout << "Ingrese el nodo de inicio (0 a " << numNodos-1 << "): ";
                            std::cin >> nodoInicio;
                            if(nodoInicio >= 0 && nodoInicio < numNodos) {
                                grafo.bfs(nodoInicio);
                            } else {
                                std::cout << "Nodo invalido\n";
                            }
                            break;
                        }
                        case 3: {
                            int inicio, fin;
                            std::cout << "Ingrese el nodo de inicio (0 a " << numNodos-1 << "): ";
                            std::cin >> inicio;
                            std::cout << "Ingrese el nodo final (0 a " << numNodos-1 << "): ";
                            std::cin >> fin;
                            if(inicio >= 0 && inicio < numNodos && fin >= 0 && fin < numNodos) {
                                grafo.dijkstra(inicio, fin);
                            } else {
                                std::cout << "Nodos invalidos\n";
                            }
                            break;
                        }
                        case 4:
                            std::cout << "Volviendo al menu anterior...\n";
                            break;
                        default:
                            std::cout << "Opcion invalida\n";
                    }
                    
                    if(opcionGrafo != 4) {
                        std::cout << "\nPresione Enter para continuar...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    }
                } while (opcionGrafo != 4);
                break;
            }
            case 3:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion invalida\n";
        }
    } while (opcionEstructura != 3);
    break;
}
            case 5:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}

