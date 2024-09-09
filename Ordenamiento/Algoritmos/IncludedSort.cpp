#include "ahead.h"
#include "auxiliary.h"

using namespace std;


//Programa principal en el que se prueba el algoritmo y se crean los output.txt
int main() {
    //retorna un vector de vectores
    vector< vector<int> > allArrays = readInputSort("../inputSort.txt");

    ofstream outputFile("../outputIncludedSort.txt");

    if (!outputFile) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        return 1;
    }

    for (size_t i = 0; i < allArrays.size(); ++i) {
        //Inicio del cronometro
        auto start = chrono::high_resolution_clock::now();
        //Uso de QuickSort.
        int size = allArrays[i].size();
        sort(allArrays[i].begin(), allArrays[i].end()); //Sort ordena dentro del mismo vector.
        //Final del cronometro
        auto end = chrono::high_resolution_clock::now();

        //Calcular la diferencia en ms
        float duration = (std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0f);

        //Imprime el arr ordenado en un archivo de texto y el tiempo que demoro con la funcion usada
        printSortingResult(outputFile, i, allArrays[i].size(), duration, "Included Sort");
    }

    return 0;
}