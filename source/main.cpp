#include <iostream>
#include <memory>
#include <DataHandler/TextDataReader.h>
#include <Serial/SerialMatrixMultiplier.h>

using namespace std;

int main(int argc, char** argv) {
    string input  = "/home/ojabassini/data.txt",
           output = "/home/ojabassini/results.txt";
    auto multiplier = make_shared<SerialMatrixMultiplier>(input);
    multiplier->multiply(output);
    return 0;
}