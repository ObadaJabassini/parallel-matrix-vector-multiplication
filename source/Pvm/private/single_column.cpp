#include <iostream>
#include <pvm3.h>
#include <memory>
#include <chrono>
#include <algorithm>
#include "DataHandler/TextDataReader.h"
#include "DataHandler/TextDataWriter.h"

using namespace std;

//class NotEnoughParameterException : public exception{
//public:
//    const char* what() const override {
//        return "Not Enough parameters";
//    }
//};

int main( int argc, char** argv ) {
    char* groupName = "single_column";
    int tid = pvm_mytid();
    pvm_catchout( stdout );
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    int size;
    double** matrix;
    double* vector;
    auto start = chrono::steady_clock::now();
    if ( is_parent ) {
        auto reader = make_shared<TextDataReader>();
        size = reader->read( argv[1],
                             matrix,
                             vector );
        int* child_id = new int[size - 1];
        start = chrono::steady_clock::now();
        int cc = pvm_spawn( "/home/obada/CLionProjects/parallel-matrix-vector-multiplication/bin/single_column",
                            NULL,
                            0,
                            "",
                            size - 1,
                            child_id );
        if ( cc != size - 1 ) {
            cout << "\nFailed to spwan required children\n...Exit...Press any Key to exit\n";
            pvm_exit();
            exit( -1 );
        }
        pvm_initsend( PvmDataDefault );
        pvm_pkint( &size,
                   1,
                   1 );
        pvm_mcast( child_id,
                   size - 1,
                   1 );
    } else {
        pvm_recv( parent_tid,
                  1 );
        pvm_upkint( &size,
                    1,
                    1 );
        vector = new double[size];
    }
    int gid = pvm_joingroup( groupName );
    pvm_barrier( groupName, size );
    int allRoot;
    if ( is_parent )
        allRoot = pvm_getinst( groupName, tid );
    else
        allRoot = pvm_getinst( groupName, parent_tid );
    int* rec = new int[size + 1];
    if ( is_parent ) {
        auto scatterData = new double[size * size + size];
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                scatterData[i * size + j] = matrix[i][j];
            }
            scatterData[i * size + size] = vector[i];
        }
        pvm_scatter( rec, scatterData, size + 1, PVM_DOUBLE, 2, groupName, allRoot );
    } else {
        pvm_scatter( rec, NULL, size + 1, PVM_DOUBLE, 2, groupName, allRoot );
    }
    transform( rec, rec + size, vector, []( double element ) -> double { return element * rec[size]; } );
    pvm_reduce( PvmSum, vector, size, PVM_DOUBLE, 4, groupName, allRoot );
    if ( is_parent ) {
        auto end = chrono::steady_clock::now();
        TextDataWriter().write( argv[2], vector, size, chrono::duration<double, milli>( end - start ).count());
    }
    pvm_barrier( groupName, size );
    pvm_lvgroup( groupName );
    pvm_exit();
}
