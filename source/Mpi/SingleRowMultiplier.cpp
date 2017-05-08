//
// Created by ojabassini on 5/7/17.
//

#include <Mpi/SingleRowMultiplier.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Mpi {

    SingleRowMultiplier::SingleRowMultiplier( std::string file_path ) : MatrixMultiplier( file_path ) {

    }

    void SingleRowMultiplier::multiply( std::string result_file_path ) {
        ifstream file;
        file.open( file_path );
        string line;
        int size = 0;
        while ( getline( file, line )) {
            if ( line != "" )
                size++;
        }
        system((string( "mpirun -np " ) + to_string( size - 3 ) + " ../../bin/mpi_single_row " + file_path + " " +
                result_file_path).c_str());
    }

    string SingleRowMultiplier::multiply( bool justTime ) {
        string temp = "/tmp/temp.txt";
        this->multiply(temp);
        ifstream file;
        string result = "", line;
        file.close();
        file.open( temp );
        std::vector<string> lines;
        while ( std::getline( file, line )) {
            lines.push_back( line );
        }
        if ( justTime )
            return lines[lines.size() - 2];
        for_each( lines.begin(), lines.end(), [ & ]( string l ) { result += line + "\n"; } );
        return result;
    }
}