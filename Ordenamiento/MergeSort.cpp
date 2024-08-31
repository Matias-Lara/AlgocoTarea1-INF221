#include <iostream>
#include <vector>

#include "auxiliary.h"

//Fuente: https://github.com/codigo404/Cpp-Data-structures-and-algorithms/tree/main/sortingAlgorithms/mergeSort

void Merge(std::vector<int>& arr, int begin, int middle, int end) {
    int i, j, k;

    //Tamanio de los dos sub Arr.
    int sizeLeft = middle - begin + 1;
    int sizeRight = end - middle;
    
    std::vector<int> arrLeft(sizeLeft);
    std::vector<int> arrRight(sizeRight);

    //Se rellena el sub arr izquierdo.
    for (int i = 0; i < sizeLeft; i++) {
        arrLeft[i] = arr[begin + i];
    }
    //Se rellena el sub arr derecho.
    for (int j = 0; j < sizeRight; j++) {
        arrRight[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = begin;

    //Se comparan los elementos de las dos lista 1 por 1 y se ordenan en el arr "principal".
    while (i < sizeLeft && j < sizeRight) {
        if (arrLeft[i] <= arrRight[j]) {
            arr[k] = arrLeft[i];
            i++;
        } else {
            arr[k] = arrRight[j];
            j++;
        }
        k++;
    }

    //Si es que i < sizeLeft sigue siendo true, quiere decir que aun quedan elementos en arrLeft.
    //Por lo que se insertaran en el arr "principal" en el mismo orden que estan, porque ya estan ordenados.
    while (i < sizeLeft) {
        arr[k] = arrLeft[i];
        i++;
        k++;
    }
    //Analago al while anterior pero en el arrRight.
    while (j < sizeRight) {
        arr[k] = arrRight[j];
        j++;
        k++;
    }
}


void MergeSort(std::vector<int>& arr, int begin, int end) {
    //Verifica si el arr es divisible aun.
    if (begin < end) {
        //Punto medio del arr a separar en 2.
        int middle = begin + (end - begin) / 2;

        //Parte recursiva:
        //Se divide en todos los subarreglos de la rama izquierda hasta arreglos de un solo elemento.
        MergeSort(arr, begin, middle);
        //Luego recursivamente se hace lo mismo con la rama derecha.
        MergeSort(arr, middle + 1, end);

        //Se fusionan las dos mitades en un solo arreglo ordenado
        Merge(arr, begin, middle, end);
    }
}


int main() {

    std::vector<int> arr = generate_arr(100);

    std::cout << "Vector Generado: ";
    printArray(arr);

    int size = arr.size();
    MergeSort(arr, 0, size - 1);

    std::cout << "Vector Ordenado";
    printArray(arr);

    return 0;
}


