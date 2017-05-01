
#include <cstddef>
#include <iostream>
#include "SingleRowMultiplier.h"

using namespace std;


SingleRowMultiplier::SingleRowMultiplier(std::string file_path) : MatrixMultiplier(file_path) {

}

void SingleRowMultiplier::multiply(std::string result_file_path) {
    system("./single_row " + file_path + " " + result_file_path);
}
