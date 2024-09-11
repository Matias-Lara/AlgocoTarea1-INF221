#include "ahead.h"
#include "Auxiliary.h"

using namespace std;


/*
 * Este archivo contiene código adaptado de:
 * Fuente: https://www.geeksforgeeks.org/strassens-matrix-multiplication/
 */

// Función para multiplicación tradicional
vector<vector<int>> traditional_multiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Función para sumar dos matrices
vector<vector<int>> add_matrix(const vector<vector<int>>& matrix_A,
                               const vector<vector<int>>& matrix_B,
                               int split_index, int multiplier = 1) {

    vector<vector<int>> result(split_index, vector<int>(split_index, 0));
    for (int i = 0; i < split_index; i++) {
        for (int j = 0; j < split_index; j++) {
            result[i][j] = matrix_A[i][j] + (multiplier * matrix_B[i][j]);
        }
    }
    return result;
}

// Función para multiplicar matrices usando Strassen
vector<vector<int>> Strassen(const vector<vector<int>>& matrix_A,
                                    const vector<vector<int>>& matrix_B) {
    int col_1 = matrix_A[0].size();
    int row_1 = matrix_A.size();
    int col_2 = matrix_B[0].size();
    int row_2 = matrix_B.size();

    // Verificar si las matrices son multiplicables
    if (col_1 != row_2) {
        cout << "Error: El número de columnas en A debe ser igual al número de filas en B\n";
        return {};
    }

    // Umbral del caso base: usar multiplicación tradicional para matrices pequeñas 16x16
    if (col_1 <= 16) {
        return traditional_multiply(matrix_A, matrix_B);
    }

    int split_index = col_1 / 2;

    vector<int> row_vector(split_index, 0);

    // Dividir matrices en submatrices
    vector<vector<int>> a00(split_index, row_vector);
    vector<vector<int>> a01(split_index, row_vector);
    vector<vector<int>> a10(split_index, row_vector);
    vector<vector<int>> a11(split_index, row_vector);
    vector<vector<int>> b00(split_index, row_vector);
    vector<vector<int>> b01(split_index, row_vector);
    vector<vector<int>> b10(split_index, row_vector);
    vector<vector<int>> b11(split_index, row_vector);

    for (int i = 0; i < split_index; i++) {
        for (int j = 0; j < split_index; j++) {
            a00[i][j] = matrix_A[i][j];
            a01[i][j] = matrix_A[i][j + split_index];
            a10[i][j] = matrix_A[split_index + i][j];
            a11[i][j] = matrix_A[split_index + i][j + split_index];
            b00[i][j] = matrix_B[i][j];
            b01[i][j] = matrix_B[i][j + split_index];
            b10[i][j] = matrix_B[split_index + i][j];
            b11[i][j] = matrix_B[split_index + i][j + split_index];
        }
    }

    // 7 multiplicaciones de Strassen
    vector<vector<int>> p = Strassen(a00, add_matrix(b01, b11, split_index, -1));
    vector<vector<int>> q = Strassen(add_matrix(a00, a01, split_index), b11);
    vector<vector<int>> r = Strassen(add_matrix(a10, a11, split_index), b00);
    vector<vector<int>> s = Strassen(a11, add_matrix(b10, b00, split_index, -1));
    vector<vector<int>> t = Strassen(add_matrix(a00, a11, split_index), add_matrix(b00, b11, split_index));
    vector<vector<int>> u = Strassen(add_matrix(a01, a11, split_index, -1), add_matrix(b10, b11, split_index));
    vector<vector<int>> v = Strassen(add_matrix(a00, a10, split_index, -1), add_matrix(b00, b01, split_index));

    // Combinar los resultados
    vector<vector<int>> result_matrix(row_1, vector<int>(col_2, 0));
    vector<vector<int>> result_matrix_00 = add_matrix(add_matrix(add_matrix(t, s, split_index), u, split_index), q, split_index, -1);
    vector<vector<int>> result_matrix_01 = add_matrix(p, q, split_index);
    vector<vector<int>> result_matrix_10 = add_matrix(r, s, split_index);
    vector<vector<int>> result_matrix_11 = add_matrix(add_matrix(add_matrix(t, p, split_index), r, split_index, -1), v, split_index, -1);

    // Colocar las submatrices en la matriz final
    for (int i = 0; i < split_index; i++) {
        for (int j = 0; j < split_index; j++) {
            result_matrix[i][j] = result_matrix_00[i][j];
            result_matrix[i][j + split_index] = result_matrix_01[i][j];
            result_matrix[split_index + i][j] = result_matrix_10[i][j];
            result_matrix[i + split_index][j + split_index] = result_matrix_11[i][j];
        }
    }

    return result_matrix;
}


int main() {
    srand(time(0)); //Semilla aleatoria para generateRandomMatrix

    vector<int> sizes = {128, 256, 1024, 2048}; //Tamanios de las matrices a medir rendimiento

    ofstream outputFile("outputStrassen.csv"); //Archivo de Salida
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

        auto start = chrono::high_resolution_clock::now();
        vector<vector<int>> result = Strassen(matrixA, matrixB);
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

        auto start = chrono::high_resolution_clock::now();
        vector<vector<int>> result = Strassen(matrixA, matrixB);
        auto end = chrono::high_resolution_clock::now();
        float duration = (chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0f);

        outputFile << "Tiempo para matriz (80% de 0's) " << size << "x" << size << ": " << duration << " ms" << endl;
    }

    outputFile.close();

    cout << "Resultados guardados en outputStrassen.csv" << endl;
    


    return 0;
}

