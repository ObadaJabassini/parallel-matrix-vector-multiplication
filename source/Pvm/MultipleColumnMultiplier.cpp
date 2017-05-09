#include <Pvm/MultipleColumnMultiplier.h>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

namespace Pvm {

    MultipleColumnMultiplier::MultipleColumnMultiplier( std::string file_path, int cols ) : MatrixMultiplier(
            file_path ) {
        this->cols = cols;
    }

    void MultipleColumnMultiplier::multiply( std::string result_file_path ) {
        system(("/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_multiple_columns " + file_path + " " + std::to_string( cols ) + " " +
                result_file_path).c_str());
    }
}