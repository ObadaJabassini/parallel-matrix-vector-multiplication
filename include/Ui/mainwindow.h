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
    void insert();
    void insertData(QString matrix, QString vector);
    void addOffset(int value);
    void addItem();
    void removeItem();
    void loadButton();
    void benchmark();

private:
    QCustomPlot* customPlot;
    void initCustomPlot();
    void initEvents();
    QString filePath;
    QVector<int> offsets;
    Ui::MainWindow* ui;
};

#endif //PROJECT_MAINWINDOW_H_H
