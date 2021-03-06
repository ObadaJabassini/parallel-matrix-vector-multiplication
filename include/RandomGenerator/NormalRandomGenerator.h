//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_NORMALRANDOMGENERATOR_H
#define PROJECT_NORMALRANDOMGENERATOR_H


#include <memory>
#include "RandomGenerator.h"

namespace Generator {

    class NormalRandomGenerator : public RandomGenerator{
    private:
        shared_ptr<std::normal_distribution<double>> normal_dist;
    public:
        NormalRandomGenerator(double mean = 0, double stddeviation = 1 );

        double generate() override;

        void generate( double*& arr, int elements ) override;

        void generate( double**& mat, int rows, int cols ) override;

    };

}

#endif //PROJECT_NORMALRANDOMGENERATOR_H
