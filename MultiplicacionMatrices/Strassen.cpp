#include "ahead.h"
#include "Auxiliary.h"

using namespace std;


/*
 * Este archivo contiene código adaptado de:
 * ChatGPT
 * Prompt: Explicame por que este codigo *CodigoEncontradoEnGeeksforGeeks* no es un strassen, y que modificaciones le hacen falta para serlo.
 * Fuente: https://www.geeksforgeeks.org/strassens-matrix-multiplication/
 */

void add_matrix(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract_matrix(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            C[i][j] = A[i][j] - B[i][j];
}

vector<vector<int>> strassen_multiply(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();

    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int new_size = n / 2;
    vector<vector<int>> a11(new_size, vector<int>(new_size));
    vector<vector<int>> a12(new_size, vector<int>(new_size));
    vector<vector<int>> a21(new_size, vector<int>(new_size));
    vector<vector<int>> a22(new_size, vector<int>(new_size));

    vector<vector<int>> b11(new_size, vector<int>(new_size));
    vector<vector<int>> b12(new_size, vector<int>(new_size));
    vector<vector<int>> b21(new_size, vector<int>(new_size));
    vector<vector<int>> b22(new_size, vector<int>(new_size));

    // Dividiendo las matrices en 4 submatrices
    for (int i = 0; i < new_size; ++i) {
        for (int j = 0; j < new_size; ++j) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + new_size];
            a21[i][j] = A[i + new_size][j];
            a22[i][j] = A[i + new_size][j + new_size];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + new_size];
            b21[i][j] = B[i + new_size][j];
            b22[i][j] = B[i + new_size][j + new_size];
        }
    }

    // Calculando las 7 multiplicaciones de Strassen
    vector<vector<int>> M1(new_size, vector<int>(new_size));
    vector<vector<int>> M2(new_size, vector<int>(new_size));
    vector<vector<int>> M3(new_size, vector<int>(new_size));
    vector<vector<int>> M4(new_size, vector<int>(new_size));
    vector<vector<int>> M5(new_size, vector<int>(new_size));
    vector<vector<int>> M6(new_size, vector<int>(new_size));
    vector<vector<int>> M7(new_size, vector<int>(new_size));

    vector<vector<int>> A_result(new_size, vector<int>(new_size));
    vector<vector<int>> B_result(new_size, vector<int>(new_size));

    add_matrix(a11, a22, A_result, new_size);
    add_matrix(b11, b22, B_result, new_size);
    M1 = strassen_multiply(A_result, B_result);

    add_matrix(a21, a22, A_result, new_size);
    M2 = strassen_multiply(A_result, b11);

    subtract_matrix(b12, b22, B_result, new_size);
    M3 = strassen_multiply(a11, B_result);

    subtract_matrix(b21, b11, B_result, new_size);
    M4 = strassen_multiply(a22, B_result);

    add_matrix(a11, a12, A_result, new_size);
    M5 = strassen_multiply(A_result, b22);

    subtract_matrix(a21, a11, A_result, new_size);
    add_matrix(b11, b12, B_result, new_size);
    M6 = strassen_multiply(A_result, B_result);

    subtract_matrix(a12, a22, A_result, new_size);
    add_matrix(b21, b22, B_result, new_size);
    M7 = strassen_multiply(A_result, B_result);

    // Combinando los resultados en la matriz final C
    vector<vector<int>> C(n, vector<int>(n));

    vector<vector<int>> C11(new_size, vector<int>(new_size));
    vector<vector<int>> C12(new_size, vector<int>(new_size));
    vector<vector<int>> C21(new_size, vector<int>(new_size));
    vector<vector<int>> C22(new_size, vector<int>(new_size));

    add_matrix(M1, M4, A_result, new_size);
    subtract_matrix(A_result, M5, B_result, new_size);
    add_matrix(B_result, M7, C11, new_size);

    add_matrix(M3, M5, C12, new_size);

    add_matrix(M2, M4, C21, new_size);

    add_matrix(M1, M3, A_result, new_size);
    subtract_matrix(A_result, M2, B_result, new_size);
    add_matrix(B_result, M6, C22, new_size);

    // Combinando las submatrices en la matriz C
    for (int i = 0; i < new_size; ++i) {
        for (int j = 0; j < new_size; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + new_size] = C12[i][j];
            C[i + new_size][j] = C21[i][j];
            C[i + new_size][j + new_size] = C22[i][j];
        }
    }

    return C;
}

int main(){
    return 0;
}

