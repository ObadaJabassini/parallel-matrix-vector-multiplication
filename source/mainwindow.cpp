#include <iostream>
#include <Ui/mainwindow.h>
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
#include <RandomGenerator/ExponentialRandomGenerator.h>
#include <Performance/ResultWriter.h>
#include <Performance/Benchmarker.h>
#include <Ui/offsetdialog.h>
#include <Ui/insertdialog.h>
#include <DataHandler/TextDataWriter.h>
#include <Ui/uniformdialog.h>
#include <QDialog>
#include <Ui/normaldialog.h>
#include <Ui/exponentialdialog.h>
#include <RandomGenerator/RubbishRandomGenerator.h>

using namespace std;
using namespace DataHandler;
using namespace Generator;
using namespace Performance;

MainWindow::MainWindow( QWidget* parent ) :
        QMainWindow( parent ) {
    ui = new Ui::MainWindow();
    ui->setupUi( this );
    setWindowTitle(QString::fromStdString("Project"));
    customPlot = ui->plotWidget;
    ui->tabWidget->setCurrentIndex(0);
    initCustomPlot();
    QStringListModel* model = new QStringListModel( this ),
            * model1 = new QStringListModel( this );
    QStringList list;
    list << "Uniform" << "Normal" << "Exponential" << "Rubbish";
    model->setStringList( list );
    ui->distBox->setModel( model );
    QStringList list1;
    list1 << "Serial" << "Pvm_Single_Row" << "Pvm_Multiple_Row" << "Pvm_Single_Column" << "Pvm_Single_Column_Second" << "Pvm_Multiple_Column"
          << "Mpi_Single_Row" << "Mpi_Multiple_Row" << "Mpi_Single_Column" << "Mpi_Single_Column_Second" << "Mpi_Multiple_Column";
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
    QString dist = ui->distBox->currentText();
    QDialog* dialog = nullptr;
    if ( dist.toStdString() == "Uniform" ) {
        dialog = new UniformDialog();
        dialog->setWindowTitle(QString::fromStdString("Select Your parameters:"));
        QObject::connect(dialog, SIGNAL(sendData(double, double)), this, SLOT(handleUniform(double, double)));
        dialog->exec();
    }
    else if(dist.toStdString() == "Exponential"){
        dialog = new ExponentialDialog();
        dialog->setWindowTitle(QString::fromStdString("Select Your parameters:"));
        QObject::connect(dialog, SIGNAL(sendData(double)), this, SLOT(handleExp(double)));
        dialog->exec();
    }
    else if(dist.toStdString() == "Normal"){
        dialog = new NormalDialog();
        dialog->setWindowTitle(QString::fromStdString("Select Your parameters:"));
        QObject::connect(dialog, SIGNAL(sendData(double, double)), this, SLOT(handleNormal(double, double)));
        dialog->exec();
    }
    else{
        generateData(new RubbishRandomGenerator());
    }
    delete dialog;
}


void MainWindow::addItem() {
    auto temp = ui->choiceBox->currentText();
    if(!temp.contains(QString::fromStdString("Multiple"))){
        auto len = ui->listWidget->count();
        for ( int i = 0; i < len; ++i ) {
            if ( temp == ui->listWidget->item( i )->text()) {
                auto message = new QMessageBox(this);
                message->setText("Already inserted");
                message->show();
                return;
            }
        }
        ui->listWidget->addItem(temp);
    }
    else{
        auto dialog = new OffsetDialog(this);
        dialog->setWindowTitle(QString::fromStdString("Your Offset"));
        QObject::connect(dialog, SIGNAL(sendData(int)), this, SLOT(addOffset(int)));
        dialog->exec();
        delete dialog;
    }
}

void MainWindow::removeItem() {
    auto items = ui->listWidget->selectedItems();
    auto len = this->offsets.count();
    for(auto& temp : items){
        if(temp->text().contains("Multiple")){
            for ( int i = 0; i < len; ++i ) {
                if(offsets[i].first == temp->text()){
                    offsets.remove(i);
                }
            }
        }
    }
    qDeleteAll(items);
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
    ui->resultEdit->setText(QString::fromStdString("matrix:\n") + matrix + QString::fromStdString("\nvector:\n") + vector);
    delete vec;
    for ( int i = 0; i < size; ++i ) {
        delete mat[i];
    }
    delete mat;
}

void MainWindow::insert() {
    auto dialog = new InsertDialog();
    dialog->setWindowTitle(QString::fromStdString("Your Data"));
    QObject::connect(dialog, SIGNAL(sendData(QString, QString)), this, SLOT(insertData(QString, QString)));
    dialog->exec();
    delete dialog;
}

