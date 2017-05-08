//

#ifndef PROJECT_RANDOMDATAGENERATOR_H
#define PROJECT_RANDOMDATAGENERATOR_H


#include <random>

using namespace std;

namespace Generator {
    class RandomGenerator {
    protected:
        mt19937 range;
    public:
        RandomGenerator( uint32_t seed = ( uint32_t ) (rand() % 1000));

        virtual double generate() = 0;

        virtual void generate( double*& arr, int size ) = 0;

        virtual void generate( double**& mat, int rows, int cols ) = 0;
    };
}
#endif //PROJECT_RANDOMDATAGENERATOR_H
