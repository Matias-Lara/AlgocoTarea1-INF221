#include "ahead.h"
#include "Auxiliary.h"

using namespace std;

/*
 * Este archivo contiene código adaptado de:
 * https://pastebin.com/ZE0H0bRr
 * Fuente: https://youtu.be/ChvEYb7UT34
 */


//Multiplicacion Estandar
void multiplyMatrices(vector<vector<int>>& result, const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int rowsA = a.size();
    int colsA = a[0].size();
    int colsB = b[0].size();

    result.assign(rowsA, vector<int>(colsB, 0)); //Se rellena con 0 la matriz resultado

    //Iterar por cada fila de la matriz A (O(n))
    for (int i = 0; i < rowsA; ++i) {
        //Iterar por cada columna del la matriz B (O(n))
        for (int j = 0; j < colsB; ++j) {
            int sum = 0; //Se reinicia la var sum

            //Sumatoria de cada elemento de la fila de A por cada elemento de la columna de B
            for (int k = 0; k < colsA; ++k) {

                //Optimizacion para no multiplicar por 0
                if (a[i][k] == 0 || b[k][j] == 0) {
                    continue; 
                }
                
                sum += a[i][k] * b[k][j];
            }
            //Se agrega a la matriz resultado
            result[i][j] = sum;
        }
    }
}

int main() {
    srand(time(0)); //Semilla aleatoria para generateRandomMatrix

    vector<int> sizes = {128, 256, 1024, 2048, 4096}; //Tamanios de las matrices a probar

    ofstream outputFile("outputClassic.csv"); //Archivo de Salida
    if (!outputFile.is_open()) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return 1;
    }

    //Multiplicacion de matrices cuadradas
    outputFile << "Tiempos de ejecucion (ms) de matrices de iguales dimensiones:" << endl;
    for (int i = 0; i < sizes.size(); i++) {
        int size = sizes[i];
        vector<vector<int>> matrixA = generateRandomMatrix(size, size);
        vector<vector<int>> matrixB = generateRandomMatrix(size, size);
        vector<vector<int>> result;

        auto start = chrono::high_resolution_clock::now();
        multiplyMatrices(result, matrixA, matrixB);
        auto end = chrono::high_resolution_clock::now();
        float duration = (chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0f);

        outputFile << "Tiempo para matriz " << size << "x" << size << ": " << duration << " ms" << endl;
    }

    //Multiplicacion de matrices cuadradas con 80% de 0's
    outputFile << "Tiempos de ejecucion (ms) de matrices cuadradas con 80% de ceros" << endl;
    //Se usara el mismo vector sizes ocupado anteriormente
    for (int i = 0; i < sizes.size(); i++) {
        int size = sizes[i];
        vector<vector<int>> matrixA = generateMatrixWithRepeatedZeros(size, size, 0.8);
        vector<vector<int>> matrixB = generateMatrixWithRepeatedZeros(size, size, 0.8);

        vector<vector<int>> result;

        auto start = chrono::high_resolution_clock::now();
        multiplyMatrices(result, matrixA, matrixB);
        auto end = chrono::high_resolution_clock::now();
        float duration = (chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0f);

        outputFile << "Tiempo para matriz (80% de 0's) " << size << "x" << size << ": " << duration << " ms" << endl;
    }

    outputFile.close();

    cout << "Resultados guardados en outputClassic.csv" << endl;

    return 0;
}