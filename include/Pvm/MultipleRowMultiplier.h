//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_MULTIPLECOLUMNMULTIPLIER_H
#define PROJECT_MULTIPLECOLUMNMULTIPLIER_H


#include "../Serial/MatrixMultiplier.h"

class MultipleRowMultiplier : public MatrixMultiplier{
private:
    int rows;
public:
    MultipleRowMultiplier(const std::string& file_path, int rows = 3);

    void multiply(std::string result_file_path) override;
    std::string  multiply(bool justTime = false) override;
};


#endif //PROJECT_MULTIPLECOLUMNMULTIPLIER_H
