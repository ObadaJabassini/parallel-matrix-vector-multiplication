
#include <fstream>
#include <chrono>
#include <memory>
#include <iostream>
#include <DataHandler/TextDataReader.h>
#include <DataHandler/TextDataWriter.h>
#include <Serial/MatrixMultiplier.h>
#include <Serial/SerialMatrixMultiplier.h>

using namespace DataHandler;

SerialMatrixMultiplier::SerialMatrixMultiplier(std::string file_path) : MatrixMultiplier(file_path) {

}

void SerialMatrixMultiplier::multiply(std::string result_file_path) {
    double** matrix;
    double* vector;
    auto reader = std::make_shared<TextDataReader>();
    int size = reader->read(file_path, matrix, vector);
    double* result = new double[size];
    auto start = chrono::steady_clock::now();
    for ( int i = 0; i < size; ++i ) {
        result[i] = 0;
        for ( int j = 0; j < size; ++j ) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    auto end = chrono::steady_clock::now();
    TextDataWriter().write(result_file_path, result, size, chrono::duration <double, milli> (end - start).count());
    delete result;
    delete vector;
    for ( int k = 0; k < size; ++k ) {
        delete matrix[k];
    }
    delete matrix;
}

string SerialMatrixMultiplier::multiply( bool justTime ) {
    double** matrix;
    double* vector;
    auto reader = std::make_shared<TextDataReader>();
    int size = reader->read(file_path, matrix, vector);
    double* result = new double[size];
    auto start = chrono::steady_clock::now();
    for ( int i = 0; i < size; ++i ) {
        result[i] = 0;
        for ( int j = 0; j < size; ++j ) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    auto end = chrono::steady_clock::now();
    if(justTime)
        return std::to_string(chrono::duration <double, milli> (end - start).count());
    throw exception();
}
