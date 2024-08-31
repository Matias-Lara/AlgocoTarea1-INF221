#include <iostream>
#include <vector>

#include "auxiliary.h"


//Fuente: https://www.geeksforgeeks.org/quick-sort-algorithm/

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
  
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    

    std::swap(arr[i + 1], arr[high]);  
    return i + 1;
}


void QuickSort(std::vector<int>& arr, int low, int high) {
  
    if (low < high) {
      
        int pi = partition(arr, low, high);

        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}




int main() {

    std::vector<int> arr = generate_arr(100);

    std::cout << "Vector Generado: ";
    printArray(arr);

    int size = arr.size();
    QuickSort(arr, 0, size - 1);

    std::cout << "Vector Ordenado";
    printArray(arr);

    return 0;
}