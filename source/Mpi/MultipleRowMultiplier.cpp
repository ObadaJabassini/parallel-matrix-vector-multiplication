#include <Mpi/MultipleRowMultiplier.h>
#include <string>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

namespace Mpi {
    MultipleRowMultiplier::MultipleRowMultiplier( std::string file_path, int rows ) : MatrixMultiplier( file_path ) {
        this->rows = rows;
    }
    void MultipleRowMultiplier::multiply( std::string result_file_path ) {
        ifstream file;
        file.open( file_path );
        string line;
        int size = 0;
        while ( getline( file, line )) {
            if ( line != "" )
                size++;
        }
        int num = ( int ) std::ceil( size / this->rows);
        system((string( "mpirun -np " ) + to_string( num ) + " /home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/mpi_multiple_rows " + file_path + " " +
                result_file_path + " " + std::to_string(this->rows)).c_str());
    }
}