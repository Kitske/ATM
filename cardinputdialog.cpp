#include "cardinputdialog.h"
#include "ui_cardinputdialog.h"
#include <QRegExpValidator>
#include "mainwindow.h"
#include <QPushButton>
#include <iostream>
#include "errordialog.h"

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
    QDialogButtonBox * bb = findChild<QDialogButtonBox*>("buttonBox");
    bb->button(QDialogButtonBox::Ok)->setText("Ок");
    bb->button(QDialogButtonBox::Ok)->setDisabled(true);
    bb->button(QDialogButtonBox::Cancel)->setText("Назад");
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags& (~Qt::WindowContextHelpButtonHint));
}

CardInputDialog::~CardInputDialog()
{
    delete ui;
}

void CardInputDialog::on_buttonBox_accepted()
{
    QDialogButtonBox * bb = findChild<QDialogButtonBox*>("buttonBox");
    QPushButton * qpb = bb->button(QDialogButtonBox::Ok);
    qpb->setDisabled(true);
    QLineEdit *le = findChild<QLineEdit*>("lineEdit");
    Q_ASSERT(le);
    QLineEdit *le1 = findChild<QLineEdit*>("lineEdit_2");
    Q_ASSERT(le1);
    QString num = le->text();
    QString pin = le1->text();
    QRegExp re("^\\d{16}$");
    QRegExp re1("^\\d{4}$");
    QString s = QString("http://localhost:1337/api/user/authorize/");
    QUrl url = QUrl(s);
    QString jsonString = QString("{\"number\":\""+num+"\",\"pin\":\""+pin+"\"}");
    QNetworkRequest qnr =QNetworkRequest(url);
    qnr.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply * repl = (static_cast<MainWindow *>(parent()))->getMgr()->post(qnr, jsonString.toUtf8());
    QEventLoop loop;
    connect(repl, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QPair<QString,QString> qp = (static_cast<MainWindow *>(parent()))->getLastRequestInfo();
    int x = QString::compare((qp.first),QString("200"), Qt::CaseInsensitive);
    QString qs =qp.first;
    if(x==0){
        (static_cast<MainWindow *>(parent()))->startSessionWithCard(num);

    }
    else {
        x = QString::compare((qp.first),QString("404"), Qt::CaseInsensitive);
        if(x==0){
            QString e1 =QString("Карти з таким номером немає в базі даних");
            (static_cast<MainWindow *>(parent()))->err(e1);
        }
        else{
            x = QString::compare((qp.first),QString("403"), Qt::CaseInsensitive);
            if(x==0){
                x = QString::compare((qp.second),QString("{\"reason\":\"auth tries\"}"), Qt::CaseInsensitive);
                if(x==0){
                QString e2 =QString("Карта заблокована");
                (static_cast<MainWindow *>(parent()))->err(e2);
                }else{
                    x = QString::compare((qp.second),QString("{\"reason\":\"pin\"}"), Qt::CaseInsensitive);
                    if(x==0){
                    QString e3 =QString("Неправильний PIN-код");
                    (static_cast<MainWindow *>(parent()))->err(e3);
                    }

                }
            }else{
                QString e4 =QString("Помилка сервера");
                (static_cast<MainWindow *>(parent()))->err(e4);
            }
        }
    }
    le->setText("");
    le1->setText("");
}

void CardInputDialog::on_lineEdit_textChanged(const QString &t)
{
    QRegExp re("^\\d{16}$");
    QRegExp re1("^\\d{4}$");
    QDialogButtonBox * bb = findChild<QDialogButtonBox*>("buttonBox");
    QPushButton * qpb = bb->button(QDialogButtonBox::Ok);
    QLineEdit * le = findChild<QLineEdit *>("lineEdit_2");
    if(t.contains(re)&& (le->text()).contains(re1)){
        qpb->setDisabled(false);
    }else{
        qpb->setDisabled(true);
    }
}

void CardInputDialog::on_lineEdit_2_textChanged(const QString &t)
{
    QRegExp re("^\\d{16}$");
    QRegExp re1("^\\d{4}$");
    QDialogButtonBox * bb = findChild<QDialogButtonBox*>("buttonBox");
    QPushButton * qpb = bb->button(QDialogButtonBox::Ok);
    QLineEdit * le = findChild<QLineEdit *>("lineEdit");
    if(t.contains(re1)&& (le->text()).contains(re)){
        qpb->setDisabled(false);
    }else{
        qpb->setDisabled(true);
    }
}
