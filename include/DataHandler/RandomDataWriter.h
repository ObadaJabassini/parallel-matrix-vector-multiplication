//
// Created by obada on 5/2/17.
//

#ifndef PROJECT_RANDOMDATAWRITER_H
#define PROJECT_RANDOMDATAWRITER_H

#include <array>
#include <string>
#include <RandomGenerator/RandomGenerator.h>

using namespace std;

template <class T>
class RandomDataWriter {
public:
    void write(string file_path, RandomGenerator<T>* generator, int size = 3);
};


#endif //PROJECT_RANDOMDATAWRITER_H
