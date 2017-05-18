//
// Created by ojabassini on 5/18/17.
//

#ifndef PROJECT_SINGLEROWMULTIPLIERSECOND_H
#define PROJECT_SINGLEROWMULTIPLIERSECOND_H

#include "../Serial/MatrixMultiplier.h"
namespace Pvm {
    class SingleRowMultiplierSecond : public MatrixMultiplier {
    public:
        SingleRowMultiplierSecond( std::string file_path );

        void multiply( std::string result_file_path ) override;

    };

}

#endif //PROJECT_SINGLEROWMULTIPLIERSECOND_H
