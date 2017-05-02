#include <iostream>
#include <pvm3.h>
#include <memory>
#include <chrono>
#include "DataHandler/TextDataReader.h"
#include "DataHandler/TextDataWriter.h"

using namespace std;

//class NotEnoughParameterException : public exception{
//public:
//    const char* what() const override {
//        return "Not Enough parameters";
//    }
//};

int main(int argc, char** argv){
    auto reader = make_shared<TextDataReader>();
    char* groupName = "single_row";
    double** matrix;
    double* vector;
    if(argc != 3){
        //throw NotEnoughParameterException();
        exit(-1);
    }
    int size = reader->read(argv[1], matrix, vector);
    int offset = atoi(argv[3]);
    if(size % offset != 0){
        double** temp = new double*[size + size % offset];
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                temp[i][j] = matrix[i][j];
            }
        }
        for ( int k = size; k < size + size % offset; ++k ) {
            for ( int i = 0; i < size; ++i ) {
                temp[k][i] = 0;
            }
        }
        matrix = temp;
    }
    int rows = size + size % offset, cols = size;
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    int* child_id;
    int num_of_process = rows / offset;
    auto start = chrono::steady_clock::now();
    int cc = pvm_spawn("/home/obada/CLionProjects/Project/pvm/single_row", nullptr, 0, "", num_of_process - 1, child_id);
    if ( cc != num_of_process - 1 ) {
        cout << "\nFailed to spwan required children\n...Exit...Press any Key to exit\n";
        pvm_exit();
    }
    int gid = pvm_joingroup(groupName);
    pvm_barrier(groupName, num_of_process);
    int groupSize = pvm_gsize(groupName);
    int allRoot;
    if ( is_parent )
        allRoot = pvm_getinst(groupName, tid);
    else
        allRoot = pvm_getinst(groupName, parent_tid);
    int* rec = new int[size * offset];
    if ( is_parent ) {
        auto scatterData = new double[rows * cols];
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                scatterData[size * i + j] = matrix[i][j];
            }
        }
        pvm_scatter(rec, scatterData, size * offset, PVM_DOUBLE, 2, groupName, allRoot);
    } else {
        pvm_scatter(rec, NULL, size * offset, PVM_DOUBLE, 2, groupName, allRoot);
    }
    auto* send = new double[offset];
    for ( int m = 0; m < offset; ++m ) {
        send[m] = 0;
        for ( int i = 0; i < cols; ++i ) {
            send[m] += rec[m * cols + i] * vector[i];
        }
    }
    if ( !is_parent )
        pvm_gather(NULL, send, offset, PVM_DOUBLE, 3, groupName, allRoot);
    else {
        auto result = new double[rows];
        pvm_gather(result, send, offset, PVM_DOUBLE, 3, groupName, allRoot);
        auto end = chrono::steady_clock::now();
        TextDataWriter().write(argv[2], result, size, chrono::duration <double, milli> (end - start).count());
    }
    pvm_barrier(groupName, groupSize);
    pvm_lvgroup(groupName);
    pvm_exit();
    delete groupName;
    delete vector;
    for ( int l = 0; l < size; ++l ) {
        delete matrix[l];
    }
    delete matrix;
}
