#include "ahead.h"
#include "auxiliary.h"

using namespace std;

//Genera un arr de n enteros aleatorios
vector<int> generate_arr(size_t n) {
    vector<int> arr(n);
    
    //Biblioteca <random>
    random_device rd;  //Semilla
    mt19937 gen(rd()); //Generador Mersenne Twister
    uniform_int_distribution<> dis(1, 100); //Distribución uniforme
    
    for(size_t i = 0; i < n; ++i) {
        arr[i] = dis(gen); 
    }
    
    return arr;
}

//Devuelve un string que representa el array
string printArray(const vector<int>& arr) {
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        ss << arr[i];
        if (i < arr.size() - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

//Transforma una linea string a un vector
vector<int> LineToVector(const string& line) {
    vector<int> result;
    string cleanedLine = line;

    //Eliminar corchetes
    cleanedLine.erase(remove(cleanedLine.begin(), cleanedLine.end(), '['), cleanedLine.end());
    cleanedLine.erase(remove(cleanedLine.begin(), cleanedLine.end(), ']'), cleanedLine.end());

    //Usar stringstream para separar por comas y convertir a enteros
    stringstream ss(cleanedLine);
    string item;
    while (getline(ss, item, ',')) {
        result.push_back(stoi(item));
    }

    return result;
}

//Lee el input txt que se le va a entregar a los algoritmos de ordenamiento
vector<vector<int>> readInputSort(const string& filename) {
    ifstream inputFile(filename); //Accede a "inputSort.txt" desde "Algoritmos"
    string line;
    vector<vector<int>> allArrays;

    if (!inputFile) {
        cerr << "Error al abrir el archivo." << endl;
        return allArrays; //Retorna un vector vacío en caso de error
    }

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            vector<int> array = LineToVector(line);
            allArrays.push_back(array);
        }
    }

    inputFile.close();

    return allArrays;
}

// Esta función imprime la información del arreglo ordenado en el archivo de salida
void printSortingResult(std::ofstream& outputFile, int i, int size, float duration, const std::string& algorithmName) {
    
    // Establecemos la precisión de los números flotantes
    outputFile << std::fixed << std::setprecision(3);
    
    if (i + 1 <= 6) {
        if (i + 1 == 1) {
            outputFile << "Arreglos Aleatorios: " << std::endl;
        }
        outputFile << "Vector " << i + 1 << ": ";
        outputFile << "El arreglo de tamanio: " << pow(10, i + 1) << " tardo " << duration << " ms" 
                   << " en ordenarse con " << algorithmName << std::endl;
        outputFile << std::endl;
    } 
    else if (i + 1 <= 12) {
        if (i + 1 == 7) {
            outputFile << "Arreglos Ordenados de menor a mayor: " << std::endl;
        }
        outputFile << "Vector " << i - 5 << ": ";
        outputFile << "El arreglo de tamanio: " << pow(10, i - 5) << " tardo " << duration << " ms" 
                   << " en ordenarse con " << algorithmName << std::endl;
        outputFile << std::endl;
    } 
    else if (i + 1 <= 18) {
        if (i + 1 == 13) {
            outputFile << "Arreglos en forma de montania: " << std::endl;
        }
        outputFile << "Vector " << i - 11 << ": ";
        outputFile << "El arreglo de tamanio: " << pow(10, i - 11) << " tardo " << duration << " ms" 
                   << " en ordenarse con " << algorithmName << std::endl;
        outputFile << std::endl;
    } 
    else {
        if (i + 1 == 19) {
            outputFile << "Arreglos con muchos valores repetidos: " << std::endl;
        }
        outputFile << "Vector " << i - 17 << ": ";
        outputFile << "El arreglo de tamanio: " << pow(10, i - 17) << " tardo " << duration << " ms" 
                   << " en ordenarse con " << algorithmName << std::endl;
        outputFile << std::endl;
    }
}