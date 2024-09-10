#include "ahead.h"
#include "Auxiliary.h"

using namespace std;

vector<vector<int>> generateRandomMatrix(int A, int B) {
    vector<vector<int>> matrix(A, vector<int>(B));

    for (int i = 0; i < A; ++i) {
        for (int j = 0; j < B; ++j) {
            matrix[i][j] = rand() % 10;  //Generar numeros aleatorios entre 0 y 9
        }
    }

    return matrix;
}


vector<vector<int>> generateMatrixWithRepeatedZeros(int A, int B, float percentage) {
    vector<vector<int>> matrix(A, vector<int>(B));
    int totalElements = A * B;
    int repeatedCount = static_cast<int>(totalElements * percentage);  //Numero de elementos repetidos
    int uniqueCount = totalElements - repeatedCount;  //Numero de elementos unicos


    // Llenar la matriz con valores aleatorios
    for (int i = 0; i < A; ++i) {
        for (int j = 0; j < B; ++j) {
            if (repeatedCount > 0) {
                matrix[i][j] = 0; //Se rellena con 0
                repeatedCount--;
            } else {
                matrix[i][j] = rand() % 100 + 1;  //Generar un valor aleatorio único
            }
        }
    }

    //Mezclar matriz para que no queden agrupados los 0
    random_device rd;
    mt19937 g(rd());
    for (int i = 0; i < A; ++i) {
        shuffle(matrix[i].begin(), matrix[i].end(), g); 
    }

    return matrix;
}