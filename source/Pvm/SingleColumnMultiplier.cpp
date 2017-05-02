//
// Created by obada on 5/1/17.
//

#include "../../include/Pvm/SingleColumnMultiplier.h"

SingleColumnMultiplier::SingleColumnMultiplier(std::string file_path)
        : MatrixMultiplier(file_path) {

}

void SingleColumnMultiplier::multiply(std::string result_file_path) {
    system("./single_column " + file_path + " " + result_file_path);
}
