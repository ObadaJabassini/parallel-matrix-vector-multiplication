#include <Performance/ResultWriter.h>
#include <Performance/Benchmarker.h>
#include <fstream>

namespace Performance {

    ResultWriter::ResultWriter( Benchmarker* benchmarker ) {
        this->benchmarker = benchmarker;
    }

    std::pair<std::vector<double>, std::string> ResultWriter::write( std::string file_path, std::vector<std::string> names ) {
        std::ofstream file;
        file.open( file_path );
        auto temp = benchmarker->benchmark();
        auto times = temp.first;
        auto len = times.size();
        for ( int i = 0; i < len; ++i ) {
            file << names[i] << " " << std::to_string( times[i] ) << std::endl;
        }
        file.close();
        return temp;
    }

}