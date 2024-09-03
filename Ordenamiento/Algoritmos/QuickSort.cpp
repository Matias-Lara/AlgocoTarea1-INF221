#include "ahead.h"
#include "auxiliary.h"

using namespace std;


/*
 * Este archivo contiene código adaptado de:
 * https://www.geeksforgeeks.org/quick-sort-algorithm/
 */

int partition(vector<int>& arr, int low, int high) {
    //Indice del elemento central
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];  //Se escoge como pivote el elemento centrla

    //Se mueve el pivote al final para reutilizar la misma logica de particion que funciona con el ultimo elemento como pivote
    swap(arr[mid], arr[high]);
    
    //Indice del ultimo elemento mas pequenio que el pivote
    int i = low - 1;

    //Este bucle asegura la invariante: [ElemMenores][ElemMayores/Iguales][SinProcesar][Pivote]
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]); //Se coloca el pivote en su posicion final [ElemMenores][Pivote][ElemMayores]
    return i + 1; //Retorna posicion del pivote
}


void QuickSort(vector<int>& arr, int low, int high) {
    
    //low va a crecer en caso de los ElemMenores y hight va a decrecer en el caso de los ElemMayores
    //Por lo que en algun momento se va a llamar a QuickSort con arreglos 1 elemento
    //Esta condicion permite no seguir diviendo esos arreglos de un solo elemento
    if (low < high) {
        int posPivot = partition(arr, low, high);

        QuickSort(arr, low, posPivot - 1);  //Recursivamente se ordena SubArreglo de [ElemMenores]
        QuickSort(arr, posPivot + 1, high); //Analogo para [ElemMayores]
    }   
}



int main() {
    //retorna un vector de vectores
    vector< vector<int> > allArrays = readInputSort("inputSort.txt");

    ofstream outputFile("../outputQuickSort.txt");

    if (!outputFile) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        return 1;
    }

    for (size_t i = 0; i < allArrays.size(); ++i) {
        //Inicio del cronometro
        auto start = chrono::high_resolution_clock::now();
        //Uso de MergeSort.
        int size = allArrays[i].size();
        QuickSort(allArrays[i], 0, size - 1); //QuickSort ordena dentro del mismo vector.
        //Final del cronometro
        auto end = chrono::high_resolution_clock::now();

        //Calcular la diferencia en ms
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        //Imprime el arr ordenado en un archivo de texto y el tiempo que demoro con la funcion usada
        if (i+1 <= 6) {
            if (i+1 == 1){
                outputFile << "Arreglos Aleatorios: " << endl;
            }
            outputFile << "Vector " << i + 1 << ": ";
            outputFile << "El arreglo de tamanio: " << pow(10, i + 1) << " tardo " << duration << " ms" << " en ordenarse con QuickSort" << endl;
            outputFile << endl;
        } else if (i+1 <= 12) {
            if (i+1 == 7){
                outputFile << "Arreglos Ordenados: " << endl;
            }
            outputFile << "Vector " << i - 5 << ": ";
            outputFile << "El arreglo de tamanio: " << pow(10, i - 5) << " tardo " << duration << " ms" << " en ordenarse con QuickSort" << endl;
            outputFile << endl;
        }
    }

    return 0;
}