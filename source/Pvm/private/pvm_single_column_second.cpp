#include <iostream>
#include <pvm3.h>
#include <memory>
#include <chrono>
#include <DataHandler/TextDataReader.h>
#include <DataHandler/ResultTextDataWriter.h>

using namespace std;
using namespace DataHandler;


int main( int argc, char** argv ) {
    pvm_catchout( stdout );
    int tid = pvm_mytid();
    int parent = pvm_parent();
    bool isParent = (parent == PvmNoParent) || (parent == PvmParentNotSet);
    double* col, element;
    int* others;
    int size, index;
    auto start = chrono::steady_clock::now();
    if ( isParent ) {
        double** matrix, *vector;
        auto reader = make_shared<TextDataReader>();
        size = reader->read( argv[1],
                             matrix,
                             vector );
        start = chrono::steady_clock::now();
        others = new int[size - 1];
        int cc = pvm_spawn(
                "/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_single_column_second",
                NULL, 0, NULL, size - 1, others );
        if ( cc != size - 1 ) {
            cout << "\nFailed to spawn required children \n...Exit...Press any Key to exit\n";
            pvm_exit();
            exit( -1 );
        }
        for ( int i = 1; i < size; ++i ) {
            pvm_initsend( PvmDataDefault );
            pvm_pkint( &size, 1, 1 );
            pvm_pkdouble( matrix[0] + i, size, size + 1 );
            pvm_pkdouble( &vector[i], 1, 1 );
            pvm_send( others[i - 1], i );
        }
        element = vector[0];
        col = new double[size];
        for ( int j = 0; j < size; ++j ) {
            col[j] = matrix[j][0];
        }
        index = 0;
    } else {
        int buffer = pvm_recv( parent, -1 );
        pvm_bufinfo( buffer, NULL, &index, NULL );
        pvm_upkint( &size, 1, 1 );
        col = new double[size];
        pvm_upkdouble( col, size, 1 );
        pvm_upkdouble( &element, 1, 1 );
        others = new int[size - 1];
        int* sib;
        pvm_siblings( &sib );
        others[0] = parent;
        for ( int i = 0, j = 1; i < size - 1; ++i ) {
            if ( tid != sib[i] ) {
                others[j++] = sib[i];
            }
        }
    }
    double result = col[index] * element;
    for ( int i = 0, j = 0; i < size; ++i ) {
        if ( i != index ) {
            pvm_initsend( PvmDataDefault );
            pvm_pkdouble( &col[i], 1, 1 );
            pvm_pkdouble( &element, 1, 1 );
            pvm_send( others[j++], index );
        }
    }
    for ( int i = 0; i < size - 1; ++i ) {
        int temp;
        int buffer = pvm_recv( -1, -1 );
        pvm_bufinfo( buffer, NULL, &temp, NULL );
        double temp1, temp2;
        pvm_upkdouble( &temp1, 1, 1 );
        pvm_upkdouble( &temp2, 1, 1 );
        result += temp1 * temp2;
    }
    if ( isParent ) {
        double* res = new double[size];
        res[0] = result;
        for ( int i = 0; i < size - 1; ++i ) {
            int temp;
            int buffer = pvm_recv( -1, -1 );
            pvm_bufinfo( buffer, NULL, &temp, NULL );
            pvm_upkdouble( &element, 1, 1 );
            res[temp] = element;
        }
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], res, size, chrono::duration<double, milli>( end - start ).count());
    } else {
        pvm_initsend( PvmDataDefault );
        pvm_pkdouble( &result, 1, 1 );
        pvm_send( parent, index );
    }
    pvm_exit();
    return 0;
}