
#ifndef PROJECT_DATAREADER_H
#define PROJECT_DATAREADER_H

#include <string>

using namespace std;

namespace DataHandler {

    class DataReader {
    public:
        virtual int read( string file_path, double**& mat, double*& vec ) = 0;
    };

}
#endif //PROJECT_DATAREADER_H
