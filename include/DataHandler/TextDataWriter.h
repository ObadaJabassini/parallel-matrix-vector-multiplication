//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_TEXTDATAWRITER_H
#define PROJECT_TEXTDATAWRITER_H

#include "DataWriter.h"

namespace DataHandler {

    class TextDataWriter : public DataWriter {
    public:
        virtual void write( std::string file_path, double* vec, int size, double time ) override;
    };

}
#endif //PROJECT_TEXTDATAWRITER_H
