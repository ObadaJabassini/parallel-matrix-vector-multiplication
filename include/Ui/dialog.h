//
// Created by ojabassini on 5/9/17.
//

#ifndef PROJECT_DIALOG_H
#define PROJECT_DIALOG_H
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
signals:
    void getData(QString matrix, QString vector);
public slots:
    void handle();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H


#endif //PROJECT_DIALOG_H
