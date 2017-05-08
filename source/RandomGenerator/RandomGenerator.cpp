//
// Created by obada on 5/1/17.
//

#include <RandomGenerator/RandomGenerator.h>

namespace Generator {

    RandomGenerator::RandomGenerator( uint32_t seed ) {
        range.seed( seed );
    }
}