
#include <DataHandler/ResultTextDataWriter.h>
#include <fstream>

using namespace std;
namespace DataHandler {

    void ResultTextDataWriter::write( std::string file_path, double* vec, int size, double time ) {
        ofstream file;
        file.open( file_path );
        file << "vector:" << endl;
        for ( int k = 0; k < size; ++k ) {
            file << vec[k];
            if( k == size - 1)
                file << endl;
            else
                file << " ";
        }
        file << "time taken:" << endl;
        file << time;
        file.close();
    }

}