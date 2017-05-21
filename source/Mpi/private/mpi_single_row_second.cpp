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
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double* row = new double[size], *vector = new double[size], element;
    auto start = chrono::steady_clock::now();
    if(rank == MASTER){
        double** matrix,*vector;
        auto reader = make_shared<TextDataReader>();
        reader->read( argv[1],
                      matrix,
                      vector );
        start = chrono::steady_clock::now();
        double* temp = new double[size * size];
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                temp[i * size + j] = matrix[i][j];
            }
        }
        MPI_Scatter(temp, size, MPI_DOUBLE, row, size, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
        MPI_Scatter(vector, 1, MPI_DOUBLE, &element, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    else{
        MPI_Scatter(NULL, size, MPI_DOUBLE, row, size, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
        MPI_Scatter(NULL, 1, MPI_DOUBLE, &element, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    MPI_Allgather(&element, 1, MPI_DOUBLE, vector, 1, MPI_DOUBLE, MPI_COMM_WORLD);

    double result = 0;
    for ( int i = 0; i < size; ++i ) {
        result += vector[i] * row[i];
    }
    if(rank == MASTER){
        MPI_Gather(&result, 1, MPI_DOUBLE, vector, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], vector, size, chrono::duration<double, milli>( end - start ).count());
    }
    else{
        MPI_Gather(&result, 1, MPI_DOUBLE, NULL, size, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
