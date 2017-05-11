//
// Created by ojabassini on 5/11/17.
//

#ifndef PROJECT_RUBBISHRANDOMGENERATOR_H
#define PROJECT_RUBBISHRANDOMGENERATOR_H

#include <memory>
#include <random>
#include "RandomGenerator.h

namespace Generator {
    class RubbishRandomGenerator : public RandomGenerator {
    public:
        double generate() override;

        void generate( double*& arr, int size ) override;

        void generate( double**& mat, int rows, int cols ) override;
    };
}


#endif //PROJECT_RUBBISHRANDOMGENERATOR_H
