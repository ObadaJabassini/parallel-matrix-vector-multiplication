//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_SERIALMATRIXMULTIPLIER_H
#define PROJECT_SERIALMATRIXMULTIPLIER_H


#include "MatrixMultiplier.h"
#include <string>

class SerialMatrixMultiplier : public MatrixMultiplier{
public:
    SerialMatrixMultiplier(std::string file_path);

    void multiply(std::string result_file_path) override;
};


#endif //PROJECT_SERIALMATRIXMULTIPLIER_H
