//
// Created by ojabassini on 5/11/17.
//

#ifndef PROJECT_NORMALDIALOG_H
#define PROJECT_NORMALDIALOG_H

#include <QDialog>

namespace Ui {
    class NormalDialog;
}

class NormalDialog : public QDialog
{
Q_OBJECT

public:
    explicit NormalDialog(QWidget *parent = 0);
    ~NormalDialog();
signals:
    void sendData(double mean, double stddev);
public slots:
    void handle();
private:
    Ui::NormalDialog *ui;
};

#endif //PROJECT_NORMALDIALOG_H
