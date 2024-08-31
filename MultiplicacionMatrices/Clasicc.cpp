#include <iostream>
#include <vector>

void multiplyMatrices(std::vector<std::vector<uint32_t>>& r, 
                      const std::vector<std::vector<uint32_t>>& a, 
                      const std::vector<std::vector<uint32_t>>& b) {

    uint16_t size = a.size(); 

    for(uint16_t i = 0; i < size; ++i) {
        for(uint16_t j = 0; j < size; ++j) {
            uint32_t s = 0;
            for(uint16_t k = 0; k < size; ++k) {
                s += a[i][k] * b[k][j];
            }
            r[i][j] = s;
        }
    }
}