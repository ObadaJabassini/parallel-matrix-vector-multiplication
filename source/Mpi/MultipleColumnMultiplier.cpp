#include <Mpi/MultipleColumnMultiplier.h>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

namespace Mpi {

    MultipleColumnMultiplier::MultipleColumnMultiplier( std::string file_path, int cols ) : MatrixMultiplier(
            file_path ) {
        this->cols = cols;
    }

    void MultipleColumnMultiplier::multiply( std::string result_file_path ) {
        system(("../../bin/mpi_multiple_columns " + file_path + " " + std::to_string( cols ) + " " +
                result_file_path).c_str());
    }

    std::string MultipleColumnMultiplier::multiply( bool justTime ) {
        string temp = "/tmp/temp.txt";
        system(("../../bin/mpi_multiple_columns " + file_path + " " + temp).c_str());
        string result = "";
        ifstream file;
        file.open( temp );
        std::string line;
        std::vector<string> lines;
        while ( std::getline( file, line )) {
            lines.push_back( line );
        }
        if ( justTime )
            return lines[lines.size() - 2];
        for_each( lines.begin(), lines.end(), [ & ]( string l ) { result += line + "\n"; } );
        return result;
    }
}