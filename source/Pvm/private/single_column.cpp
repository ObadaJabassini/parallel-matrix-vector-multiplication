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
    char* groupName = "single_row";
    double** matrix;
    double* vector;
    pvm_catchout(stdout);
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    int size, count;
    int* child_id;
    auto start = chrono::steady_clock::now();
    if ( is_parent ) {
        auto reader = make_shared<TextDataReader>();
        size = reader->read(argv[1], matrix, vector);
        count = size - 1;
        child_id = new int[count];
        start = chrono::steady_clock::now();
        int cc = pvm_spawn("/home/obada/CLionProjects/Project/bin/single_column", NULL, 0, "", count, child_id);
        if ( cc != count ) {
            cout << "\nFailed to spwan required children\n...Exit...Press any Key to exit\n";
            pvm_exit();
            exit(-1);
        }
        pvm_initsend(PvmDataDefault);
        pvm_pkint(&size, 1, 1);
        pvm_pkint(&count, 1, 1);
        pvm_pkdouble(vector, size, 1);
        pvm_mcast(child_id, count, 1);
    } else {
        pvm_recv(parent_tid, 1);
        pvm_upkint(&size, 1, 1);
        pvm_upkint(&count, 1, 1);
        pvm_upkdouble(vector, size, 1);
//        auto info = pvm_upkdouble(vector, size, 1);
//        switch(info){
//            case PvmNoBuf:
//                cout << "No buf";
//                break;
//            case PvmBadMsg:
//                cout << "bad msg";
//                break;
//            case PvmNoData:
//                cout << "bad data";
//                break;
//        }
//        vector = new double[3]{1, 2, 3};
//        for ( int i = 0; i < count; ++i ) {
//            cout << vector[i] << " ";
//        }
    }
    int gid = pvm_joingroup(groupName);
    pvm_barrier(groupName, count + 1);
    int groupSize = pvm_gsize(groupName);
    int allRoot;
    if ( is_parent )
        allRoot = pvm_getinst(groupName, tid);
    else
        allRoot = pvm_getinst(groupName, parent_tid);
    int* rec = new int[size];
    if ( is_parent ) {
        int scatterCount = groupSize * size;
        auto scatterData = new double[scatterCount];
        for ( int j = 0; j < size; ++j ) {
            for ( int i = 0; i < size; ++i ) {
                scatterData[i * size + j] = matrix[i][j];
            }
        }
        pvm_scatter(rec, scatterData, size, PVM_DOUBLE, 2, groupName, allRoot);
    } else {
        pvm_scatter(rec, NULL, size, PVM_DOUBLE, 2, groupName, allRoot);
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
}
