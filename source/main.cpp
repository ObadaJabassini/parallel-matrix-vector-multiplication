#include <iostream>
#include <memory>
#include <QtWidgets/QApplication>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <Ui/mainwindow.h>

using namespace std;

int main( int argc, char** argv ) {
    QApplication app( argc, argv );
    QFile f( "../qdarkstyle/style.qss" );
    if ( !f.exists()) {
        printf( "Unable to set stylesheet, file not found\n" );
    } else {
        f.open( QFile::ReadOnly | QFile::Text );
        QTextStream ts( &f );
        qApp->setStyleSheet( ts.readAll());
    }
    auto window = make_shared<MainWindow>();
    window->show();
    return app.exec();
}

#include "main.moc"