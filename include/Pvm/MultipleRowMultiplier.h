//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_MULTIPLEROWMULTIPLIER_H
#define PROJECT_MULTIPLEROWMULTIPLIER_H


#include "../Serial/MatrixMultiplier.h"

namespace Pvm {

    class MultipleRowMultiplier : public MatrixMultiplier {
    private:
        int rows;
    public:
        MultipleRowMultiplier( std::string file_path, int rows);

        void multiply( std::string result_file_path ) override;

    };
}

#endif //PROJECT_MULTIPLEROWMULTIPLIER_H
