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
        int cc = pvm_spawn("/home/obada/CLionProjects/Project/bin/single_row", NULL, 0, "", count, child_id);
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
    pvm_barrier(groupName, size);
    int allRoot;
    if ( is_parent )
        allRoot = pvm_getinst(groupName, tid);
    else
        allRoot = pvm_getinst(groupName, parent_tid);
    int* rec = new int[size];
    if ( is_parent ) {
        auto scatterData = new double[size * size];
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                scatterData[i * size + j] = matrix[i][j];
            }
        }
        pvm_scatter(rec, scatterData, size, PVM_DOUBLE, 2, groupName, allRoot);
    } else {
        pvm_scatter(rec, NULL, size, PVM_DOUBLE, 2, groupName, allRoot);
    }
    double sum = 0;
    for ( int k = 0; k < size; ++k ) {
        sum += rec[k] * vector[k];
    }
    if ( !is_parent )
        pvm_gather(NULL, &sum, 1, PVM_DOUBLE, 3, groupName, allRoot);
    else {
        auto result = new double[size];
        pvm_gather(result, &sum, 1, PVM_DOUBLE, 3, groupName, allRoot);
        auto end = chrono::steady_clock::now();
//        for ( int i = 0; i < size; ++i ) {
//            cout << result[i] << endl;
//        }
        TextDataWriter().write(argv[2], result, size, chrono::duration<double, milli>(end - start).count());
    }
    pvm_barrier(groupName, size);
    pvm_lvgroup(groupName);
    pvm_exit();
}
