//
// Created by ojabassini on 5/9/17.
//

#ifndef PROJECT_MAINWINDOW_H_H
#define PROJECT_MAINWINDOW_H_H

#include <QMainWindow>
#include <iostream>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <qcustomplot.h>
#include <RandomGenerator/RandomGenerator.h>

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:

    explicit MainWindow( QWidget* parent = 0 );

    ~MainWindow();

public slots:
    void generate();
    void handleUniform(double lower, double upper);
    void handleNormal(double mean, double stddev);
    void handleExp(double lambda);
    void insert();
    void insertData(QString matrix, QString vector);
    void addOffset(int value);
    void addItem();
    void removeItem();
    void loadButton();
    void benchmark();

private:
    QCustomPlot* customPlot;
    QCPBars* timeBar;
    void initCustomPlot();
    void initEvents();
    void generateData(Generator::RandomGenerator* generator);
    QString filePath;
    QVector<std::pair<QString,int> > offsets;
    Ui::MainWindow* ui;
};

#endif //PROJECT_MAINWINDOW_H_H
