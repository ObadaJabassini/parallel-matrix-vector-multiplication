//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_UNIFORMRANDOMGENERATOR_H
#define PROJECT_UNIFORMRANDOMGENERATOR_H

#include <bits/unique_ptr.h>
#include "RandomGenerator.h"

template <class T>
class UniformRandomGenerator : public RandomGenerator{
private:
    std::unique_ptr<std::uniform_int_distribution<T>> uniform_dist;
public:
    UniformRandomGenerator(uint32_t seed = rand() % 1000, T low, T high);
    UniformRandomGenerator(uint32_t seed = rand() % 1000);

    T generate() override;

    void generate(T*& arr, int size) override;

    void generate(T**& mat, int rows, int cols) override;
};


#endif //PROJECT_UNIFORMRANDOMGENERATOR_H
