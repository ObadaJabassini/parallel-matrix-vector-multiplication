//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_UNIFORMRANDOMGENERATOR_H
#define PROJECT_UNIFORMRANDOMGENERATOR_H

#include <memory>
#include <random>
#include "RandomGenerator.h"

namespace Generator {
    class UniformRandomGenerator : public RandomGenerator{
    private:
        std::shared_ptr<std::uniform_real_distribution<double>> uniform_dist;
    public:
        UniformRandomGenerator( uint32_t seed = ( uint32_t ) (rand() % 1000), double low = 0, double high = 1);

        double generate() override;

        void generate( double*& arr, int size ) override;

        void generate( double**& mat, int rows, int cols ) override;
    };
}
#endif //PROJECT_UNIFORMRANDOMGENERATOR_H
