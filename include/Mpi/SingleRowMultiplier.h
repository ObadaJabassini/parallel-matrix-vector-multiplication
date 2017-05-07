//
// Created by ojabassini on 5/7/17.
//

#ifndef PROJECT_SINGLEROWMULTIPLIER_H
#define PROJECT_SINGLEROWMULTIPLIER_H

#include "../Serial/MatrixMultiplier.h"

namespace Mpi {
    class SingleRowMultiplier : public MatrixMultiplier {
    public:
        SingleRowMultiplier( std::string file_path );

        void multiply( std::string result_file_path ) override;

        std::string multiply( bool justTime = false ) override;
    };

}

#endif //PROJECT_SINGLEROWMULTIPLIER_H
