
#include <RandomGenerator/UniformRandomGenerator.h>

namespace Generator {
    UniformRandomGenerator::UniformRandomGenerator( uint32_t seed, double low, double high ): RandomGenerator( seed ) {
        uniform_dist = std::make_shared<std::uniform_real_distribution<double>>( low, high );
    }

    double UniformRandomGenerator::generate() {
        return (*uniform_dist)( this->range );
    }

    void UniformRandomGenerator::generate( double*& arr, int size ) {
        for ( int i = 0; i < size; ++i ) {
            arr[i] = (*uniform_dist)( this->range );
        }
    }

    void UniformRandomGenerator::generate( double**& mat, int rows, int cols ) {
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                mat[i][j] = (*uniform_dist)( this->range );
            }
        }
    }
}