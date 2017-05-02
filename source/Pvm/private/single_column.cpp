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

int main(int argc, char** argv) {
    auto reader = make_shared<TextDataReader>();
    char* groupName = "single_row";
    double** matrix;
    double* vector;
    if ( argc != 3 ) {
        //throw NotEnoughParameterException();
        exit(-1);
    }
    int size = reader->read(argv[1], matrix, vector);
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    int count = size - 1, block_size = size;
    int* child_id;
    auto start = chrono::steady_clock::now();
    int cc = pvm_spawn("/home/obada/CLionProjects/Project/pvm/single_row", nullptr, 0, "", count, child_id);
    if ( cc != count ) {
        cout << "\nFailed to spwan required children\n...Exit...Press any Key to exit\n";
        pvm_exit();
    }
    int gid = pvm_joingroup(groupName);
    pvm_barrier(groupName, count + 1);
    int groupSize = pvm_gsize(groupName);
    int allRoot;
    if ( is_parent )
        allRoot = pvm_getinst(groupName, tid);
    else
        allRoot = pvm_getinst(groupName, parent_tid);
    int* rec = new int[block_size];
    if ( is_parent ) {
        int scatterCount = groupSize * block_size;
        auto scatterData = new double[scatterCount];
        for ( int j = 0; j < size; ++j ) {
            for ( int i = 0; i < size; ++i ) {
                scatterData[i * size + j] = matrix[i][j];
            }
        }
        pvm_scatter(rec, scatterData, block_size, PVM_DOUBLE, 2, groupName, allRoot);
    } else {
        pvm_scatter(rec, NULL, block_size, PVM_DOUBLE, 2, groupName, allRoot);
    }
    auto send = new double[size];
    for ( int k = 0; k < size; ++k ) {
        send[k] = rec[k] * vector[gid];
    }
    pvm_reduce(PvmSum, send, size, PVM_DOUBLE, 4, groupName, allRoot);
    if(is_parent){
        auto end = chrono::steady_clock::now();
        TextDataWriter().write(argv[2], send, size, chrono::duration<double, milli>(end - start).count());
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
