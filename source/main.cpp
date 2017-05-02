#include <iostream>
#include <memory>
#include <string>
#include "../include/Serial/SerialMatrixMultiplier.h"
#include "../include/Serial/MatrixMultiplier.h"
#include <DataHandler/TextDataReader.h>

using namespace std;

int main(int argc, char** argv) {
    auto multiplier = make_shared<SerialMatrixMultiplier>(string("/home/obada/data.txt"));
    multiplier->multiply(string("/home/obada/results.txt"));
    return 0;
}