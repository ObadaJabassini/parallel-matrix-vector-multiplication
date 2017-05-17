#include <iostream>
#include <memory>
#include <chrono>
#include <DataHandler/TextDataReader.h>
#include <DataHandler/ResultTextDataWriter.h>
#include <mpi.h>

using namespace std;
using namespace DataHandler;

int main(int argc, char** argv){
    MPI_Init( &argc, &argv );
    const int MASTER = 0;
    int rank, offset, processes, rows, cols;
    double** matrix, *vector;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank );
    MPI_Comm_size(MPI_COMM_WORLD, &processes );
    auto start = chrono::steady_clock::now();
    if(rank == MASTER){
        offset = stoi(argv[3]);
        auto reader = make_shared<TextDataReader>();
        rows = reader->read( argv[1],
                             matrix,
                             vector );
        start = chrono::steady_clock::now();
        cols = rows;
        if(cols % offset != 0){
            cols = rows + (offset - cols % offset);
            auto temp = new double*[rows];
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
        for ( int i = 1; i < processes; ++i ) {
            MPI_Send(&rows, 1, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(&cols, 1, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(&offset, 1, MPI_INT, i, i, MPI_COMM_WORLD);
        }
    }
    else{
        MPI_Recv(&rows, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        MPI_Recv(&cols, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        MPI_Recv(&offset, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
    }
    double* rec = new double[rows * offset + offset];
    if(rank == MASTER){
        double* scatter_data = new double[rows * cols + cols];
        for ( int j = 0; j < cols; ++j ) {
            for ( int i = 0; i < rows; ++i ) {
                scatter_data[j * (rows + 1) + i] = matrix[i][j];
            }
            scatter_data[(j + 1) * rows + j] = vector[j];
        }
        MPI_Scatter(scatter_data, rows * offset + offset, MPI_DOUBLE, rec, rows * offset + offset, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    else{
        MPI_Scatter(NULL, rows * offset + offset, MPI_DOUBLE, rec, rows * offset + offset, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    vector = new double[cols];
    for ( int k = 0; k < cols; ++k ) {
        vector[k] = 0;
        for ( int i = 0; i < rows * offset; i += rows + 1 ) {
            vector[k] += rec[i + k] * rec[i + rows];
        }
    }
    double* result = new double[cols];
    MPI_Reduce(vector, result, cols, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
    if(rank == MASTER){
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], result, rows, chrono::duration<double, milli>( end - start ).count());
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}