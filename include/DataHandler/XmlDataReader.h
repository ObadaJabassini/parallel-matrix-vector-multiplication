//
// Created by ojabassini on 5/17/17.
//

#ifndef PROJECT_XMLDATAREADER_H
#define PROJECT_XMLDATAREADER_H

#include "DataReader.h"

using namespace std;

namespace DataHandler {
    class XmlDataReader: public DataReader{
    public:
        int read( string file_path, double**& mat, double*& vec ) override;
    };
}

#endif //PROJECT_XMLDATAREADER_H
