#ifndef PROJECT_SINGLEROWMULTIPLIER_H
#define PROJECT_SINGLEROWMULTIPLIER_H


#include "../Serial/MatrixMultiplier.h"

class SingleRowMultiplier : public MatrixMultiplier{
public:
    SingleRowMultiplier(std::string file_path);

    void multiply(std::string result_file_path) override;
};


#endif //PROJECT_SINGLEROWMULTIPLIER_H
