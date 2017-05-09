//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_SINGLECOLUMNMULTIPLIER_H
#define PROJECT_SINGLECOLUMNMULTIPLIER_H

#include <string>
#include "../Serial/MatrixMultiplier.h"

namespace Pvm {

    class SingleColumnMultiplier : public MatrixMultiplier {
    public:
        SingleColumnMultiplier( std::string file_path );

        void multiply( std::string result_file_path ) override;

    };
}
#endif //PROJECT_SINGLECOLUMNMULTIPLIER_H
