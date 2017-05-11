//
// Created by ojabassini on 5/11/17.
//

#ifndef PROJECT_SECOND_H
#define PROJECT_SECOND_H

#include <Serial/MatrixMultiplier.h>

namespace Pvm {
    class SingleColumnMultiplierSecond : public MatrixMultiplier {
    public:
        SingleColumnMultiplierSecond( std::string file_path );

        void multiply( std::string result_file_path ) override;

    };
}

#endif //PROJECT_SINGLECOLUMNMULTIPLIERSECOND_H
