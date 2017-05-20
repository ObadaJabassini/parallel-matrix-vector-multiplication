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
    double* row = new double[size];
    double element;
    auto start = chrono::steady_clock::now();
    if ( rank == MASTER ) {
        double** matrix,*vector;
        auto reader = make_shared<TextDataReader>();
        reader->read( argv[1],
                      matrix,
                      vector );
        start = chrono::steady_clock::now();
        for ( int i = 1; i < size; ++i ) {
            MPI_Send(matrix[i], size, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
            MPI_Send(&vector[i], 1, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
        }
        row = matrix[0];
        element = vector[0];
        delete vector;
    }
    else{
        MPI_Recv(row, size, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        MPI_Recv(&element, 1, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
    }
    double result = row[rank] * element;
    for ( int i = 0; i < size; ++i ) {
        if(i != rank){
            MPI_Send(&element, 1, MPI_DOUBLE, i, rank, MPI_COMM_WORLD);
        }
    }
    for ( int i = 0; i < size - 1; ++i ) {
        MPI_Status status;
        MPI_Recv(&element, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        result += row[status.MPI_TAG] * element;
    }
    if(rank == MASTER){
        double* res = new double[size];
        res[0] = result;
        for ( int i = 0; i < size - 1; ++i ) {
            MPI_Status status;
            MPI_Recv(&element, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            res[status.MPI_TAG] = element;
        }
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], res, size, chrono::duration<double, milli>( end - start ).count());
    }
    else{
        MPI_Send(&result, 1, MPI_DOUBLE, MASTER, rank, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    delete row;
}