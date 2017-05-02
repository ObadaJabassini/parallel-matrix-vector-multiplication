

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../include/DataHandler/TextDataReader.h"

using namespace std;

int TextDataReader::read(string file_path, double**& mat, double*& vec) {
    vector<string> lines;
    std::ifstream input(file_path);
    std::string line;
    for ( ; getline(input, line); ) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        lines.push_back(line);
    }
    unsigned long len = lines.size();
    int size = ( int ) (len - 3);
    mat = new double* [size];
    vec = new double[size];
    for ( int j = 0; j < size; ++j ) {
        mat[j] = new double[size];
    }
    bool readingMat = true;
    int currentRow = 0;
    for ( int i = 0; i < len; ++i ) {
        if ( lines[i] == "matrix:" ) {
            readingMat = true;
        } else if ( lines[i] == "vector:" ) {
            readingMat = false;
        } else {
            auto row = TextDataReader::split(lines[i], ',');
            if(readingMat) {
                for ( int j = 0; j < size; ++j ) {
                    mat[currentRow][j] = stod(row[j]);
                }
                ++currentRow;
            }
            else{
                for ( int j = 0; j < size; ++j ) {
                    vec[j] = stod(row[j]);
                }
            }
        }
    }
    return size;
}

std::vector<std::string> TextDataReader::split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

template<typename Out>
void TextDataReader::split(const std::string& s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while ( std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

