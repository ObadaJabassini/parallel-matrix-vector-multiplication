#include <iostream>
#include <memory>
#include <RandomGenerator/NormalRandomGenerator.h>
#include <DataHandler/TextDataReader.h>
#include <RandomGenerator/UniformRandomGenerator.h>
#include <Mpi/SingleRowMultiplier.h>
#include <Performance/Benchmarker.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QApplication>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QObject>
#include <Ui/mainwindow.h>

using namespace std;
using namespace Generator;
using namespace DataHandler;
using namespace Mpi;
using namespace Performance;

int main(int argc, char** argv) {
    QApplication app (argc, argv);
    QFile f("../qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    auto window = make_shared<MainWindow>();
    window->show();
    return app.exec();
}

#include "main.moc"