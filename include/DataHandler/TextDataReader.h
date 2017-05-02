//
// Created by obada on 5/1/17.
//

#ifndef PROJECT_TEXTDATAREADER_H
#define PROJECT_TEXTDATAREADER_H


#include <vector>
#include "DataReader.h"
using namespace std;

class TextDataReader : public DataReader{
private:
    template<typename Out>
    static void split(const std::string& s, char delim, Out result);

    static std::vector<std::string> split(const std::string& s, char delim);
public:
    virtual int read(string file_path, double**& mat, double*& vec) override;
};


#endif //PROJECT_TEXTDATAREADER_H
