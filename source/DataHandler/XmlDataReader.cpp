#include <DataHandler/XmlDataReader.h>
#include <ThirdParty/pugiconfig.hpp>
#include <ThirdParty/pugixml.hpp>

using namespace pugi;

namespace DataHandler{
    int XmlDataReader::read( string file_path, double**& mat, double*& vec ) {
        xml_document document;
        document.load(file_path.c_str());
        auto matrix = document.child("Matrix");
        auto vector = document.child("Vector");
        int size = 0;
        for (pugi::xml_node row = matrix.child("Row"); row; row = row.next_sibling("Row"))
        {
            ++size;
        }
        mat = new double*[size];
        for ( int i = 0; i < size; ++i ) {
            mat[i] = new double[size];
        }
        vec = new double[size];
        int i = 0;
        for (pugi::xml_node row = matrix.child("Row"); row; row = row.next_sibling("Row"))
        {
            int j = 0;
            for (pugi::xml_node element = row.child("Element"); element; element = element.next_sibling("Element"))
            {
                mat[i][j++] = stod(string(element.value()));
            }
            ++i;
        }
        i = 0;
        for (pugi::xml_node element = vector.child("Element"); element; element = element.next_sibling("Element")){
            vec[i++] = stod(string(element.value()));
        }
        return size;
    }
}
