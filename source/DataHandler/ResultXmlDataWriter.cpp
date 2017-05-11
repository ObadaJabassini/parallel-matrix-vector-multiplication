
#include <DataHandler/ResultXmlDataWriter.h>
#include <fstream>
#include <ThirdParty/pugiconfig.hpp>
#include <ThirdParty/pugixml.hpp>

using namespace std;
using namespace pugi;

namespace DataHandler {

    void ResultXmlDataWriter::write( std::string file_path, double* vec, int size, double time ) {
        xml_document document;
        xml_node resultNode, timeNode, vectorNode;
        timeNode.set_name("Time");
        timeNode.set_value(std::to_string(time).c_str());
        vectorNode.set_name("Vector");
        for ( int i = 0; i < size; ++i ) {
            xml_node node;
            node.set_name("Element");
            node.set_value(std::to_string(vec[i]).c_str());
            vectorNode.append_copy(node);
        }
        resultNode.set_name("Result");
        resultNode.append_copy(vectorNode);
        resultNode.append_copy(timeNode);
        document.append_copy(resultNode);
        document.save_file(file_path.c_str());
    }
}