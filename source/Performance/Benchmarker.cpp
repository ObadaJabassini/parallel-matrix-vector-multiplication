#include <Performance/Benchmarker.h>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

namespace Performance {

    Benchmarker::Benchmarker( std::vector<MatrixMultiplier*> multipliers ) {
        this->multipliers = multipliers;
    }

    std::pair<std::vector<double>, std::string> Benchmarker::benchmark() {
        auto len = this->multipliers.size();
        std::vector<double> times( len );
        auto t = QString::fromStdString( multipliers[0]->multiply( false ));
        auto t1 = t.split( "\n" );
        times[0] = t1[1].toDouble();
        thread threads[len - 1];
        mutex lock;
        auto fun = [ & ]( MatrixMultiplier* multiplier, int index ) {
            //lock.lock();
            times[index] = std::stod( multipliers[index]->multiply( true ));
            //lock.unlock();
        };
        for ( int i = 1; i < len; ++i ) {
            threads[i - 1] = thread( fun, multipliers[i], i );
        }
        for ( auto& tt : threads ) {
            tt.join();
        }
        return std::make_pair( times, t1[0].toStdString());
    }

    std::pair<std::vector<double>, std::string> Benchmarker::measure() {
        return this->benchmark();
    }

    void Benchmarker::setMultiplier( std::vector<MatrixMultiplier*> multipliers ) {
        this->multipliers = multipliers;
    }

}