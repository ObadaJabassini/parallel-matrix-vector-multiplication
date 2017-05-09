//
// Created by obada on 5/1/17.
//

#include <Serial/MatrixMultiplier.h>
#include <Serial/SerialMatrixMultiplier.h>
#include <Pvm/SingleRowMultiplier.h>
#include <Pvm/SingleColumnMultiplier.h>
#include <Pvm/MultipleRowMultiplier.h>
#include <Pvm/MultipleColumnMultiplier.h>
#include <include/Pvm/MultipleColumnMultiplier.h>
#include <include/Mpi/MultipleRowMultiplier.h>
#include <include/Mpi/SingleColumnMultiplier.h>
#include <include/Mpi/SingleRowMultiplier.h>
#include <include/Mpi/MultipleColumnMultiplier.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

MatrixMultiplier::MatrixMultiplier(std::string file_path) {
    this->file_path = file_path;
}

MatrixMultiplier* MatrixMultiplier::create( std::string name, std::string filePath) {
    if(name == "Serial"){
        return new SerialMatrixMultiplier(filePath);
    }
    if(name == "Pvm_Single_Row"){
        return new Pvm::SingleRowMultiplier(filePath);
    }
    if(name == "Pvm_Single_Column"){
        return new Pvm::SingleColumnMultiplier(filePath);
    }
    if(name == "Pvm_Multiple_Row"){
        return new Pvm::MultipleRowMultiplier(filePath);
    }
    if(name == "Pvm_Multiple_Column"){
        //return new Pvm::MultipleColumnMultiplier(filePath);
    }
    if(name == "Mpi_Single_Row"){
        //return new Mpi::SingleRowMultiplier(filePath);
    }
    if(name == "Mpi_Single_Column"){
        //return new Mpi::SingleColumnMultiplier(filePath);
    }
    if(name == "Mpi_Multiple_Row"){
        return new Mpi::MultipleRowMultiplier(filePath);
    }
    if(name == "Mpi_Multiple_Column"){
        //return new Mpi::MultipleColumnMultiplier(filePath);
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
    for_each( lines.begin(), lines.end(), [ & ]( string l ) { result += line + "\n"; } );
    return result;
}
