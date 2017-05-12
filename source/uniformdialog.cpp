#include <Ui/uniformdialog.h>
#include "ui_uniformdialog.h"

UniformDialog::UniformDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::UniformDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(handle()));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

UniformDialog::~UniformDialog()
{
    delete ui;
}

void UniformDialog::handle(){
    emit sendData(ui->lowerBox->text().toDouble(), ui->upperBox->text().toDouble());
    this->close();
}

#include "uniformdialog.moc"