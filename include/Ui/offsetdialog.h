//
// Created by ojabassini on 5/10/17.
//

#ifndef PROJECT_OFFSETDIALOG_H
#define PROJECT_OFFSETDIALOG_H

#include <QDialog>

namespace Ui {
    class OffsetDialog;
}

class OffsetDialog : public QDialog
{
Q_OBJECT

public:
    explicit OffsetDialog(QWidget *parent = 0);
    ~OffsetDialog();
signals:
    void sendData(int offset);
public slots:
    void handle();

private:
    Ui::OffsetDialog *ui;
};

#endif //PROJECT_OFFSETDIALOG_H
