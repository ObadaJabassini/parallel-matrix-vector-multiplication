#include <Ui/normaldialog.h>
#include "ui_normaldialog.h"

NormalDialog::NormalDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::NormalDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(handle()));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

NormalDialog::~NormalDialog()
{
    delete ui;
}

void NormalDialog::handle(){
    emit sendData(ui->meanBox->value(), ui->devBox->value());
    this->close();
}

#include "normaldialog.moc"