//
// Created by obada on 5/2/17.
//

#include <DataHandler/RandomDataWriter.h>
#include <fstream>

using namespace std;

namespace DataHandler {

    string RandomDataWriter::write( string file_path, Generator::RandomGenerator* generator, int size ) {
        ofstream file;
        file.open( file_path );
        double** matrix = new double* [size];
        for ( int i = 0; i < size; ++i ) {
            matrix[i] = new double[size];
        }
        generator->generate( matrix, size, size );
        double* vector = new double[size];
        generator->generate( vector, size );
        string res = "";
        res += "matrix:\n";
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                res += std::to_string( matrix[i][j] );
                if ( j == size - 1 )
                    res += "\n";
                else {
                    res += " ";
                }
            }
        }
        res += "vector:\n";
        for ( int k = 0; k < size; ++k ) {
            res += std::to_string(vector[k]);
            if ( k != size - 1 )
                res += " ";
        }
        file << res;
        file.close();
        return res;
    }

}