#include <Mpi/MultipleRowMultiplierSecond.h>
#include <string>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

namespace Mpi {
    MultipleRowMultiplierSecond::MultipleRowMultiplierSecond( std::string file_path, int rows ) : MatrixMultiplier( file_path ) {
        this->rows = rows;
    }
    void MultipleRowMultiplierSecond::multiply( std::string result_file_path ) {
        ifstream file;
        file.open( file_path );
        string line;
        int size = 0;
        while ( getline( file, line )) {
            if ( line != "" )
                size++;
        }
        int num = ( int ) std::ceil( size / this->rows);
        system((string( "mpirun -n " ) + to_string( num ) + " /home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/mpi_multiple_rows_second " + file_path + " " +
                result_file_path + " " + std::to_string(this->rows)).c_str());
    }
}