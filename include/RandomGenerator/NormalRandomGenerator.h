//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_NORMALRANDOMGENERATOR_H
#define PROJECT_NORMALRANDOMGENERATOR_H


#include <memory>
#include "RandomGenerator.h"

template <class T>
class NormalRandomGenerator : public RandomGenerator<T>{
private:
    normal_distribution<T>* normal_dist;
public:
    NormalRandomGenerator(uint32_t seed, float mean = 1, float stddeviation = 0);

    T generate() override;

    void generate(T*& arr, int elements) override;

    void generate(T**& mat, int rows, int cols) override;
    ~NormalRandomGenerator();
};



#endif //PROJECT_NORMALRANDOMGENERATOR_H
