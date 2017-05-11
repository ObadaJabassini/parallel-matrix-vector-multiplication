
#include <RandomGenerator/NormalRandomGenerator.h>
#include <memory>
#include <random>

namespace Generator {

    NormalRandomGenerator::NormalRandomGenerator( double mean, double stddeviation ) {
        this->normal_dist = make_shared<std::normal_distribution<double>>( mean, stddeviation );
    }

    double NormalRandomGenerator::generate() {
        return (*normal_dist)( this->range );
    }

    void NormalRandomGenerator::generate( double*& arr, int elements ) {
        for ( int i = 0; i < elements; ++i ) {
            arr[i] = (*normal_dist)( this->range );
        }
    }

    void NormalRandomGenerator::generate( double**& mat, int rows, int cols ) {
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                mat[i][j] = (*normal_dist)( this->range );
            }
        }
    }
}