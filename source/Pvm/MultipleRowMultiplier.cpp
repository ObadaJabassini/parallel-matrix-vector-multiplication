

#include <Pvm/MultipleRowMultiplier.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

namespace Pvm {


    MultipleRowMultiplier::MultipleRowMultiplier( std::string file_path, int rows ) : MatrixMultiplier( file_path ) {
        this->rows = rows;
    }

    void MultipleRowMultiplier::multiply( std::string result_file_path ) {
        system(("/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_multiple_rows " + file_path + " " + std::to_string( rows ) + " " +
                result_file_path).c_str());
    }

    string MultipleRowMultiplier::multiply( bool justTime ) {
        string temp = "/tmp/temp.txt";
        system(("/home/ojabassini/CLionProjects/parallel-matrix-vector-multiplication/bin/pvm_multiple_rows " + file_path + " " + temp).c_str());
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