//
// Created by obada on 5/1/17.
//

#include <Serial/MatrixMultiplier.h>
#include <Serial/SerialMatrixMultiplier.h>
#include <Pvm/SingleRowMultiplier.h>
#include <Pvm/SingleColumnMultiplier.h>
#include <Pvm/MultipleRowMultiplier.h>
#include <Pvm/MultipleColumnMultiplier.h>
#include <Pvm/MultipleColumnMultiplier.h>
#include <Mpi/MultipleRowMultiplier.h>
#include <Mpi/SingleColumnMultiplier.h>
#include <Mpi/SingleRowMultiplier.h>
#include <Mpi/MultipleColumnMultiplier.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <Mpi/SingleColumnMultiplierSecond.h>
#include <Pvm/SingleColumnMultiplierSecond.h>

using namespace std;

MatrixMultiplier::MatrixMultiplier(std::string file_path) {
    this->file_path = file_path;
}

MatrixMultiplier* MatrixMultiplier::create( std::string name, std::string filePath, int offset) {
    if(name == "Serial"){
        return new SerialMatrixMultiplier(filePath);
    }
    if(name == "Pvm_Single_Row"){
        return new Pvm::SingleRowMultiplier(filePath);
    }
    if(name == "Pvm_Single_Column"){
        return new Pvm::SingleColumnMultiplier(filePath);
    }
    if(name == "Pvm_Single_Column_Second"){
        return new Pvm::SingleColumnMultiplierSecond(filePath);
    }
    if(name == "Pvm_Multiple_Row"){
        return new Pvm::MultipleRowMultiplier(filePath, offset);
    }
    if(name == "Pvm_Multiple_Column"){
        return new Pvm::MultipleColumnMultiplier(filePath, offset);
    }
    if(name == "Mpi_Single_Row"){
        return new Mpi::SingleRowMultiplier(filePath);
    }
    if(name == "Mpi_Single_Column"){
        return new Mpi::SingleColumnMultiplier(filePath);
    }
    if(name == "Mpi_Single_Column_Second"){
        return new Mpi::SingleColumnMultiplierSecond(filePath);
    }
    if(name == "Mpi_Multiple_Row"){
        return new Mpi::MultipleRowMultiplier(filePath, offset);
    }
    if(name == "Mpi_Multiple_Column"){
        return new Mpi::MultipleColumnMultiplier(filePath, offset);
    }
    return nullptr;
}

std::string MatrixMultiplier::multiply( bool justTime ) {
    string temp = "/tmp/temp.txt";
    this->multiply(temp);
    string result = "";
    ifstream file;
    file.open( temp );
    std::string line;
    std::vector<string> lines;
    while ( std::getline( file, line )) {
        lines.push_back( line );
    }
    if ( justTime )
        return lines[lines.size() - 1];
    return lines[1] + "\n" + lines[lines.size() - 1];
}
