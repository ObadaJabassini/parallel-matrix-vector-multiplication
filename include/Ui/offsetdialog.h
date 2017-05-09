#ifndef OFFSETDIALOG_H
#define OFFSETDIALOG_H

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
    void getData(int value);
public slots:
    void handle();
private:
    Ui::OffsetDialog *ui;
};

#endif // OFFSETDIALOG_H
