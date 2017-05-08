
#ifndef PROJECT_BENCHMARKER_H
#define PROJECT_BENCHMARKER_H

#include <Serial/MatrixMultiplier.h>
#include <vector>

namespace Performance {

    class Benchmarker {
    private:
        std::vector<MatrixMultiplier*> multipliers;
    public:
        Benchmarker( std::vector<MatrixMultiplier*> multipliers );

        std::vector<double> benchmark();

        std::vector<double> measure();

        void setMultiplier( std::vector<MatrixMultiplier*> multipliers );
    };

}
#endif //PROJECT_BENCHMARKER_H
