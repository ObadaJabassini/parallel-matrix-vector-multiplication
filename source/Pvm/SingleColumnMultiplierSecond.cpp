
#include <Pvm/SingleColumnMultiplierSecond.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Pvm {

    SingleColumnMultiplierSecond::SingleColumnMultiplierSecond( std::string file_path ) : MatrixMultiplier(file_path){

    }

    void SingleColumnMultiplierSecond::multiply( std::string result_file_path ) {
        system(("/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_single_column_second " + file_path + " " + result_file_path).c_str());
    }

}