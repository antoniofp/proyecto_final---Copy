#ifndef SEARCH_VISUALIZER_H
#define SEARCH_VISUALIZER_H

#include <vector>
#include <string>

extern const std::string RESET;
extern const std::string RED;    
extern const std::string GREEN;   
extern const std::string YELLOW;  
extern const std::string BLUE;    

class SearchVisualizer {
private:
    std::vector<int> originalArr;  // Arreglo original desordenado
    std::vector<int> sortedArr;    // Arreglo ordenado para binary search
    void showProgress(int current, int total) const;
    void displayArray(const std::vector<int>& arr, int current, const std::string& message = "") const;

public:
    SearchVisualizer(const std::vector<int>& input_array);
    void linearSearch(int target);
    void binarySearch(int target);
};

#endif