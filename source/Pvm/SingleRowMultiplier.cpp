
#include <iostream>
#include <Pvm/SingleRowMultiplier.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Pvm {

    SingleRowMultiplier::SingleRowMultiplier( std::string file_path ) : MatrixMultiplier( file_path ) {

    }

    void SingleRowMultiplier::multiply( std::string result_file_path ) {
        system(("/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_single_row " + file_path + " " + result_file_path).c_str());
    }

}