//
// Created by ojabassini on 5/23/17.
//

#ifndef PROJECT_MULTIPLEROWMULTIPLIERSECOND_H
#define PROJECT_MULTIPLEROWMULTIPLIERSECOND_H

#include "../Serial/MatrixMultiplier.h"

namespace Mpi {
    class MultipleRowMultiplierSecond : public MatrixMultiplier {
    private:
        int rows;
    public:
        MultipleRowMultiplierSecond( std::string file_path, int rows);

        void multiply( std::string result_file_path ) override;

    };
}


#endif //PROJECT_MULTIPLEROWMULTIPLIERSECOND_H
