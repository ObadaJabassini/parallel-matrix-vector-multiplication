#include "Ui/mainwindow.h"
#include <iostream>
#include <DataHandler/RandomDataWriter.h>
#include <RandomGenerator/RandomGenerator.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include "ui_mainwindow.h"
#include <memory>
#include <QtWidgets/QFileDialog>
#include <RandomGenerator/UniformRandomGenerator.h>
#include <RandomGenerator/NormalRandomGenerator.h>
#include <Performance/ResultWriter.h>
#include <Performance/Benchmarker.h>
#include <include/Ui/dialog.h>
#include <include/DataHandler/TextDataWriter.h>

using namespace std;
using namespace DataHandler;
using namespace Generator;
using namespace Performance;

MainWindow::MainWindow( QWidget* parent ) :
        QMainWindow( parent ) {
    ui = new Ui::MainWindow();
    ui->setupUi( this );
    QStringListModel* model = new QStringListModel( this ),
            * model1 = new QStringListModel( this );
    QStringList list;
    list << "Uniform" << "Normal" << "Rubbish";
    model->setStringList( list );
    ui->distBox->setModel( model );
    QStringList list1;
    list1 << "Serial" << "Pvm_Single_Row" << "Pvm_Multiple_Row" << "Pvm_Single_Column" << "Pvm_Multiple_Column"
          << "Mpi_Single_Row" << "Mpi_Multiple_Row" << "Mpi_Single_Column" << "Mpi_Multiple_Column";
    model1->setStringList( list1 );
    ui->choiceBox->setModel( model1 );
    initEvents();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initEvents() {
    QObject::connect( ui->generateButton, SIGNAL( clicked( bool )), this, SLOT( generate()));
    QObject::connect( ui->insertButton, SIGNAL( clicked( bool )), this, SLOT( insert()));
    QObject::connect( ui->addButton, SIGNAL( clicked( bool )), this, SLOT( addItem()));
    QObject::connect( ui->removeButton, SIGNAL( clicked( bool )), this, SLOT( removeItem()));
    QObject::connect( ui->loadButton, SIGNAL( clicked( bool )), this, SLOT( loadButton()));
    QObject::connect( ui->benchmarkButton, SIGNAL( clicked( bool )), this, SLOT( benchmark()));
}

void MainWindow::generate() {
    int size = ui->dimensionBox->value();
    QString dist = ui->distBox->currentText();
    if ( size <= 2 ) {
        return;
    }
    QString path = QFileDialog::getOpenFileName( this, tr( "Select Your file:" ));
    auto writer = make_shared<RandomDataWriter>();
    RandomGenerator* generator;
    if ( dist.toStdString() == "Uniform" ) {
        generator = new UniformRandomGenerator();
    } else {
        generator = new NormalRandomGenerator();
    }
    writer->write( path.toStdString(), generator, size );
    delete generator;
}


void MainWindow::addItem() {
    auto len = ui->listWidget->count();
    for ( int i = 0; i < len; ++i ) {
        if ( ui->choiceBox->currentText() == ui->listWidget->item( i )->text()) {
            return;
        }
    }
    ui->listWidget->addItem( ui->choiceBox->currentText());
}

void MainWindow::removeItem() {
    qDeleteAll( ui->listWidget->selectedItems());
}

void MainWindow::benchmark() {
    string resultFilePath = QFileDialog::getOpenFileName( this, tr( "Select Your file:" )).toStdString();
    vector<MatrixMultiplier*> multipliers;
    vector<string> names;
    string filePath = this->filePath.toStdString();
    auto len = ui->listWidget->count();
    for ( int i = 0; i < len; ++i ) {
        string name = ui->listWidget->item( i )->text().toStdString();
        names.push_back( name );
        multipliers.push_back( MatrixMultiplier::create( name, filePath ));
    }
    auto benchmarker = new Benchmarker( multipliers );
    auto writer = new ResultWriter( benchmarker );
    writer->write( resultFilePath, names );
}

void MainWindow::loadButton() {
    filePath = QFileDialog::getOpenFileName( this, tr( "Select Your file:" ));
}

void MainWindow::insertData( QString matrix, QString vector ) {
    string filePath = QFileDialog::getOpenFileName( this, tr( "Select Your file:" )).toStdString();
    auto sp = vector.split(" ");
    auto ma = matrix.split("\n");
    double* vec, **mat;
    int size = sp.count();
    vec = new double[size];
    mat = new double*[size];
    for ( int i = 0; i < size; ++i ) {
        mat[i] = new double[size];
    }
    for ( int i = 0; i < size; ++i ) {
        vec[i] = std::stod(sp[i].toStdString());
    }
    for ( int i = 0; i < size; ++i ) {
        auto temp = ma[i].split(" ");
        for ( int j = 0; j < size; ++j ) {
            mat[i][j] = std::stod(temp[j].toStdString());
        }
    }
    auto writer = make_shared<TextDataWriter>();
    writer->write(filePath, mat, vec, size);
}

void MainWindow::insert() {
    auto dialog = new Dialog();
    QObject::connect(dialog, SIGNAL(getData(QString, QString)), this, SLOT(insertData(QString, QString)));
    dialog->exec();
    delete dialog;
}



#include "mainwindow.moc"