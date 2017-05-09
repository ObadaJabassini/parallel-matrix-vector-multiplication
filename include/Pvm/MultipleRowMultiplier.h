//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_MULTIPLECOLUMNMULTIPLIER_H
#define PROJECT_MULTIPLECOLUMNMULTIPLIER_H


#include "../Serial/MatrixMultiplier.h"

namespace Pvm {

    class MultipleRowMultiplier : public MatrixMultiplier {
    private:
        int rows;
    public:
        MultipleRowMultiplier( std::string file_path, int rows = 3 );

        void multiply( std::string result_file_path ) override;

    };
}

#endif //PROJECT_MULTIPLECOLUMNMULTIPLIER_H
