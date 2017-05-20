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
    char* groupName = "multiple_columns";
    int tid = pvm_mytid();
    int parent_tid = pvm_parent();
    pvm_catchout( stdout );
    bool is_parent = (parent_tid == PvmNoParent) || (parent_tid == PvmParentNotSet);
    int rows, cols, block_size, count;
    double** matrix;
    double* vector;
    auto start = chrono::steady_clock::now();
    if ( is_parent ) {
        block_size = stoi(argv[3]);
        auto reader = make_shared<TextDataReader>();
        rows = reader->read( argv[1],
                             matrix,
                             vector );
        start = chrono::steady_clock::now();
        cols = rows;
        if(cols % block_size != 0){
            cols = rows + (block_size - rows % block_size);
            double** temp = new double*[rows];
            for ( int i = 0; i < rows; ++i ) {
                temp[i] = new double[cols];
            }
            for ( int i = 0; i < rows; ++i ) {
                for ( int j = 0; j < rows; ++j ) {
                    temp[i][j] = matrix[i][j];
                }
            }
            for ( int i = 0; i < rows; ++i ) {
                for ( int j = rows; j < cols; ++j ) {
                    temp[i][j] = 0;
                }
            }
            matrix = temp;
            double* temp2 = new double[cols];
            for ( int i = 0; i < rows; ++i ) {
                temp2[i] = vector[i];
            }
            for ( int i = rows; i < cols; ++i ) {
                temp2[i] = 0;
            }
            vector = temp2;
        }
        count = cols / block_size;
        if(count != 1) {
            int* child_id = new int[count - 1];
            int cc = pvm_spawn(
                    "/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_multiple_columns",
                    NULL,
                    0,
                    "",
                    count - 1,
                    child_id );
            if ( cc != count - 1 ) {
                cout << "\nFailed to spwan required children\n...Exit...Press any Key to exit\n";
                pvm_exit();
                exit( -1 );
            }
            pvm_initsend( PvmDataDefault );
            pvm_pkint( &rows, 1, 1 );
            pvm_pkint( &cols, 1, 1 );
            pvm_pkint( &block_size, 1, 1 );
            pvm_pkint( &count, 1, 1 );
            pvm_mcast( child_id, count - 1, 1 );
        }
    }
    else{
        pvm_recv(-1, -1);
        pvm_upkint(&rows, 1, 1);
        pvm_upkint(&cols, 1, 1);
        pvm_upkint(&block_size, 1, 1);
        pvm_upkint(&count, 1, 1);
    }
    pvm_joingroup(groupName);
    pvm_barrier(groupName, count);
    int allRoot;
    if ( is_parent )
        allRoot = pvm_getinst( groupName, tid );
    else
        allRoot = pvm_getinst( groupName, parent_tid );
    double* rec = new double[rows * block_size + block_size];
    if(is_parent){
        double* scatter_data = new double[rows * cols + cols];
        for ( int j = 0; j < cols; ++j ) {
            for ( int i = 0; i < rows; ++i ) {
                scatter_data[j * (rows + 1) + i] = matrix[i][j];
            }
            scatter_data[(j + 1) * rows + j] = vector[j];
        }
        pvm_scatter( rec, scatter_data, rows * block_size + block_size, PVM_DOUBLE, 2, groupName, allRoot );
    }
    else{
        pvm_scatter( rec, NULL, rows * block_size + block_size, PVM_DOUBLE, 2, groupName, allRoot );
    }
    vector = new double[rows];
    for ( int k = 0; k < rows; ++k ) {
        vector[k] = 0;
        for ( int i = 0; i < rows * block_size + block_size - rows; i += rows + 1 ) {
            vector[k] += rec[i + k] * rec[i + rows];
        }
    }
    pvm_reduce( PvmSum, vector, rows, PVM_DOUBLE, 4, groupName, allRoot );
    if ( is_parent ) {
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], vector, rows, chrono::duration<double, milli>( end - start ).count());
    }
    pvm_barrier( groupName, count );
    pvm_lvgroup( groupName );
    pvm_exit();
}
