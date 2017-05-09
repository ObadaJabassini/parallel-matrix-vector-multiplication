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
    void addItem();
    void removeItem();
    void loadButton();
    void benchmark();

private:
    void initEvents();
    QString filePath;
    Ui::MainWindow* ui;
};

#endif //PROJECT_MAINWINDOW_H_H
