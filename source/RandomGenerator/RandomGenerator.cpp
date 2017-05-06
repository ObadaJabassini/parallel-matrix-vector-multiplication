//
// Created by obada on 5/1/17.
//

#include <RandomGenerator/RandomGenerator.h>

template <class T>
RandomGenerator<T>::RandomGenerator(uint32_t seed) {
    range.seed(seed);
}
