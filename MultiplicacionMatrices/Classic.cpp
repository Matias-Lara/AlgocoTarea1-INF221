#include <iostream>
#include <vector>

/*
 * Este archivo contiene código adaptado de:
 * https://pastebin.com/ZE0H0bRr
 * Fuente: https://youtu.be/ChvEYb7UT34
 */


void multiplyMatrices(std::vector<std::vector<uint32_t>>& result, 
                      const std::vector<std::vector<uint32_t>>& a, 
                      const std::vector<std::vector<uint32_t>>& b) {

    uint16_t rowsA = a.size(); //Filas de la matriz a
    uint16_t colsA = a[0].size(); //Columnas de la matriz a
    uint16_t rowsB = b.size(); //Filas de la matriz b
    uint16_t colsB = b[0].size(); //Columnas de la matriz b

    //Verificacion de dim de las matrices
    if (colsA != rowsB) {
        std::cerr << "Error dimensional" << std::endl;
        return;
    }

    //Matriz resultado con ceros
    result.assign(rowsA, std::vector<uint32_t>(colsB, 0));

    //Multiplicacion de matrices
    for (uint16_t i = 0; i < rowsA; ++i) {
        for (uint16_t j = 0; j < colsB; ++j) {
            uint32_t s = 0;
            for (uint16_t k = 0; k < colsA; ++k) {
                s += a[i][k] * b[k][j];
            }
            result[i][j] = s;
        }
    }
}


int main() {
    // Matriz A (2x3)
    std::vector<std::vector<uint32_t>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // Matriz B (3x2)
    std::vector<std::vector<uint32_t>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    // Matriz para almacenar el resultado de la multiplicación (2x2)
    std::vector<std::vector<uint32_t>> result;

    // Llamamos a la función de multiplicación
    multiplyMatrices(result, A, B);

    //
    std::cout << "Matriz resultante: " << std::endl;
    for (size_t i = 0; i < result.size(); ++i) {
        for (size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}