#include <DataHandler/TextDataWriter.h>

namespace DataHandler{
    void TextDataWriter::write( string filePath, double** matrix, double* vector, int size ) {
        ofstream file;
        file.open(filePath);
        file << "matrix:" << endl;
        for ( int i = 0; i < size; ++i ) {
            for ( int j = 0; j < size; ++j ) {
                file << matrix[i][j] << " ";
            }
            file << endl;
        }
        file << "vector:" << endl;
        for ( int i = 0; i < size; ++i ) {
            file << vector[i] << " ";
        }
        file.close();
    }
}