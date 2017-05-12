#include <Ui/offsetdialog.h>
#include "ui_offsetdialog.h"

OffsetDialog::OffsetDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::OffsetDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(handle()));
}

OffsetDialog::~OffsetDialog()
{
    delete ui;
}

void OffsetDialog::handle(){
    emit sendData(ui->offsetBox->text().toInt());
    this->close();
}

#include "offsetdialog.moc"