//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_NORMALRANDOMGENERATOR_H
#define PROJECT_NORMALRANDOMGENERATOR_H


#include <bits/unique_ptr.h>
#include "RandomGenerator.h"

template <class T>
class NormalRandomGenerator : public RandomGenerator<T>{
private:
    std::unique_ptr<normal_distribution<T>> normal_dist;
public:
    NormalRandomGenerator(uint32_t seed, float mean, float stddeviation);

    T generate() override;

    void generate(T*& arr, int elements) override;

    void generate(T**& mat, int rows, int cols) override;
};



#endif //PROJECT_NORMALRANDOMGENERATOR_H
