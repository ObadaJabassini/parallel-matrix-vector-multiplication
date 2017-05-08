//
// Created by obada on 5/1/17.
//

#include <Pvm/SingleColumnMultiplier.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Pvm {


    SingleColumnMultiplier::SingleColumnMultiplier( std::string file_path )
            : MatrixMultiplier( file_path ) {

    }

    void SingleColumnMultiplier::multiply( std::string result_file_path ) {
        system(("/home/ojabassini/CLionProjects/bin/pvm_single_column " + file_path + " " + result_file_path).c_str());
    }


    string SingleColumnMultiplier::multiply( bool justTime ) {
        string temp = "/tmp/temp.txt";
        system(("/home/ojabassini/CLionProjects/bin/pvm_single_column " + file_path + " " + temp).c_str());
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