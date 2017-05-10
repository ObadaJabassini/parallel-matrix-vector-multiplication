#include <Ui/insertdialog.h>
#include "ui_insertdialog.h"

InsertDialog::InsertDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::InsertDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(handle()));
}

void InsertDialog::handle(){
    emit sendData(ui->matrixEdit->toPlainText(), ui->vectorEdit->text());
    this->close();
}

InsertDialog::~InsertDialog()
{
    delete ui;
}

#include "insertdialog.moc"