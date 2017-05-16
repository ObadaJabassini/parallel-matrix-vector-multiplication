#include <iostream>
#include <pvm3.h>
#include <memory>
#include <chrono>
#include <DataHandler/TextDataReader.h>
#include <DataHandler/ResultTextDataWriter.h>

using namespace std;
using namespace DataHandler;

int main( int argc, char** argv ) {
    double* row;
    int* others;
    pvm_catchout( stdout );
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    int size;
    int index;
    double element;
    auto start = chrono::steady_clock::now();
    if ( is_parent ) {
        double** matrix, *vector;
        auto reader = make_shared<TextDataReader>();
        size = reader->read( argv[1],
                             matrix,
                             vector );
        start = chrono::steady_clock::now();
        others = new int[size - 1];
        int cc = pvm_spawn( "/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_single_row",
                            NULL,
                            0,
                            "",
                            size - 1,
                            others );
        if ( cc != size - 1 ) {
            cout << "\nFailed to spawn required children \n...Exit...Press any Key to exit\n";
            pvm_exit();
            exit( -1 );
        }
        for ( int i = 1; i < size; ++i ) {
            pvm_initsend( PvmDataDefault );
            pvm_pkint( &size, 1, 1 );
            pvm_pkdouble( matrix[i], size, 1);
            pvm_pkdouble( &vector[i], 1, 1);
            pvm_send(others[i - 1], i);
        }
        index = 0;
        element = vector[0];
        row = matrix[0];
    } else {
        int buffer = pvm_recv( parent_tid,
                               -1 );
        pvm_bufinfo( buffer, NULL, &index, NULL );
        pvm_upkint( &size, 1, 1 );
        row = new double[size];
        pvm_upkdouble( row, size, 1 );
        pvm_upkdouble( &element, 1, 1 );
        others = new int[size - 1];
        int* sib = new int[size - 1];
        pvm_siblings( &sib );
        others[0] = parent_tid;
        for ( int i = 0, j = 1; i < size - 1; ++i ) {
            if(tid != sib[i])
                others[j++] = sib[i];
        }
    }
    pvm_initsend(PvmDataDefault);
    pvm_pkdouble(&element, 1, 1);
    pvm_mcast(others, size - 1, index);
    double result = element * row[index];
    for ( int l = 0; l < size - 1; ++l ) {
        int temp;
        int buffer = pvm_recv( -1,
                               -1 );
        pvm_bufinfo( buffer, NULL, &temp, NULL );
        pvm_upkdouble(&element, 1, 1);
        result += row[temp] * element;
    }
    if(is_parent){
        double* res = new double[size];
        res[0] = result;
        for ( int i = 0; i < size - 1; ++i ) {
            int buffer = pvm_recv(-1, -1);
            pvm_bufinfo( buffer, NULL, &index, NULL );
            pvm_upkdouble(&result, 1, 1);
            res[index] = result;
        }
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], res, size, chrono::duration<double, milli>( end - start ).count());
    }
    else{
        pvm_initsend(PvmDataDefault);
        pvm_pkdouble(&result, 1, 1);
        pvm_send(parent_tid, index);
    }
    pvm_exit();
}
