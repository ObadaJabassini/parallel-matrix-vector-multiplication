//
// Created by obada on 5/1/17.
//

#include <Mpi/SingleColumnMultiplier.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Mpi {


    SingleColumnMultiplier::SingleColumnMultiplier( std::string file_path )
            : MatrixMultiplier( file_path ) {

    }

    void SingleColumnMultiplier::multiply( std::string result_file_path ) {
        ifstream file;
        file.open(file_path);
        string line;
        int size = 0;
        while(getline(file, line)){
            if(line != "")
                size++;
        }
        system((string("mpirun -np ") + to_string(size - 3) + " /home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/mpi_single_column " + file_path + " " + result_file_path).c_str());
    }

}