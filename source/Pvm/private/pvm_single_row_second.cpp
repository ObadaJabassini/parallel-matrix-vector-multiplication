#include <iostream>
#include <pvm3.h>
#include <memory>
#include <chrono>
#include <algorithm>
#include <DataHandler/TextDataReader.h>
#include <DataHandler/ResultTextDataWriter.h>

using namespace std;
using namespace DataHandler;

int main( int argc, char** argv ) {
    char* groupName = "pvm_single_row_second1";
    pvm_catchout( stdout );
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    double* row;
    double element;
    int size, index;
    auto start = chrono::steady_clock::now();
    pvm_joingroup( groupName );
    int allRoot;
    if(!is_parent) {
        allRoot = pvm_getinst( groupName, parent_tid );
        size = stoi(argv[1]);
    }
    else{
        allRoot = pvm_getinst( groupName, tid );
    }
    if ( is_parent ) {
        double* vector, ** matrix;
        auto reader = make_shared<TextDataReader>();
        size = reader->read( argv[1],
                             matrix,
                             vector );
        int* others = new int[size - 1];
        string str = std::to_string( size );
        start = chrono::steady_clock::now();
        char* pass[2] = {&str[0], NULL};
        int cc = pvm_spawn(
                ( char* ) "/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_single_row_second",
                pass,
                0,
                ( char* ) "",
                size - 1,
                others );
        if ( cc != size - 1 ) {
            cout << "\nFailed to spwan required children\n...Exit...Press any Key to exit\n";
            pvm_exit();
            exit( -1 );
        }
        int* indices = new int[size];
        for ( int i = 0; i < size; ++i ) {
            indices[i] = i;
        }
        double* scatterData = new double[size * size];
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                scatterData[i * size + j] = matrix[i][j];
            }
        }
        row = new double[size];
        pvm_barrier( groupName, size );
        pvm_scatter( row, scatterData, size, PVM_DOUBLE, 4, groupName, allRoot );
        pvm_scatter( &index, indices, 1, PVM_INT, 2, groupName, allRoot );
        pvm_scatter( &element, vector, 1, PVM_DOUBLE, 3, groupName, allRoot );
    } else {
        row = new double[size];
        pvm_barrier( groupName, size );
        pvm_scatter( row, NULL, size, PVM_DOUBLE, 4, groupName, allRoot );
        pvm_scatter( &index, NULL, 1, PVM_INT, 2, groupName, allRoot );
        pvm_scatter( &element, NULL, 1, PVM_DOUBLE, 3, groupName, allRoot );
    }
    pvm_barrier( groupName, size );
    double result = element * row[index];
    pvm_initsend( PvmDataDefault );
    pvm_pkdouble( &element, 1, 1 );
    pvm_bcast( groupName, index );
    for ( int j = 1; j <= size - 1; ++j ) {
        int temp;
        int buffer = pvm_recv( -1, -1 );
        pvm_bufinfo( buffer, NULL, &temp, NULL );
        pvm_upkdouble( &element, 1, 1 );
        result += row[temp] * element;
    }
    pvm_barrier( groupName, size );
    if ( is_parent ) {
        pvm_gather( row, &result, 1, PVM_DOUBLE, 4, groupName, allRoot );
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], row, size, chrono::duration<double, milli>( end - start ).count());
    } else {
        pvm_gather( NULL, &result, 1, PVM_DOUBLE, 4, groupName, allRoot );
    }
    pvm_barrier( groupName, size );
    pvm_exit();
}