void MainWindow::benchmark() {
    string resultFilePath = QFileDialog::getOpenFileName( this, tr( "Select Your file:" ), tr("/home/ojabassini")).toStdString();
    vector<MatrixMultiplier*> multipliers;
    vector<string> names;
    string filePath = this->filePath.toStdString();
    auto len = ui->listWidget->count();
    for ( int i = 0, j = 0; i < len; ++i ) {
        auto temp = ui->listWidget->item( i )->text();
        string name = temp.toStdString();
        names.push_back( name );
        if(temp.contains("Multiple")){
            auto t = temp.lastIndexOf(QString::fromStdString("_"));
            multipliers.push_back( MatrixMultiplier::create( name.substr( 0, ( unsigned long ) t ), filePath, offsets[j++].second));
        }
        else {
            multipliers.push_back( MatrixMultiplier::create( name, filePath ));
        }
    }
    auto benchmarker = new Benchmarker( multipliers );
    auto writer = new ResultWriter( benchmarker );
    auto data = writer->write( resultFilePath, names );
    QVector<double> ticks;
    QVector<QString> labels;
    auto size = names.size();
    for ( int i = 0; i < size; ++i ) {
        ticks << i + 1;
        labels << QString::fromStdString(names[i]);
    }
    QSharedPointer<QCPAxisTickerText> textTicker( new QCPAxisTickerText() );
    textTicker->addTicks( ticks, labels );
    customPlot->xAxis->setTicker( textTicker );
    QVector<double> timeData;
    auto first = data.first;
    auto len1 = first.size();
    for ( int i = 0; i < len1; ++i ) {
        timeData << first[i] * 10;
    }
    timeBar->setData( ticks, timeData );
    ui->resultEdit->setText(QString::fromStdString("vector:\n") + QString::fromStdString(data.second));
    delete writer;
    delete benchmarker;
    len1 = multipliers.size();
    for ( int i = 0; i < len1; ++i ) {
        delete multipliers[i];
    }
}

void MainWindow::initCustomPlot() {
    QLinearGradient gradient( 0, 0, 0, 400 );
    gradient.setColorAt( 0, QColor( 49, 54, 59 ));
    //gradient.setColorAt( 0.38, QColor( 105, 105, 105 ));
    gradient.setColorAt( 0.38, QColor( 49, 54, 59 ));
    gradient.setColorAt( 1, QColor( 49, 54, 59 ));
    customPlot->setBackground( QBrush( gradient ));
    customPlot->xAxis->setTickLabelRotation( 60 );
    customPlot->xAxis->setSubTicks( false );
    customPlot->xAxis->setTickLength( 0, 4 );
    customPlot->xAxis->setRange( 0, 8 );
    customPlot->xAxis->setBasePen( QPen( Qt::white ));
    customPlot->xAxis->setTickPen( QPen( Qt::white ));
    customPlot->xAxis->grid()->setVisible( true );
    customPlot->xAxis->grid()->setPen( QPen( QColor( 130, 130, 130 ), 0, Qt::DotLine ));
    customPlot->xAxis->setTickLabelColor( Qt::white );
    customPlot->xAxis->setLabelColor( Qt::white );
    customPlot->yAxis->setRange( 0, 12.1 );
    customPlot->yAxis->setPadding( 5 ); // a bit more space to the left border
    customPlot->yAxis->setLabel( "Time Consumed(Multiplied By 10 In Milliseconds)" );
    customPlot->yAxis->setBasePen( QPen( Qt::white ));
    customPlot->yAxis->setTickPen( QPen( Qt::white ));
    customPlot->yAxis->setSubTickPen( QPen( Qt::white ));
    customPlot->yAxis->grid()->setSubGridVisible( true );
    customPlot->yAxis->setTickLabelColor( Qt::white );
    customPlot->yAxis->setLabelColor( Qt::white );
    customPlot->yAxis->grid()->setPen( QPen( QColor( 130, 130, 130 ), 0, Qt::SolidLine ));
    customPlot->yAxis->grid()->setSubGridPen( QPen( QColor( 130, 130, 130 ), 0, Qt::DotLine ));
    customPlot->legend->setVisible( true );
    customPlot->axisRect()->insetLayout()->setInsetAlignment( 0, Qt::AlignTop | Qt::AlignHCenter );
    customPlot->legend->setBrush( QColor( 255, 255, 255, 100 ));
    customPlot->legend->setBorderPen( Qt::NoPen );
    customPlot->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
    timeBar = new QCPBars( customPlot->xAxis, customPlot->yAxis );
    timeBar->setAntialiased( false );
    timeBar->setStackingGap( 1 );
    timeBar->setName( "Time" );
    //auto temp = QColor( 111, 9, 176 );
    auto temp = QColor( 20, 20, 20 );
    timeBar->setPen( QPen( temp.lighter( 170 )));
    timeBar->setBrush( temp);
}

void MainWindow::addOffset( int value ) {
    auto temp = ui->choiceBox->currentText() + QString::fromStdString("_") + QString::number(value);
    for ( int i = 0; i < ui->listWidget->count(); ++i ) {
        if(temp == ui->listWidget->item(i)->text()){
            auto message = new QMessageBox(this);
            message->setText("Already inserted");
            message->show();
            return;
        }
    }
    offsets << std::make_pair(temp, value);
    ui->listWidget->addItem(temp);
}

void MainWindow::generateData( Generator::RandomGenerator* generator ) {
    int size = atoi(ui->dimensionBox->text().toStdString().c_str());
    if ( size <= 2 ) {
        return;
    }
    QString path = QFileDialog::getOpenFileName( this, tr( "Select Your file:" ));
    auto writer = make_shared<RandomDataWriter>();
    auto data = writer->write( path.toStdString(), generator, size );
    ui->resultEdit->setText(QString::fromStdString(data));
}

void MainWindow::handleUniform( double lower, double upper ) {
    generateData(new UniformRandomGenerator(lower, upper));
}

void MainWindow::handleNormal( double mean, double stddev ) {
    generateData(new NormalRandomGenerator(mean, stddev));
}

void MainWindow::handleExp( double lambda ) {
    generateData(new ExponentialRandomGenerator(lambda));
}


#include "mainwindow.moc"