#include <RandomGenerator/RubbishRandomGenerator.h>

namespace Generator {

    double RubbishRandomGenerator::generate() {
        return rand();
    }

    void RubbishRandomGenerator::generate( double*& arr, int elements ) {
        for ( int i = 0; i < elements; ++i ) {
            arr[i] = rand();
        }
    }

    void RubbishRandomGenerator::generate( double**& mat, int rows, int cols ) {
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                mat[i][j] = rand();
            }
        }
    }
}
