//
// Created by ojabassini on 5/11/17.
//

#ifndef PROJECT_UNIFORMDIALOG_H
#define PROJECT_UNIFORMDIALOG_H


#include <QDialog>

namespace Ui {
    class UniformDialog;
}

class UniformDialog : public QDialog
{
Q_OBJECT

public:
    explicit UniformDialog(QWidget *parent = 0);
    ~UniformDialog();
signals:
    void sendData(double lower, double upper);
public slots:
    void handle();

private:
    Ui::UniformDialog *ui;
};


#endif //PROJECT_UNIFORMDIALOG_H
