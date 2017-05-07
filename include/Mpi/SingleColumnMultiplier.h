//
// Created by ojabassini on 5/7/17.
//

#ifndef PROJECT_SINGLECOLUMNMULTIPLIER_H
#define PROJECT_SINGLECOLUMNMULTIPLIER_H

#include "../Serial/MatrixMultiplier.h"

namespace Mpi {

    class SingleColumnMultiplier : public MatrixMultiplier {
    public:
        SingleColumnMultiplier( std::string file_path );

        void multiply( std::string result_file_path ) override;

        std::string multiply( bool justTime = false ) override;
    };
}

#endif //PROJECT_SINGLECOLUMNMULTIPLIER_H
