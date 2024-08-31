#include <iostream>
#include <vector>
#include <random>

#include "auxiliary.h"

std::vector<int> Bubblesort(std::vector<int> arr) {
    int n = arr.size();
    for (size_t i = 0; i < n; i++) {
        //j solo necesita iterar hasta el ultimo elemento que no ha sido colocado en su posición final.
        for (size_t j = 0; j < (n - i - 1) ; j++) {
            //Si el elemento j es mayor que el elemento que le sigue, debe "burbujear" para subir a la siguiente posicion.
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
    return arr;
}


int main() {

    std::vector<int> arr = generate_arr(100);

    std::cout << "Vector Generado: ";
    printArray(arr);

    int size = arr.size();
    Bubblesort(arr);

    std::cout << "Vector Ordenado";
    printArray(arr);

    return 0;
}