//
// Created by ojabassini on 5/8/17.
//

#ifndef PROJECT_RESULTWRITER_H
#define PROJECT_RESULTWRITER_H

#include "Benchmarker.h"
#include <vector>

namespace Performance {

    class ResultWriter {
    private:
        Benchmarker* benchmarker;
    public:
        ResultWriter( Benchmarker* benchmarker );

        void write( std::string file_path, std::vector<std::string> names );
    };

}
#endif //PROJECT_RESULTWRITER_H
