//
// Created by ojabassini on 5/11/17.
//

#ifndef PROJECT_EXPONENTIALDIALOG_H
#define PROJECT_EXPONENTIALDIALOG_H

#include <QDialog>

namespace Ui {
class ExponentialDialog;
}

class ExponentialDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExponentialDialog(QWidget *parent = 0);
    ~ExponentialDialog();
public slots:
    void handle();
signals:
    void sendData(double lambda);
private:
    Ui::ExponentialDialog *ui;
};

#endif //PROJECT_EXPONENTIALDIALOG_H
