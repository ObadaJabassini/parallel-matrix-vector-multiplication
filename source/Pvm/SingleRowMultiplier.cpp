
#include <iostream>
#include <Pvm/SingleRowMultiplier.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


SingleRowMultiplier::SingleRowMultiplier(std::string file_path) : MatrixMultiplier(file_path) {

}

void SingleRowMultiplier::multiply(std::string result_file_path) {
    system(("../../bin/single_row " + file_path + " " + result_file_path).c_str());
}

string SingleRowMultiplier::multiply(bool justTime) {
    string temp = "/tmp/temp.txt";
    system(("../../bin/single_row " + file_path + " " + temp).c_str());
    string result = "";
    ifstream file;
    file.open(temp);
    std::string line;
    std::vector<string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    if(justTime)
        return lines[lines.size() - 2];
    for_each(lines.begin(), lines.end(), [&](string l){result += line + "\n";});
    return result;
}

