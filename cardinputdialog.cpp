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
    QLineEdit *le1 = findChild<QLineEdit*>("lineEdit_2");
    Q_ASSERT(le1);
    le1->setEchoMode(QLineEdit::Password);
    QRegExp re1("^\\d{4}$");
    QRegExpValidator *validator1 = new QRegExpValidator(re1, this);
    le1->setValidator(validator1);
}

CardInputDialog::~CardInputDialog()
{
    delete ui;
}

bool CardInputDialog::isUserSigningInIsServerApproved(QString & cardNumber,QString & pin){
    bool res = true;
    //here should be request to the server

    //
    return res;
}

void CardInputDialog::on_buttonBox_accepted()
{
    QLineEdit *le = findChild<QLineEdit*>("lineEdit");
    Q_ASSERT(le);
    QLineEdit *le1 = findChild<QLineEdit*>("lineEdit_2");
    Q_ASSERT(le1);
    QString num = le->text();
    QString pin = le1->text();
    QRegExp re("^\\d{16}$");
    QRegExp re1("^\\d{4}$");

    if(num.contains(re)&&pin.contains(re1)&&isUserSigningInIsServerApproved(num,pin)){



        le->setText("");
        le1->setText("");
    }
    else{

    }

}
