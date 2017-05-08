#include <iostream>
#include <memory>
#include <RandomGenerator/NormalRandomGenerator.h>
#include <DataHandler/TextDataReader.h>
#include <RandomGenerator/UniformRandomGenerator.h>
#include <Mpi/SingleRowMultiplier.h>
#include <Pvm/SingleRowMultiplier.h>
#include <Performance/Benchmarker.h>

using namespace std;
using namespace Generator;
using namespace DataHandler;
using namespace Mpi;
using namespace Performance;


int main(int argc, char** argv) {
//    int size = 5;
//    double* vector = new double[size];
//    generator->generate(vector, size);
//    for ( int i = 0; i < size; ++i ) {
//        cout << vector[i] << " ";
//    }
    auto gen = UniformRandomGenerator(1000, 100, 200);
    int size = 5;
    double* vector = new double[size];
    gen.generate(vector, size);
    for ( int i = 0; i < size; ++i ) {
        cout << vector[i] << " ";
    }
    return 0;
}