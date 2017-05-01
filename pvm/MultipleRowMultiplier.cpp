

#include "MultipleRowMultiplier.h"

MultipleRowMultiplier::MultipleRowMultiplier(const std::string& file_path, int rows) : MatrixMultiplier(file_path){
    this->rows = rows;
}

void MultipleRowMultiplier::multiply(std::string result_file_path) {
    system("./multiple_rows " + file_path + " " + std::to_string(rows) + " " + result_file_path);
}

