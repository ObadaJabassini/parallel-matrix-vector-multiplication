//
// Created by ojabassini on 5/7/17.
//

#ifndef PROJECT_MULTIPLEROWMULTIPLIER_H
#define PROJECT_MULTIPLEROWMULTIPLIER_H

#include "../Serial/MatrixMultiplier.h"

namespace Mpi {
    class MultipleRowMultiplier : public MatrixMultiplier {
    private:
        int rows;
    public:
        MultipleRowMultiplier( std::string file_path, int rows = 3 );

        void multiply( std::string result_file_path ) override;

        std::string multiply( bool justTime = false ) override;
    };
}


#endif //PROJECT_MULTIPLEROWMULTIPLIER_H
