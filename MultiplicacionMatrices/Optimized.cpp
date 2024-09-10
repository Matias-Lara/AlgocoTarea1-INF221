#include "ahead.h"
#include "auxiliary.h"

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
void multiplyMatrices(vector<vector<int>>& result, 
                      const vector<vector<int>>& a, 
                      const vector<vector<int>>& b) {

    int rowsA = a.size();
    int colsA = a[0].size();  // Número de columnas de A = Número de filas de B
    int colsB = b[0].size();  // Número de columnas de B

    // Transponemos la matriz B para mejorar la localidad de datos
    vector<vector<int>> transposedB = transposeMatrix(b);

    // Asignar tamaño a la matriz resultante
    result.assign(rowsA, vector<int>(colsB, 0));

    // Multiplicación optimizada omitiendo multiplicaciones con 0
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            int sum = 0;
            for (int k = 0; k < colsA; ++k) {
                if (a[i][k] != 0 && transposedB[j][k] != 0) {
                    sum += a[i][k] * transposedB[j][k];  // Producto sólo si ambos elementos son distintos de 0
                }
            }
            result[i][j] = sum;
        }
    }
}