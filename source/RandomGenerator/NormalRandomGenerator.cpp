
#include "../../include/RandomGenerator/NormalRandomGenerator.h"

NormalRandomGenerator::NormalRandomGenerator(uint32_t seed = rand() % 1000, float mean, float stddeviation) : RandomGenerator(seed){
    normal_dist = std::make_unique<std::normal_distribution>(mean, stddeviation);
}

template <class T>
T NormalRandomGenerator::generate() {
    return (*normal_dist)(range);
}

template <class T>
void NormalRandomGenerator::generate(T*& arr, int elements) {
    for ( int i = 0; i < elements; ++i ) {
        arr[i] = (*normal_dist)(range);
    }
}

template <class T>
void NormalRandomGenerator::generate(T**& mat, int rows, int cols) {
    for ( int i = 0; i < rows; ++i ) {
        for ( int j = 0; j < cols; ++j ) {
            mat[i][j] = (*normal_dist)(range);
        }
    }
}
