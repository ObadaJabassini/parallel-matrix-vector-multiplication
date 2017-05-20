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
    double* col, element;
    if ( rank == MASTER ) {
        double** matrix, *vector;
        auto reader = make_shared<TextDataReader>();
        reader->read( argv[1],
                      matrix,
                      vector );
        start = chrono::steady_clock::now();
        for ( int i = 1; i < size; ++i ) {
            double* buffer = new double[size + 1];
            for ( int j = 0; j < size; ++j ) {
                buffer[j] = matrix[j][i];
            }
            buffer[size] = vector[i];
            MPI_Send( buffer, size + 1, MPI_DOUBLE, i, rank, MPI_COMM_WORLD);
        }
        element = vector[0];
        col = new double[size];
        for ( int j = 0; j < size; ++j ) {
            col[j] = matrix[j][0];
        }
        delete vector;
        for ( int i = 0; i < size; ++i ) {
            delete matrix[i];
        }
        delete matrix;
    } else {
        auto buffer = new double[size + 1];
        MPI_Recv( buffer, size + 1, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, NULL );
        element = buffer[size];
        col = new double[size];
        for ( int i = 0; i < size; ++i ) {
            col[i] = buffer[i];
        }
        delete buffer;
    }
    double* send;
    for ( int i = 0; i < size; ++i ) {
        if ( rank != i ) {
            send = new double[2];
            send[0] = col[i];
            send[1] = element;
            MPI_Send( send, 2, MPI_DOUBLE, i, rank, MPI_COMM_WORLD);
            delete send;
        }
    }
    double* rec;
    double result = col[rank] * element;
    for ( int i = 0; i < size - 1; ++i ) {
        rec = new double[2];
        MPI_Status status;
        MPI_Recv( rec, 2, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
        auto temp = status.MPI_TAG;
        result += rec[0] * rec[1];
        delete rec;
    }
    if ( rank == MASTER ) {
        double* res = new double[size];
        res[0] = result;
        for ( int i = 0; i < size - 1; ++i ) {
            MPI_Status status;
            MPI_Recv( &element, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
            res[status.MPI_TAG] = element;
        }
        auto end = chrono::steady_clock::now();
        ResultTextDataWriter().write( argv[2], res, size, chrono::duration<double, milli>( end - start ).count());
    } else {
        MPI_Send( &result, 1, MPI_DOUBLE, MASTER, rank, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    delete rec;
    delete col;
}