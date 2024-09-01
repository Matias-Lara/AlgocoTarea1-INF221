#include <iostream>
#include <vector>

/*
 * Este archivo contiene código adaptado de:
 * https://pastebin.com/9TNNbwGk
 * Fuente: https://youtu.be/ChvEYb7UT34
 */


// Función para transponer una matriz
void transposeMatrix(std::vector<std::vector<uint32_t>>& m) {
    uint16_t size = m.size(); // Suponemos que la matriz es cuadrada

    for(uint16_t i = 0; i < size; ++i) {
        for(uint16_t j = i; j < size; ++j) {
            uint32_t t = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = t;
        }
    }
}

///
/// r = a*b (Matrices)
///  -> La función transpondrá internamente la matriz B para optimizar la localidad de datos.
///
void multiplyMatrices(std::vector<std::vector<uint32_t>>& r, 
                      const std::vector<std::vector<uint32_t>>& a, 
                      std::vector<std::vector<uint32_t>> b) { // b no es const porque se va a transponer dentro de la función

    uint16_t size = a.size(); // Asumimos que las matrices son cuadradas

    // Transponemos la matriz B para mejorar la localidad de datos
    transposeMatrix(b);

    for(uint16_t i = 0; i < size; ++i) {
        for(uint16_t j = 0; j < size; ++j) {
            uint32_t s = 0;
            for(uint16_t k = 0; k < size; ++k) {
                s += a[i][k] * b[j][k]; // Nota: ahora b[j][k] debido a la transposición
            }
            r[i][j] = s;
        }
    }
}