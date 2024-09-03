#include "ahead.h"
#include "auxiliary.h"

using namespace std;

vector<int> Bubblesort(vector<int> arr) {
    int n = arr.size();
    for (size_t i = 0; i < n; i++) {
        //j solo necesita iterar hasta el ultimo elemento que no ha sido colocado en su posición final.
        for (size_t j = 0; j < (n - i - 1) ; j++) {
            //Si el elemento j es mayor que el elemento que le sigue, debe "burbujear" para subir a la siguiente posicion.
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
    return arr;
}


int main() {

    //retorna un vector de vectores
    vector< vector<int> > allArrays = readInputSort("inputSort.txt");

    ofstream outputFile("outputBubbleSort.txt");

    if (!outputFile) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        return 1;
    }

    for (size_t i = 0; i < allArrays.size(); ++i) {

        //Inicio del cronometro
        auto start = chrono::high_resolution_clock::now();
        //Uso de BubbleSort
        vector<int> sortedArray = Bubblesort(allArrays[i]);
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
            outputFile << "El arreglo de tamanio: " << pow(10, i + 1) << " tardo " << duration << " ms" << " en ordenarse con BubbleSort" << endl;
            outputFile << endl;
        } else if (i+1 <= 12) {
            if (i+1 == 7){
                outputFile << "Arreglos Ordenados: " << endl;
            }
            outputFile << "Vector " << i - 5 << ": ";
            outputFile << "El arreglo de tamanio: " << pow(10, i - 5) << " tardo " << duration << " ms" << " en ordenarse con BubbleSort" << endl;
            outputFile << endl;
        }
    }

    return 0;
}