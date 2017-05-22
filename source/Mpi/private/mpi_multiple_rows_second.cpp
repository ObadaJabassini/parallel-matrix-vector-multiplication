#include <iostream>
#include <memory>
#include <chrono>
#include <DataHandler/TextDataReader.h>
#include <DataHandler/ResultTextDataWriter.h>
#include <mpi.h>

using namespace std;
using namespace DataHandler;

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    const int MASTER = 0;
    int rows, cols, rank, offset;
    double* part, *matrix, *vector;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    auto start = chrono::steady_clock::now();
    if(rank == MASTER){
        offset = atoi( argv[3] );
        double* temp;
        double** mat;
        auto reader = make_shared<TextDataReader>();
        cols = reader->read( argv[1],
                             mat,
                             vector );
        start = chrono::steady_clock::now();
        rows = cols;
        if ( cols % offset != 0 ) {
            rows = cols + (offset - cols % offset);
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
        int* data = new int[3];
        data[0] = rows;
        data[1] = cols;
        data[2] = offset;
        MPI_Bcast(data, 3 , MPI_INT, MASTER, MPI_COMM_WORLD);
        matrix = new double[cols * offset];
        MPI_Scatter(temp, cols * offset, MPI_DOUBLE, matrix, cols * offset, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
        part = new double[offset];
        MPI_Scatter(vector, offset, MPI_DOUBLE, part, offset, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    else{
        int* data = new int[3];
        MPI_Bcast(data, 3 , MPI_INT, MASTER, MPI_COMM_WORLD);
        rows = data[0];
        cols = data[1];
        offset = data[2];
        matrix = new double[cols * offset];
        MPI_Scatter(NULL, cols * offset, MPI_DOUBLE, matrix, cols * offset, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
        part = new double[offset];
        MPI_Scatter(NULL, offset, MPI_DOUBLE, part, offset, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    vector = new double[rows];
    MPI_Allgather(part, offset, MPI_DOUBLE, vector, offset, MPI_DOUBLE, MPI_COMM_WORLD);
    double* result = new double[offset];
    for ( int i = 0; i < offset; ++i ) {
        result[i] = 0;
        for ( int j = 0; j < rows; ++j ) {
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
    if(rank == MASTER){
        MPI_Gather(result, offset, MPI_DOUBLE, vector, offset, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], vector, cols,
                                      chrono::duration<double, milli>( end - start ).count());
    }
    else{
        MPI_Gather(result, offset, MPI_DOUBLE, NULL, offset, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}