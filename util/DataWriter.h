

#ifndef PROJECT_DATAWRITER_H
#define PROJECT_DATAWRITER_H

#include <string>

class DataWriter {
public:
    virtual void write(std::string file_path, double* result, int size, double time) = 0;
};


#endif //PROJECT_DATAWRITER_H
