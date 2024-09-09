#include "ahead.h"
#include "auxiliary.h"

using namespace std;


/*
 * Este archivo contiene código adaptado de:
 * https://www.geeksforgeeks.org/quick-sort-algorithm/
 */

int partition(vector<int>& arr, int low, int high) {
    //Pivote elemento aleatorio
    int randomIndex = low + rand() % (high - low + 1);
    int pivot = arr[randomIndex];

    //Pivote al final para reutilizar logica de particion ultimo elemento como pivote
    swap(arr[randomIndex], arr[high]);
    
    //Ultimo elemento mas pequenio que el pivote
    int i = low - 1;

    //Invariante: [ElemMenores][ElemMayores/Iguales][SinProcesar][Pivote]
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]); //[ElemMenores][Pivote][ElemMayores]
    return i + 1; //Posicion del Pivote
}


void QuickSort(vector<int>& arr, int low, int high) {
    //Esta condicion permite no seguir diviendo esos arreglos de un solo elemento
    if (low < high) {
        int posPivot = partition(arr, low, high);

        QuickSort(arr, low, posPivot - 1);  //Recursivamente se ordena SubArreglo de [ElemMenores]
        QuickSort(arr, posPivot + 1, high); //Analogo para [ElemMayores]
    }   
}


//Programa principal en el que se prueba el algoritmo y se crean los output.txt
int main() {
    //retorna un vector de vectores
    vector< vector<int> > allArrays = readInputSort("../inputSort.txt");

    ofstream outputFile("../outputQuickSort.txt");

    if (!outputFile) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        return 1;
    }

    for (size_t i = 0; i < allArrays.size(); ++i) {
        //Inicio del cronometro
        auto start = chrono::high_resolution_clock::now();
        //Uso de QuickSort.
        int size = allArrays[i].size();
        QuickSort(allArrays[i], 0, size - 1); //QuickSort ordena dentro del mismo vector.
        //Final del cronometro
        auto end = chrono::high_resolution_clock::now();

        //Calcular la diferencia en ms
        float duration = (std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0f);

        //Imprime el arr ordenado en un archivo de texto y el tiempo que demoro con la funcion usada
        printSortingResult(outputFile, i, allArrays[i].size(), duration, "QuickSort");
    }

    return 0;
}