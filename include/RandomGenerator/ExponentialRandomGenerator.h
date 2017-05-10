//
// Created by ojabassini on 5/10/17.
//

#ifndef PROJECT_RUBBISHRANDOMGENERATOR_H
#define PROJECT_RUBBISHRANDOMGENERATOR_H

#include <memory>
#include "RandomGenerator.h"

using namespace std;

namespace Generator {
    class ExponentialRandomGenerator : public RandomGenerator {
    private:
        shared_ptr<std::exponential_distribution<double>> dist;
    public:
        ExponentialRandomGenerator( uint32_t seed = ( uint32_t ) (rand() % 1000), double lambda = 30 );

        double generate() override;

        void generate( double*& arr, int elements ) override;

        void generate( double**& mat, int rows, int cols ) override;
    };
}

#endif //PROJECT_RUBBISHRANDOMGENERATOR_H
