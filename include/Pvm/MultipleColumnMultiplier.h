//
// Created by ojabassini on 5/7/17.
//

#ifndef PROJECT_MULTIPLECOLUMNMULTIPLIER_H
#define PROJECT_MULTIPLECOLUMNMULTIPLIER_H

#include <Serial/MatrixMultiplier.h>

class MultipleColumnMultiplier : public MatrixMultiplier{
private:
    int cols;
public:
    MultipleColumnMultiplier(std::string file_path, int cols);
    void multiply(std::string result_file_path) override;
    std::string  multiply(bool justTime = false) override;
};
#endif //PROJECT_MULTIPLECOLUMNMULTIPLIER_H
