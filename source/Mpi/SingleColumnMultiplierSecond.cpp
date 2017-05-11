#include <Mpi/SingleColumnMultiplierSecond.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


namespace Mpi{

    SingleColumnMultiplierSecond::SingleColumnMultiplierSecond( std::string file_path )
            : MatrixMultiplier( file_path ) {

    }

    void SingleColumnMultiplierSecond::multiply( std::string result_file_path ) {
        ifstream file;
        file.open(file_path);
        string line;
        int size = 0;
        while(getline(file, line)){
            if(line != "")
                size++;
        }
        system((string("mpirun -n ") + to_string(size - 3) + " /home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/mpi_single_column_second " + file_path + " " + result_file_path).c_str());
    }
}