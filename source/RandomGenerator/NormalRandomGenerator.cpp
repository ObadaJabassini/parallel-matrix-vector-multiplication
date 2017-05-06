
#include <RandomGenerator/NormalRandomGenerator.h>
#include <memory>
#include <random>

template <class T>
NormalRandomGenerator<T>::NormalRandomGenerator(uint32_t seed, float mean, float stddeviation) : RandomGenerator<T>(seed){
    this->normal_dist = new std::normal_distribution<T>(mean, stddeviation);
}

template <class T>
T NormalRandomGenerator<T>::generate() {
    return (*normal_dist)(this->range);
}

template <class T>
void NormalRandomGenerator<T>::generate(T*& arr, int elements) {
    for ( int i = 0; i < elements; ++i ) {
        arr[i] = (*normal_dist)(this->range);
    }
}

template <class T>
void NormalRandomGenerator<T>::generate(T**& mat, int rows, int cols) {
    for ( int i = 0; i < rows; ++i ) {
        for ( int j = 0; j < cols; ++j ) {
            mat[i][j] = (*normal_dist)(this->range);
        }
    }
}

template <class T>
NormalRandomGenerator<T>::~NormalRandomGenerator() {
    delete this->normal_dist;
}
