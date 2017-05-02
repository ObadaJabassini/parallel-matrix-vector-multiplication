//

#ifndef PROJECT_RANDOMDATAGENERATOR_H
#define PROJECT_RANDOMDATAGENERATOR_H


#include <random>

using namespace std;

template <class T>
class RandomGenerator {
protected:
    mt19937 range;
public:
    RandomGenerator(uint32_t seed = rand() % 1000);
    virtual T generate() = 0;
    virtual void generate(T*& arr, int size) = 0;
    virtual void generate(T**& mat, int rows, int cols) = 0;
};


#endif //PROJECT_RANDOMDATAGENERATOR_H
