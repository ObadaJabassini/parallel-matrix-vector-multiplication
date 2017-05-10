#include <Performance/Benchmarker.h>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <iostream>

namespace Performance {

    Benchmarker::Benchmarker( std::vector<MatrixMultiplier*> multipliers ) {
        this->multipliers = multipliers;
    }

    std::pair<std::vector<double>, std::string> Benchmarker::benchmark() {
        auto len = this->multipliers.size();
        std::vector<double> times;
        auto t = QString::fromStdString(multipliers[0]->multiply( false));
        auto t1 = t.split("\n");
        times.push_back(t1[1].trimmed().toDouble());
        for ( int i = 1; i < len; ++i ) {
            times.push_back( std::stod( multipliers[i]->multiply( true )));
        }
        return std::make_pair(times, t1[0].trimmed().toStdString());
    }

    std::pair<std::vector<double>, std::string> Benchmarker::measure() {
        return this->benchmark();
    }

    void Benchmarker::setMultiplier( std::vector<MatrixMultiplier*> multipliers ) {
        this->multipliers = multipliers;
    }

}