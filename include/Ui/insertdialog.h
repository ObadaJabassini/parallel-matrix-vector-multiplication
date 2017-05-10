//
// Created by ojabassini on 5/10/17.
//

#ifndef PROJECT_INSERTDIALOG_H
#define PROJECT_INSERTDIALOG_H

#include <QDialog>

namespace Ui {
    class InsertDialog;
}

class InsertDialog : public QDialog
{
Q_OBJECT

public:
    explicit InsertDialog(QWidget *parent = 0);
    ~InsertDialog();
signals:
    void sendData(QString matrix, QString vector);
public slots:
    void handle();

private:
    Ui::InsertDialog *ui;
};

#endif //PROJECT_INSERTDIALOG_H
