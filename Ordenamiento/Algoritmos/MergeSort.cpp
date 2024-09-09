#include "ahead.h"
#include "auxiliary.h"

using namespace std;

/*
 * Este archivo contiene código adaptado de:
 * https://github.com/codigo404/Cpp-Data-structures-and-algorithms/tree/main/sortingAlgorithms/mergeSort
 */

void Merge(vector<int>& arr, int begin, int middle, int end) {
    int i, j, k;

    //Tamanio de los subArr
    int sizeLeft = middle - begin + 1;
    int sizeRight = end - middle;
    
    vector<int> arrLeft(sizeLeft);
    vector<int> arrRight(sizeRight);

    //Se rellena el sub arr izquierdo
    for (int i = 0; i < sizeLeft; i++) {
        arrLeft[i] = arr[begin + i];
    }
    //Analogo con el derecho
    for (int j = 0; j < sizeRight; j++) {
        arrRight[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = begin;

    //Se comparan los elementos de las dos lista 1 por 1 y se ordenan en el arr "principal"
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

    //Si es que i < sizeLeft sigue siendo true, quiere decir que aun quedan elementos en arrLeft
    //Por lo que se insertaran en el arr "principal" en el mismo orden que estan, porque ya estan ordenados
    while (i < sizeLeft) {
        arr[k] = arrLeft[i];
        i++;
        k++;
    }
    //Analago para arrRight
    while (j < sizeRight) {
        arr[k] = arrRight[j];
        j++;
        k++;
    }
}


void MergeSort(vector<int>& arr, int begin, int end) {
    //Verifica si el arr es divisible aun.
    if (begin < end) {
        //Punto medio del arr a separar en 2.
        int middle = begin + (end - begin) / 2;

        //Parte recursiva:
        //Se divide en todos los subarreglos de la rama izquierda hasta arreglos de un solo elemento
        MergeSort(arr, begin, middle);
        //Luego recursivamente se hace lo mismo con la rama derecha
        MergeSort(arr, middle + 1, end);

        //Se fusionan las dos mitades en un solo arreglo ordenado
        Merge(arr, begin, middle, end);
    }
}


//Programa principal en el que se prueba el algoritmo y se crean los output.txt
int main() {
    //retorna un vector de vectores
    vector< vector<int> > allArrays = readInputSort("../inputSort.txt");

    ofstream outputFile("../outputMergeSort.txt");

    if (!outputFile) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        return 1;
    }

    for (size_t i = 0; i < allArrays.size(); ++i) {
        //Inicio del cronometro
        auto start = chrono::high_resolution_clock::now();
        //Uso de QuickSort.
        int size = allArrays[i].size();
        MergeSort(allArrays[i], 0, size - 1); //MergeSort ordena dentro del mismo vector.
        //Final del cronometro
        auto end = chrono::high_resolution_clock::now();

        //Calcular la diferencia en ms
        float duration = (std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0f);

        //Imprime el arr ordenado en un archivo de texto y el tiempo que demoro con la funcion usada
        printSortingResult(outputFile, i, allArrays[i].size(), duration, "MergeSort");
    }

    return 0;
}


