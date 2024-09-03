//Archivo Fuente
#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "ahead.h"

//Declaracion de Funciones auxiliares
std::vector<int> generate_arr(size_t n);

std::string printArray(const std::vector<int>& arr);

std::vector<std::vector<int>> readInputSort(const std::string& filename);

#endif 

