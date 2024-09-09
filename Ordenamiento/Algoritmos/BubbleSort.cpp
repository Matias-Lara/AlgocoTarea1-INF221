#include "ahead.h"
#include "auxiliary.h"

using namespace std;

vector<int> Bubblesort(vector<int> arr) {
    int n = arr.size();
    bool swapped; //Bandera de optimizacion.

    for (size_t i = 0; i < n; i++) {
        //j solo necesita iterar hasta el ultimo elemento que no ha sido colocado en su posición final.
        for (size_t j = 0; j < (n - i - 1) ; j++) {
            //Si el elemento j es mayor que el elemento siguiente, debe "burbujear" oara intercambiar.
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        //Si no se realiazo ningun intercambio, el arreglo ya esta ordenado
        if (!swapped) {
            break;
        }
    }
    return arr;
}


//Programa principal en el que se prueba el algoritmo y se crean los output.txt
int main() {
    //retorna un vector de vectores
    vector< vector<int> > allArrays = readInputSort("../inputSort.txt");

    ofstream outputFile("../outputBubbleSort.txt");

    if (!outputFile) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        return 1;
    }

    for (size_t i = 0; i < allArrays.size(); ++i) {
        //Inicio del cronometro
        auto start = chrono::high_resolution_clock::now();
        
        //Uso de BubbleSort
        int size = allArrays[i].size();
        vector<int> sortedArray = Bubblesort(allArrays[i]);

        //Final del cronometro
        auto end = chrono::high_resolution_clock::now();

        //Calcular la diferencia en ms
        float duration = (std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0f);

        //Imprime el arr ordenado en un archivo de texto y el tiempo que demoro con la funcion usada
        printSortingResult(outputFile, i, allArrays[i].size(), duration, "BubbleSort");
    }

    return 0;
}