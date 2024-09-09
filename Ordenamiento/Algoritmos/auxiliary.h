//Archivo Fuente
#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "ahead.h"

using namespace std;

//Declaracion de Funciones auxiliares
vector<int> generate_arr(size_t n);

string printArray(const vector<int>& arr);

vector<vector<int>> readInputSort(const string& filename);

vector<int> LineToVector(const string& line);

void printSortingResult(ofstream& outputFile, int i, int size, float duration, const string& algorithmName);

#endif 

