

#include <Pvm/MultipleRowMultiplier.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

namespace Pvm {


    MultipleRowMultiplier::MultipleRowMultiplier( std::string file_path, int rows ) : MatrixMultiplier( file_path ) {
        this->rows = rows;
    }

    void MultipleRowMultiplier::multiply( std::string result_file_path ) {
        system(("/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_multiple_rows " + file_path + " " + std::to_string( rows ) + " " +
                result_file_path).c_str());
    }

}