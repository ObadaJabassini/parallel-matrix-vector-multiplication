#include <Mpi/MultipleColumnMultiplier.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

namespace Mpi {

    MultipleColumnMultiplier::MultipleColumnMultiplier( std::string file_path, int cols ) : MatrixMultiplier(
            file_path ) {
        this->cols = cols;
    }

    void MultipleColumnMultiplier::multiply( std::string result_file_path ) {
        ifstream file;
        file.open( file_path );
        string line;
        int size = 0;
        while ( getline( file, line )) {
            if ( line != "" )
                size++;
        }
        int num = ( int ) std::ceil( size / this->cols);
        system((string( "mpirun -np " ) + to_string( num ) + " ../../bin/mpi_multiple_columns " + file_path + " " +
                result_file_path + " " + std::to_string(this->cols)).c_str());
    }

    std::string MultipleColumnMultiplier::multiply( bool justTime ) {
        string temp = "/tmp/temp.txt";
        this->multiply(temp);
        string result = "", line;
        ifstream file;
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