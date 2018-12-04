#include "errordialog.h"
#include "ui_errordialog.h"
#include "mainwindow.h"
#include "qlabel.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags& (~Qt::WindowContextHelpButtonHint));

}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::message(QString& m){
    (findChild<QLabel *>("errorDialLabel"))->setText(m);
    this->show();
}
