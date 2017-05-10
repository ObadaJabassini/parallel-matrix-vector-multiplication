#include <RandomGenerator/ExponentialRandomGenerator.h>

using namespace std;

namespace Generator{

    ExponentialRandomGenerator::ExponentialRandomGenerator( uint32_t seed, double lambda ) : RandomGenerator(seed) {
        dist = make_shared<exponential_distribution>(lambda);
    }

    double ExponentialRandomGenerator::generate() {
        return (*dist)( this->range );
    }

    void ExponentialRandomGenerator::generate( double*& arr, int elements ) {
        for ( int i = 0; i < elements; ++i ) {
            arr[i] = (*dist)( this->range );
        }
    }

    void ExponentialRandomGenerator::generate( double**& mat, int rows, int cols ) {
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                mat[i][j] = (*dist)( this->range );
            }
        }
    }

}