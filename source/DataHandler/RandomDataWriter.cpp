//
// Created by obada on 5/2/17.
//

#include <DataHandler/RandomDataWriter.h>
#include <fstream>

using namespace std;

namespace DataHandler {

    void RandomDataWriter::write( string file_path, Generator::RandomGenerator* generator, int size ) {
        ofstream file;
        file.open( file_path );
        double** matrix = new double*[size];
        for ( int i = 0; i < size; ++i ) {
            matrix[i] = new double[size];
        }
        generator->generate( matrix, size, size );
        double* vector = new double[size];
        generator->generate( vector, size );
        file << "matrix:" << endl;
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                file << matrix[i][j];
                if ( j == size - 1 )
                    file << endl;
                else {
                    file << " ";
                }
            }
        }
        file << "vector:" << endl;
        for ( int k = 0; k < size; ++k ) {
            file << vector[k];
            if ( k != size - 1 )
                file << " ";
        }
        file.close();
    }

}