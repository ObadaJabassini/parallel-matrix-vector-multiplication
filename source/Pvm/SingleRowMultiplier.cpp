
#include <iostream>
#include "../../include/Pvm/SingleRowMultiplier.h"
#include <string>

using namespace std;


SingleRowMultiplier::SingleRowMultiplier(std::string file_path) : MatrixMultiplier(file_path) {

}

void SingleRowMultiplier::multiply(std::string result_file_path) {
    system(("../../bin/single_row " + file_path + " " + result_file_path).c_str());
}
