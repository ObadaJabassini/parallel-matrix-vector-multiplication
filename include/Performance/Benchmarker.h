
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

        std::pair<std::vector<double>, std::string> benchmark();

        std::pair<std::vector<double>, std::string> measure();

        void setMultiplier( std::vector<MatrixMultiplier*> multipliers );
    };

}
#endif //PROJECT_BENCHMARKER_H
