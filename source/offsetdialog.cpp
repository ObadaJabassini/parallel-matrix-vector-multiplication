#include <Ui/offsetdialog.h>
#include "ui_offsetdialog.h"

OffsetDialog::OffsetDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::OffsetDialog)
{
    ui->setupUi(this);
    QObject::connect(this, SLOT(accept()), this, SLOT(handle()));
}

void OffsetDialog::handle(){
    emit getData(ui->offsetBox->value());
}

OffsetDialog::~OffsetDialog()
{
    delete ui;
}

#include "offsetdialog.moc"