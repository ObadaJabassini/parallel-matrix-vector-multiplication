#include <Mpi/MultipleColumnMultiplier.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>

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
        system((string( "mpirun -n " ) + to_string( num ) + " /home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/mpi_multiple_columns " + file_path + " " +
                result_file_path + " " + std::to_string(this->cols)).c_str());
    }
}