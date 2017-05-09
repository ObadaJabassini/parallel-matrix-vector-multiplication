#include <Ui/dialog.h>
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(this, SLOT(accept()), this, SLOT(handle()));
}

void Dialog::handle(){
    emit getData(ui->matrixEdit->toPlainText(), ui->vectorEdit->text());
}

Dialog::~Dialog()
{
    delete ui;
}

#include "dialog.moc"