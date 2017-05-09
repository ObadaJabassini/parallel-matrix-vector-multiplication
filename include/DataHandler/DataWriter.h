//
// Created by ojabassini on 5/9/17.
//

#ifndef PROJECT_DATAWRITER_H
#define PROJECT_DATAWRITER_H

#include <fstream>
using namespace std;

namespace DataHandler {
    class DataWriter{
    public:
        virtual void write(string filePath, double** matrix, double* vector, int size) = 0;
    };
}

#endif //PROJECT_DATAWRITER_H
