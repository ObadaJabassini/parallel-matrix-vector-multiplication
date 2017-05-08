#include <iostream>
#include <memory>
#include <RandomGenerator/NormalRandomGenerator.h>
#include <DataHandler/TextDataReader.h>
#include <RandomGenerator/UniformRandomGenerator.h>
#include <Mpi/SingleRowMultiplier.h>
#include <Pvm/SingleRowMultiplier.h>

using namespace std;
using namespace Generator;
using namespace DataHandler;
using namespace Mpi;


int main(int argc, char** argv) {
//    int size = 5;
//    double* vector = new double[size];
//    generator->generate(vector, size);
//    for ( int i = 0; i < size; ++i ) {
//        cout << vector[i] << " ";
//    }
    auto mult = new SingleRowMultiplier("/home/ojabassini/data.txt");
    mult->multiply(string("/home/ojabassini/results.txt"));
    return 0;
}