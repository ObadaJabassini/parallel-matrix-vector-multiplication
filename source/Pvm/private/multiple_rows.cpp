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
    char* groupName = "multiple_row";
    double** matrix;
    double* vector;
    pvm_catchout(stdout);
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    int size, count, offset, rows, cols, num_of_process;
    int* child_id;
    auto start = chrono::steady_clock::now();
    if ( is_parent ) {
        auto reader = make_shared<TextDataReader>();
        size = reader->read(argv[1], matrix, vector);
        count = size - 1;
        offset = atoi(argv[3]);
        child_id = new int[count];
        start = chrono::steady_clock::now();
        rows = size + size % offset;
        cols = size;
        num_of_process = rows / offset;
        int cc = pvm_spawn("/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/pvm/multiple_rows", nullptr, 0, "", num_of_process - 1,
                           child_id);
        if ( cc != num_of_process - 1 ) {
            cout << "\nFailed to spwan required children\n...Exit...Press any Key to exit\n";
            pvm_exit();
        }
        pvm_initsend(PvmDataDefault);
        pvm_pkint(&size, 1, 1);
        pvm_pkint(&count, 1, 1);
        pvm_pkint(&offset, 1, 1);
        pvm_pkdouble(vector, size, 1);
        pvm_mcast(child_id, count, 1);
        if ( size % offset != 0 ) {
            double** temp = new double* [size + size % offset];
            for ( int l = 0; l < size + size % offset; ++l ) {
                temp[l] = new double[size];
            }
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
    } else {
        pvm_recv(parent_tid, 1);
        pvm_upkint(&size, 1, 1);
        pvm_upkint(&count, 1, 1);
        pvm_upkint(&offset, 1, 1);
        pvm_upkdouble(vector, size, 1);
        rows = size + size % offset;
        cols = size;
        num_of_process = num_of_process = rows / offset;
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
        TextDataWriter().write(argv[2], result, size, chrono::duration<double, milli>(end - start).count());
    }
    pvm_barrier(groupName, groupSize);
    pvm_lvgroup(groupName);
    pvm_exit();
}
