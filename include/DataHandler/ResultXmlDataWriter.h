//
// Created by ojabassini on 5/12/17.
//

#ifndef PROJECT_RESULTXMLDATAWRITER_H
#define PROJECT_RESULTXMLDATAWRITER_H


#include "ResultDataWriter.h"

namespace DataHandler {

    class ResultXmlDataWriter : public ResultDataWriter {
    public:
        virtual void write( std::string file_path, double* vec, int size, double time ) override;
    };

}

#endif //PROJECT_RESULTXMLDATAWRITER_H
