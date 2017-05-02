
#include "../../include/RandomGenerator/UniformRandomGenerator.h"

template <class T>
UniformRandomGenerator<T>::UniformRandomGenerator(uint32_t seed, T low, T high): RandomGenerator<T>(seed) {
    uniform_dist = std::make_shared<std::uniform_int_distribution<T>>(low, high);
}

template <class T>
UniformRandomGenerator<T>::UniformRandomGenerator(uint32_t seed) : RandomGenerator<T>(seed) {
    uniform_dist = std::make_unique<std::uniform_int_distribution<T>>();
}

template <class T>
T UniformRandomGenerator<T>::generate() {
    return (*uniform_dist)(this->range);
}

template <class T>
void UniformRandomGenerator<T>::generate(T*& arr, int size) {
    for ( int i = 0; i < size; ++i ) {
        arr[i] = (*uniform_dist)(this->range);
    }
}

template <class T>
void UniformRandomGenerator<T>::generate(T**& mat, int rows, int cols) {
    for ( int i = 0; i < rows; ++i ) {
        for ( int j = 0; j < cols; ++j ) {
            mat[i][j] = (*uniform_dist)(this->range);
        }
    }
}
