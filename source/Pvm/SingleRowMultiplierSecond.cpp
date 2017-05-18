
#include <iostream>
#include <Pvm/SingleRowMultiplierSecond.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Pvm {

    SingleRowMultiplierSecond::SingleRowMultiplierSecond( std::string file_path ) : MatrixMultiplier( file_path ) {

    }

    void SingleRowMultiplierSecond::multiply( std::string result_file_path ) {
        system(("/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_single_row_second " + file_path + " " + result_file_path).c_str());
    }

}