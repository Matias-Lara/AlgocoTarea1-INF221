#include "auxiliary.h"
#include <random>

//Genera un arr de n enteros aleatorios
std::vector<int> generate_arr(size_t n) {
    std::vector<int> arr(n);
    
    //Biblioteca <random>
    std::random_device rd;  //Semilla
    std::mt19937 gen(rd()); //Generador Mersenne Twister
    std::uniform_int_distribution<> dis(1, 100); //Distribución uniforme
    
    for(size_t i = 0; i < n; ++i) {
        arr[i] = dis(gen); 
    }
    
    return arr;
}

//Imprime un arr
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}