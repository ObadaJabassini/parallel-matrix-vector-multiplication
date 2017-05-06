#include <iostream>
#include <pvm3.h>
#include <memory>
#include <chrono>
#include <DataHandler/TextDataReader.h>
#include <DataHandler/TextDataWriter.h>

using namespace std;

int main( int argc, char** argv ) {
    char* groupName = "multiple_rows";
    double* vector;
    double* part;
    double* matrix;
    pvm_catchout( stdout );
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    auto start = chrono::steady_clock::now();
    int rows, cols, index;
    int block_size;
    int* others;
    int count;
    if ( is_parent ) {
        index = 0;
        block_size = stoi( argv[3] );
        double* temp;
        double** matrix;
        auto reader = make_shared<TextDataReader>();
        cols = reader->read( argv[1],
                             matrix,
                             vector );
        rows = cols;
        if ( cols % block_size != 0 ) {
            rows = cols + cols % block_size;
            temp = new double[rows * cols];
            for ( int i = 0; i < cols; ++i ) {
                for ( int j = 0; j < cols; ++j ) {
                    temp[i * cols + j] = matrix[i][j];
                }
            }
            for ( int i = cols; i < rows; ++i ) {
                temp[i] = 0;
            }
            double* temp2 = new double[rows];
            for ( int k = 0; k < cols; ++k ) {
                temp2[k] = vector[k];
            }
            for ( int l = cols; l < rows; ++l ) {
                temp2[l] = 0;
            }
            vector = temp2;
        } else {
            temp = new double[cols * cols];
        }
        start = chrono::steady_clock::now();
        count = rows / block_size;
        others = new int[count - 1];
        int cc = pvm_spawn( "/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/multiple_rows",
                            NULL,
                            0,
                            "",
                            count - 1,
                            others );
        if ( cc != count - 1 ) {
            cout << "\nFailed to spawn required children \n...Exit...Press any Key to exit\n";
            pvm_exit();
            exit( -1 );
        }
        for ( int m = 1; m < count; ++m ) {
            pvm_initsend( PvmDataDefault );
            pvm_pkint( &rows, 1, 1 );
            pvm_pkint( &cols, 1, 1 );
            pvm_pkint( &block_size, 1, 1 );
            pvm_pkint( &count, 1, 1 );
            pvm_pkdouble( temp + m * cols * block_size, cols * block_size, 1 );
            pvm_pkdouble( vector + m * block_size, block_size, 1 );
            pvm_send( others[m - 1], m );
        }
        index = 0;
        part = new double[block_size];
        for ( int n = 0; n < block_size; ++n ) {
            part[n] = vector[n];
        }
    } else {
        int buffer = pvm_recv( -1, -1 );
        pvm_bufinfo( buffer, NULL, &index, NULL );
        pvm_upkint( &rows, 1, 1 );
        pvm_upkint( &cols, 1, 1 );
        pvm_upkint( &block_size, 1, 1 );
        pvm_upkint( &count, 1, 1 );
        matrix = new double[block_size * cols];
        pvm_upkdouble( matrix, cols * block_size, 1 );
        part = new double[block_size];
        pvm_upkdouble( part, block_size, 1 );
        others = new int[count - 1];
        others[0] = parent_tid;
        int* sib = new int[count - 1];
        pvm_siblings( &sib );
        for ( int i = 0, j = 1; i < count - 1; ++i ) {
            if ( tid != sib[i] )
                others[j++] = sib[i];
        }
    }
    vector = new double[rows];
    for ( int i = 0; i < block_size; ++i ) {
        vector[index * block_size + i] = part[i];
    }
    pvm_initsend( PvmDataDefault );
    pvm_pkdouble( part, block_size, 1 );
    pvm_mcast( others, count - 1, index );
    for ( int l = 0; l < count - 1; ++l ) {
        int temp;
        int buffer = pvm_recv( -1,
                               -1 );
        pvm_bufinfo( buffer, NULL, &temp, NULL );
        pvm_upkdouble( part, block_size, 1 );
        for ( int i = 0; i < block_size; ++i ) {
            vector[temp * block_size + i] = part[i];
        }
    }
    double* result = new double[block_size];
    for ( int i = 0; i < block_size; ++i ) {
        result[i] = 0;
        for ( int j = 0; j < cols; ++j ) {
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
    if ( is_parent ) {
        for ( int i = 0; i < block_size; ++i ) {
            vector[i] = result[i];
        }
        for ( int i = 0; i < count - 1; ++i ) {
            int buffer = pvm_recv( -1, -1 );
            pvm_bufinfo( buffer, NULL, &index, NULL );
            pvm_upkdouble( result, block_size, 1 );
            for ( int j = 0; j < block_size; ++j ) {
                vector[index * block_size + j] = result[j];
            }
        }
        for ( int k = 0; k < rows; ++k ) {
            cout << vector[k] << " ";
        }
        auto end = chrono::steady_clock::now();
        TextDataWriter().write( argv[2], vector, rows - rows % block_size,
                                chrono::duration<double, milli>( end - start ).count());
    } else {
        pvm_initsend( PvmDataDefault );
        pvm_pkdouble( result, block_size, 1 );
        pvm_send( parent_tid, index );
    }
    pvm_exit();
}