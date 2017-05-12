#include <Ui/exponentialdialog.h>
#include "ui_exponentialdialog.h"

ExponentialDialog::ExponentialDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ExponentialDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(handle()));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

ExponentialDialog::~ExponentialDialog()
{
    delete ui;
}

void ExponentialDialog::handle(){
    emit sendData(ui->lambdaBox->text().toDouble());
    this->close();
}

#include "exponentialdialog.moc"