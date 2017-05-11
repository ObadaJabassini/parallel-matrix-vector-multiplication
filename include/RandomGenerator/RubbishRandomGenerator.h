//
// Created by ojabassini on 5/11/17.
//

#ifndef PROJECT_RUBBISH_H
#define PROJECT_RUBBISH_H

#include "RandomGenerator.h"

namespace Generator{
 class RubbishRandomGenerator : public RandomGenerator{
    public:
       double generate() override;

       void generate( double*& arr, int size ) override;

       void generate( double**& mat, int rows, int cols ) override;
 };
}

#endif //PROJECT_RUBBISH_H
