
#include "UniformRandomGenerator.h"

template <class T>
UniformRandomGenerator::UniformRandomGenerator(uint32_t seed, T low, T high): RandomGenerator(seed) {
    uniform_dist = std::make_unique<std::uniform_int_distribution<T>>(low, high);
}

template <class T>
UniformRandomGenerator::UniformRandomGenerator(uint32_t seed) : RandomGenerator(seed) {
    uniform_dist = std::make_unique<std::uniform_int_distribution<T>>();
}

template <class T>
T UniformRandomGenerator::generate() {
    return (*uniform_dist)(range);
}

template <class T>
void UniformRandomGenerator::generate(T*& arr, int size) {
    for ( int i = 0; i < size; ++i ) {
        arr[i] = (*uniform_dist)(range);
    }
}

template <class T>
void UniformRandomGenerator::generate(T**& mat, int rows, int cols) {
    for ( int i = 0; i < rows; ++i ) {
        for ( int j = 0; j < cols; ++j ) {
            mat[i][j] = (*uniform_dist)(range);
        }
    }
}
