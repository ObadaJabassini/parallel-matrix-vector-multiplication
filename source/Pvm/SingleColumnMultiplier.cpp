//
// Created by obada on 5/1/17.
//

#include <Pvm/SingleColumnMultiplier.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Pvm {


    SingleColumnMultiplier::SingleColumnMultiplier( std::string file_path )
            : MatrixMultiplier( file_path ) {

    }

    void SingleColumnMultiplier::multiply( std::string result_file_path ) {
        system(("/home/ojabassini/CLionProjects/bin/pvm_single_column " + file_path + " " + result_file_path).c_str());
    }

}