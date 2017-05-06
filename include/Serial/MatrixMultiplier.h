
#ifndef PROJECT_MATRIXMULTIPLIER_H
#define PROJECT_MATRIXMULTIPLIER_H

#include <string>

class MatrixMultiplier {
protected:
    std::string file_path;
public:
    MatrixMultiplier(std::string file_path);
    virtual void multiply(std::string result_file_path) = 0;
    virtual std::string multiply(bool justTime = false) = 0;
};


#endif //PROJECT_MATRIXMULTIPLIER_H
