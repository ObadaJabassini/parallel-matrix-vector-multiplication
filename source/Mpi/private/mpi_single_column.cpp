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
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank );
    MPI_Comm_size(MPI_COMM_WORLD, &size );
    auto start = chrono::steady_clock::now();
    double* vector = new double[size + 1];
    if ( rank == MASTER ) {
        auto reader = make_shared<TextDataReader>();
        double** matrix, *temp;
        reader->read( argv[1],
                      matrix,
                      temp );
        start = chrono::steady_clock::now();
        auto scatterData = new double[size * size + size];
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                scatterData[i * (size + 1) + j] = matrix[j][i];
            }
            scatterData[(i + 1) * size + i] = temp[i];
        }
        MPI_Scatter(scatterData, size + 1, MPI_DOUBLE, vector, size + 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    else{
        MPI_Scatter(NULL, size + 1, MPI_DOUBLE, vector, size + 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    }
    for ( int i = 0; i < size; ++i ) {
        vector[i] *= vector[size];
    }
    auto result = new double[size];
    MPI_Reduce(vector, result, size, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
    if(rank == MASTER){
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], result, size, chrono::duration<double, milli>( end - start ).count());
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}