#include <iostream>
#include <memory>
#include <chrono>
#include <DataHandler/TextDataReader.h>
#include <DataHandler/ResultTextDataWriter.h>
#include <mpi.h>

using namespace std;
using namespace DataHandler;

int main( int argc, char** argv ) {
    MPI_Init( &argc, &argv );
    const int MASTER = 0;
    int rank, rows, cols, offset, processes;
    double* matrix, * vector, * part;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank );
    MPI_Comm_size(MPI_COMM_WORLD, &processes );
    auto start = chrono::steady_clock::now();
    if ( rank == MASTER ) {
        offset = atoi( argv[3] );
        double* temp;
        double** mat;
        auto reader = make_shared<TextDataReader>();
        cols = reader->read( argv[1],
                             mat,
                             vector );
        rows = cols;
        if ( cols % offset != 0 ) {
            rows = cols + cols % offset;
            temp = new double[rows * cols];
            for ( int i = 0; i < cols; ++i ) {
                for ( int j = 0; j < cols; ++j ) {
                    temp[i * cols + j] = mat[i][j];
                }
            }
            for ( int i = cols * cols; i < rows * cols; ++i ) {
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
            for ( int i = 0; i < cols; ++i ) {
                for ( int j = 0; j < cols; ++j ) {
                    temp[i * cols + j] = mat[i][j];
                }
            }
        }
        for ( int i = 1; i < processes; ++i ) {
            MPI_Send(&rows, 1, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(&cols, 1, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(&offset, 1, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(temp + i * cols * offset, cols * offset, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
            MPI_Send(vector + i * offset, offset, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
        }
        part = new double[offset];
        for ( int n = 0; n < offset; ++n ) {
            part[n] = vector[n];
        }
        matrix = new double[offset * cols];
        for ( int i = 0; i < offset; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                matrix[i * cols + j] = temp[i * cols + j];
            }
        }
    }
    else{
        MPI_Recv(&rows, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        MPI_Recv(&cols, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        MPI_Recv(&offset, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        matrix = new double[offset * cols];
        MPI_Recv(matrix, offset * cols, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        part = new double[offset];
        MPI_Recv(part, offset, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
    }
    vector = new double[rows];
    for ( int i = 0; i < offset; ++i ) {
        vector[rank * offset + i] = part[i];
    }
    for ( int i = 0; i < processes; ++i ) {
        if(rank != i){
            MPI_Send(part, offset, MPI_DOUBLE, i, rank, MPI_COMM_WORLD);
        }
    }
    for ( int l = 0; l < processes - 1; ++l ) {
        MPI_Status status;
        MPI_Recv(part, offset, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        for ( int i = 0; i < offset; ++i ) {
            vector[status.MPI_TAG * offset + i] = part[i];
        }
    }
    double* result = new double[offset];
    for ( int i = 0; i < offset; ++i ) {
        result[i] = 0;
        for ( int j = 0; j < cols; ++j ) {
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
    if(rank == MASTER){
        for ( int i = 0; i < offset; ++i ) {
            vector[i] = result[i];
        }
        for ( int i = 0; i < processes - 1; ++i ) {
            MPI_Status status;
            MPI_Recv(result, offset, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            for ( int j = 0; j < offset; ++j ) {
                vector[status.MPI_TAG * offset + j] = result[j];
            }
        }
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], vector, cols,
                                chrono::duration<double, milli>( end - start ).count());
    }
    else{
        MPI_Send(result, offset, MPI_DOUBLE, MASTER, rank, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}