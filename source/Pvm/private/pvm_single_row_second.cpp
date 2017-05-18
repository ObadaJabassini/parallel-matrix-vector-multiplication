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
    char* groupName = "pvm_single_row_second";
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    pvm_catchout( stdout );
    double* row, element, **matrix;
    int* others, size;
    auto start = chrono::steady_clock::now();
    if ( is_parent ) {
        double* vector;
        auto reader = make_shared<TextDataReader>();
        size = reader->read( argv[1],
                             matrix,
                             vector );
        others = new int[size - 1];
        start = chrono::steady_clock::now();
        int cc = pvm_spawn(
                "/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_single_row_second",
                NULL,
                0,
                "",
                size - 1,
                others );
        if ( cc != size - 1 ) {
            cout << "\nFailed to spwan required children\n...Exit...Press any Key to exit\n";
            pvm_exit();
            exit( -1 );
        }
        element = vector[0];
        for ( int i = 1; i < size; ++i ) {
            pvm_initsend( PvmDataDefault );
            pvm_pkint( &size, 1, 1 );
            pvm_pkdouble( &vector[i], 1, 1 );
            pvm_send( others[i - 1], 2 );
        }
    } else {
        pvm_recv( -1, -1 );
        pvm_upkint( &size, 1, 1 );
        pvm_upkdouble( &element, 1, 1 );
        others = new int[size - 1];
        int* sib = new int[size - 1];
        pvm_siblings( &sib );
        others[0] = parent_tid;
        for ( int i = 0, j = 1; i < size - 1; ++i ) {
            if ( tid != sib[i] )
                others[j++] = sib[i];
        }
    }
    int gid = pvm_joingroup( groupName );
    pvm_barrier(groupName, size);
    int allRoot;
    if ( is_parent )
        allRoot = pvm_getinst( groupName, tid );
    else
        allRoot = pvm_getinst( groupName, parent_tid );
    row = new double[size];
    if(is_parent){
        double* scatterData = new double[size * size];
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                scatterData[i * size + j] = matrix[i][j];
            }
        }
        pvm_scatter( row, scatterData, size, PVM_DOUBLE, 2, groupName, allRoot );
    }
    else{
        pvm_scatter( row, NULL, size, PVM_DOUBLE, 2, groupName, allRoot );
    }
    for ( int i = 0; i < size; ++i ) {
        cout << row[i] << " ";
    }
    cout << endl;
    double result = element * row[gid];
    pvm_initsend( PvmDataDefault );
    pvm_pkdouble( &element, 1, 1 );
    pvm_mcast( others, size - 1, gid );
    for ( int j = 1; j <= size - 1; ++j ) {
        int index;
        int buffer = pvm_recv( -1,
                               -1 );
        pvm_bufinfo( buffer, NULL, &index, NULL );
        pvm_upkdouble( &element, 1, 1 );
        result += row[index] * element;
    }
    pvm_barrier(groupName, size);
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
