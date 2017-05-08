#include <iostream>
#include <memory>
#include <RandomGenerator/NormalRandomGenerator.h>
#include <DataHandler/TextDataReader.h>
#include <RandomGenerator/UniformRandomGenerator.h>
#include <Mpi/SingleRowMultiplier.h>
#include <Performance/Benchmarker.h>
#include <qt5/QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QApplication>

using namespace std;
using namespace Generator;
using namespace DataHandler;
using namespace Mpi;
using namespace Performance;

int main(int argc, char** argv) {
    QApplication app (argc, argv);
    auto window = new QWidget();
    QPushButton* button = new QPushButton("hi", window);
    window->show();
    return app.exec();
}