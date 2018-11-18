#include "cardinputdialog.h"
#include "ui_cardinputdialog.h"
#include <QRegExpValidator>

CardInputDialog::CardInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardInputDialog)
{
    ui->setupUi(this);
    QLineEdit *le = findChild<QLineEdit*>("lineEdit");
    Q_ASSERT(le);
    QRegExp re("^\\d{16}$");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    le->setValidator(validator);
}

CardInputDialog::~CardInputDialog()
{
    delete ui;
}
bool CardInputDialog::isCardNumberServerApproved(QString & qst){
    bool res = true;
    //here should be request to the server

    //
    return res;
}

void CardInputDialog::on_buttonBox_accepted()
{
    QLineEdit *le = findChild<QLineEdit*>("lineEdit");
    Q_ASSERT(le);
    QString t = le->text();
    QRegExp re("^\\d{16}$");

    if(t.contains(re)&&isCardNumberServerApproved(t)){
        le->setText("");
    }
    else{

    }

}
