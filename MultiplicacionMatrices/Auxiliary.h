//Archivo Fuente
#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "ahead.h"

using namespace std;
//Declaracion de funciones auxiliares

//Funcion para generar una matriz aleatoria de tamaño AxB
vector<vector<int>> generateRandomMatrix(int A, int B);
//Funcion para generar una matriz aleatoria de tamaño AxB con un porcentaje de ceros
vector<vector<int>> generateMatrixWithRepeatedZeros(int A, int B, float percentage);

#endif 