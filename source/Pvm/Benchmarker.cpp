#include <Performance/Benchmarker.h>

Benchmarker::Benchmarker( std::vector<MatrixMultiplier*> multipliers ) {
    this->multipliers = multipliers;
}

std::vector<double> Benchmarker::benchmark() {
    auto len = this->multipliers.size();
    std::vector<double> times;
    for ( int i = 0; i < len; ++i ) {
        times.push_back(std::stod(multipliers[i]->multiply(true)));
    }
    return times;
}

std::vector<double> Benchmarker::measure() {
    return this->benchmark();
}

void Benchmarker::setMultiplier( std::vector<MatrixMultiplier*> multipliers ) {
    this->multipliers = multipliers;
}