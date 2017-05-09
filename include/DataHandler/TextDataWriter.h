//
// Created by ojabassini on 5/9/17.
//

#ifndef PROJECT_TEXTDATAWRITER_H
#define PROJECT_TEXTDATAWRITER_H

#include "DataWriter.h"

namespace DataHandler {
    class TextDataWriter: public DataWriter{
    public:
        void write( string filePath, double** matrix, double* vector, int size ) override;
    };
}
#endif //PROJECT_TEXTDATAWRITER_H
