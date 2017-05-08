
#include <DataHandler/TextDataWriter.h>
#include <fstream>

using namespace std;
namespace DataHandler {


    void TextDataWriter::write( std::string file_path, double* vec, int size, double time ) {
        ofstream file;
        file.open( file_path );
        file << "vector:" << endl;
        for ( int k = 0; k < size; ++k ) {
            file << vec[k] << (k == size - 1 ? "\n" : ",");
        }
        file << "time taken:" << endl;
        file << time << endl;
        file.close();
    }

}