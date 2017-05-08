#include <Performance/ResultWriter.h>
#include <Performance/Benchmarker.h>
#include <fstream>

namespace Performance {

    ResultWriter::ResultWriter( Benchmarker* benchmarker ) {
        this->benchmarker = benchmarker;
    }

    void ResultWriter::write( std::string file_path, std::vector<std::string> names ) {
        std::ofstream file;
        file.open( file_path );
        auto times = benchmarker->benchmark();
        auto len = times.size();
        for ( int i = 0; i < len; ++i ) {
            file << names[i] << " " << std::to_string( times[i] ) << std::endl;
        }
        file.close();
    }

}