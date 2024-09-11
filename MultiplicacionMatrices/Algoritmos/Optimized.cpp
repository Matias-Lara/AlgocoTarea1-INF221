#include "ahead.h"
#include "Auxiliary.h"

using namespace std;

/*
 * Este archivo contiene código adaptado de:
 * https://pastebin.com/ZE0H0bRr
 * Fuente: https://youtu.be/ChvEYb7UT34
 */


//Funcion para transponer una matriz no cuadrada
vector<vector<int>> transposeMatrix(const vector<vector<int>>& m) {
    int rows = m.size();
    int cols = m[0].size();
    vector<vector<int>> transposed(cols, vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = m[i][j];
        }
    }
    return transposed;
}

//Multiplicacion de matrices optimizada para matrices no cuadradas
void optimized_multiply(vector<vector<int>>& result, 
                      const vector<vector<int>>& a, 
                      const vector<vector<int>>& b) {

    int rowsA = a.size();
    int colsA = a[0].size();
    int rowsB = b.size();
    int colsB = b[0].size();

    //Compatibilidad de dimensiones
    if (colsA != rowsB) {
        cerr << "Error: Las matrices no son dimensionalmente multiplicables. " << endl;
        return;
    } 

    //Transponemos la matriz B para mejorar la localidad de datos
    vector<vector<int>> transposedB = transposeMatrix(b);

    //Asignar tamaño a la matriz resultante y rellenar con 0's
    result.assign(rowsA, vector<int>(colsB, 0));

    // Multiplicación optimizada omitiendo multiplicaciones con 0
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            int sum = 0;
            for (int k = 0; k < colsA; ++k) {
                //optimizacion para no multiplicar por 0
                if (a[i][k] != 0 && transposedB[j][k] != 0) {
                    sum += a[i][k] * transposedB[j][k];  
                }
            }
            result[i][j] = sum;
        }
    }
}


int main() {
    srand(time(0)); //Semilla aleatoria para generateRandomMatrix

    vector<int> sizes = {128, 256, 1024, 2048, 4096}; //Tamanios de las matrices a medir rendimiento

    ofstream outputFile("outputOptimized.csv"); //Archivo de Salida
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
        optimized_multiply(result, matrixA, matrixB);
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
        optimized_multiply(result, matrixA, matrixB);
        auto end = chrono::high_resolution_clock::now();
        float duration = (chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0f);

        outputFile << "Tiempo para matriz (80% de 0's) " << size << "x" << size << ": " << duration << " ms" << endl;
    }

    outputFile.close();

    cout << "Resultados guardados en outputOptimized.csv" << endl;

    return 0;
}