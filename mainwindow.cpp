#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRegExpValidator>
#include <cstdlib>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QHttpPart>

#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qhttpmultipart.h>

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),moneyNominalValueCount(new int[6]),
    cardDial(this),giveCashDial(this),currentCardNum("0000000000000000"),
    addCashDial(this),transactionDial(this),errorDial(this),
    mgr(new QNetworkAccessManager(this)),lastRequestInfo(QPair<QString,QString>(QString(" "),QString(" ")))
{
    ui->setupUi(this);

    moneyNominalValueCount[0]=1000; //500
    moneyNominalValueCount[1]=1000; //200
    moneyNominalValueCount[2]=1000; //100
    moneyNominalValueCount[3]=1000; //50
    moneyNominalValueCount[4]=1000; //20
    moneyNominalValueCount[5]=1000; //10

    setWindowIcon(QIcon(":/appIco.png"));

    QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);

    QWidget * cw = qsw->widget(2);
    QWidget * cw1 = qsw->widget(3);
    QWidget * cw3 = qsw->widget(5);

    QLineEdit * le = cw->findChild<QLineEdit*>("lineEditGiveCashMenu");
    QLineEdit * le1 = cw1->findChild<QLineEdit*>("lineEditAddCash");
    QLineEdit * le2 = cw3->findChild<QLineEdit *>("lineEditTransaction");
    QLineEdit * le3 = cw3->findChild<QLineEdit *>("lineEditTransaction_2");

    QRegExp re1("^(10000)|([1-9]\\d?\\d?0)$");
    QRegExpValidator *validator1 = new QRegExpValidator(re1, this);
    le->setValidator(validator1);

    QRegExp re2("^((1\\d\\d\\d)|(2000)|([1-9]\\d?\\d?))0$");
    QRegExpValidator *validator2 = new QRegExpValidator(re2, this);
    le1->setValidator(validator2);

    QRegExp re3("^\\d{16}$");
    QRegExpValidator *validator3 = new QRegExpValidator(re3, this);
    le3->setValidator(validator3);

    QRegExp re4("^((8000)|([1-7]\\d{3})|([1-9]\\d?\\d?))0$");
    QRegExpValidator *validator4 = new QRegExpValidator(re4, this);
    le2->setValidator(validator4);

    QPushButton * qpb = cw->findChild<QPushButton *>("pushButton2GiveCashMenu");
    QPushButton * qpb1 = cw1->findChild<QPushButton *>("addCashPushButton_4");
    QPushButton * qpb2 = cw3->findChild<QPushButton *>("transactionPushButton_4");
    qpb->setDisabled(true);
    qpb1->setDisabled(true);
    qpb2->setDisabled(true);

    qsw->setCurrentIndex(0);

    connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinish(QNetworkReply*)));
}

QNetworkAccessManager * MainWindow::getMgr(){
    return mgr;
}


void MainWindow::onRequestFinish(QNetworkReply* reply)
{
  /*if (reply->error() == QNetworkReply::NoError)
    {*/
      QByteArray content= reply->readAll();
      QString body(content);
      QString codeAttr = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toString();
      std::cout << codeAttr.toStdString()<<std::endl;
      std::cout <<body.toStdString()<< std::endl; // ok
    /*} else {
       QByteArray content= reply->readAll();
       QString body(content);
       std::cout <<body.toStdString()<< std::endl; // ok
        //empty, but must be exist
    }*/
      lastRequestInfo=QPair<QString,QString>(codeAttr,body);
      reply->deleteLater();
}

QPair<QString,QString> MainWindow::getLastRequestInfo(){
    return lastRequestInfo;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cardDial.show();
}

void MainWindow::startSessionWithCard(const QString& cardNum){
    QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);

    QWidget * cwServices = qsw->widget(1);

    QLabel * cardNumLabel = cwServices->findChild<QLabel*>("label_5");
    QString cardNumWithSpaces = cardNum.mid(0,4)+" "+cardNum.mid(4,4)+" "+cardNum.mid(8,4)+" "+cardNum.mid(12,4);
    cardNumLabel->setText(cardNumWithSpaces);

    QWidget * cw = qsw->widget(2);
    QLabel * cardNumLabel1 = cw->findChild<QLabel *>("label3GiveCashMenu");
    cardNumLabel1->setText(cardNumWithSpaces);

    QWidget * cw1 = qsw->widget(3);
    QLabel * cardNumLabel2 = cw1->findChild<QLabel *>("addCashLabel_5");
    cardNumLabel2->setText(cardNumWithSpaces);

    QWidget * cw2 = qsw->widget(4);
    QLabel * cardNumLabel3 = cw2->findChild<QLabel *>("checkBalanceLabel_5");
    cardNumLabel3->setText(cardNumWithSpaces);

    QWidget * cw3 = qsw->widget(5);
    QLabel * cardNumLabel4 = cw3->findChild<QLabel *>("transactionLabel_5");
    cardNumLabel4->setText(cardNumWithSpaces);

    currentCardNum=cardNum;
    nextMenu(0,1);
}

void MainWindow::on_pushButton_4_clicked()
{
    backToLastMenu();
}

void MainWindow::backToLastMenu(){
    QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    qsw->setCurrentIndex(menusStack.top());
    menusStack.pop();
}

void MainWindow::nextMenu(int previous,int next){
    QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    menusStack.push(previous);
    qsw->setCurrentIndex(next);
}

void MainWindow::on_pushButton_6_clicked()
{
    nextMenu(1,2);
}

void MainWindow::on_pushButton1GiveCashMenu_clicked()
{
    QStackedWidget * qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(2);
    QLineEdit * le = cw->findChild<QLineEdit *>("lineEditGiveCashMenu");
    Q_ASSERT(le);
    le->setText("");

    QPushButton * qpb =cw->findChild<QPushButton *>("pushButton2GiveCashMenu");
    qpb->setDisabled(true);

    backToLastMenu();
}

void MainWindow::on_pushButton2GiveCashMenu_clicked()
{
    QStackedWidget * qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(2);
    QLineEdit *le = cw->findChild<QLineEdit*>("lineEditGiveCashMenu");
    processGivingCash(le->text().toInt());
}

void MainWindow::processGivingCash(int value){
    int * tempNominalValueCount = new int[6];
    for(int i=0;i<6;++i)
        tempNominalValueCount[i]=0;
    const int valueCopy(value);
    while(div(value,500).quot>0&&moneyNominalValueCount[0]>0){
        ++tempNominalValueCount[0];
        value-=500;
    }
    while(div(value,200).quot>0&&moneyNominalValueCount[1]>0){
        ++tempNominalValueCount[1];
        value-=200;
    }
    while(div(value,100).quot>0&&moneyNominalValueCount[2]>0){
        ++tempNominalValueCount[2];
        value-=100;
    }
    while(div(value,50).quot>0&&moneyNominalValueCount[3]>0){
        ++tempNominalValueCount[3];
        value-=50;
    }
    while(div(value,20).quot>0&&moneyNominalValueCount[4]>0){
        ++tempNominalValueCount[4];
        value-=20;
    }
    while(div(value,10).quot>0&&moneyNominalValueCount[5]>0){
        ++tempNominalValueCount[5];
        value-=10;
    }
    int processedAllValues(0);
    if(value==0){
        for(int i=0;i<6;++i){
            moneyNominalValueCount[i]-=tempNominalValueCount[i];
            processedAllValues+=tempNominalValueCount[i];
        }
        giveCashDial.changeLabels(valueCopy,processedAllValues,tempNominalValueCount);
        giveCashDial.show();
    }
    else{

    }
}

void MainWindow::on_lineEditGiveCashMenu_textChanged(const QString &t)
{
    QStackedWidget * qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(2);
    QPushButton * qpb = cw->findChild<QPushButton *>("pushButton2GiveCashMenu");
    QRegExp re1("(10000)|([1-9]\\d?\\d?0)");
    QLineEdit *le = cw->findChild<QLineEdit*>("lineEditGiveCashMenu");
    Q_ASSERT(le);
    if(t.contains(re1)){
        qpb->setDisabled(false);
    }else{
        qpb->setDisabled(true);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    nextMenu(1,3);
}

void MainWindow::on_addCashPushButton_3_clicked()
{
    QStackedWidget * qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(3);
    QLineEdit * le = cw->findChild<QLineEdit *>("lineEditAddCash");
    Q_ASSERT(le);
    le->setText("");

    QPushButton * qpb =cw->findChild<QPushButton *>("addCashPushButton_4");
    qpb->setDisabled(true);

    backToLastMenu();
}

void MainWindow::on_addCashPushButton_4_clicked()
{
    QStackedWidget * qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(3);
    QLineEdit *le = cw->findChild<QLineEdit*>("lineEditAddCash");
    processAddingCash(le->text().toInt());
}

void MainWindow::processAddingCash(int value){
    QString n = currentCardNum.mid(0,4)+" "+currentCardNum.mid(4,4)+" "+currentCardNum.mid(8,4)+" "+currentCardNum.mid(12,4);
    addCashDial.changeLabels(n,value);
    addCashDial.show();
}

void MainWindow::on_lineEditAddCash_textChanged(const QString &t)
{
    QStackedWidget * qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(3);
    QPushButton * qpb = cw->findChild<QPushButton *>("addCashPushButton_4");
    QRegExp re1("((1\\d\\d\\d)|(2000)|([1-9]\\d?\\d?))0");
    QLineEdit *le = cw->findChild<QLineEdit*>("lineEditAddCash");
    Q_ASSERT(le);
    if(t.contains(re1)){
        qpb->setDisabled(false);
    }else{
        qpb->setDisabled(true);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    nextMenu(1,4);
}

void MainWindow::on_checkBalancePushButton_3_clicked()
{
    backToLastMenu();
}

void MainWindow::on_pushButton_8_clicked()
{
    nextMenu(1,5);
}

void MainWindow::on_transactionPushButton_3_clicked()
{
    QStackedWidget * qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);

    QWidget * cw = qsw->widget(5);

    QLineEdit * le = cw->findChild<QLineEdit *>("lineEditTransaction");
    QLineEdit * le1 = cw->findChild<QLineEdit *>("lineEditTransaction_2");

    Q_ASSERT(le);
    Q_ASSERT(le1);

    le->setText("");
    le1->setText("");

    QPushButton * qpb =cw->findChild<QPushButton *>("transactionPushButton_4");
    qpb->setDisabled(true);

    backToLastMenu();
}

void MainWindow::err(QString& s){
    errorDial.message(s);
}

//zdisnutu perekaz
void MainWindow::on_transactionPushButton_4_clicked()
{
    QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    QWidget * cw = qsw->widget(5);
    QString cardS1 = (cw->findChild<QLabel *>("transactionLabel_5"))->text();
    QLineEdit * le1 = cw->findChild<QLineEdit *>("lineEditTransaction");
    QLineEdit * le2 = cw->findChild<QLineEdit *>("lineEditTransaction_2");
    QString le2Text = le2->text();
    QRegExp re1("^((8000)|([1-7]\\d{3})|([1-9]\\d?\\d?))0$");
    QRegExp re2("^\\d{16}$");
    QString sumS = le1->text();
    if(!((le1->text()).contains(re1))){
        QString errmsg1 =QString("Неправильний формат суми для переказу");
        errorDial.message(errmsg1);
    }
    else if(!((le2->text()).contains(re2))){
        QString errmsg2 =QString("Неправильний формат номеру карти отримувача");
        errorDial.message(errmsg2);
    }
    else {
        QString cardS2 = le2Text.mid(0,4)+" "+le2Text.mid(4,4)+" "+le2Text.mid(8,4)+" "+le2Text.mid(12,4);
        transactionDial.changeLabels(cardS1,sumS,cardS2);
        transactionDial.show();
    }

}

void MainWindow::on_lineEditTransaction_textChanged(const QString &t)
{
    QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    QWidget * cw = qsw->widget(5);
    QPushButton * qpb = cw->findChild<QPushButton *>("transactionPushButton_4");
    QLineEdit * le2 = cw->findChild<QLineEdit *>("lineEditTransaction_2");
    QRegExp re1("^((8000)|([1-7]\\d{3})|([1-9]\\d?\\d?))0$");
    QRegExp re2("^\\d{16}$");
    if(t.contains(re1)&&le2->text().contains(re2)){
        qpb->setDisabled(false);
    }
    else{
        qpb->setDisabled(true);
    }
}

void MainWindow::on_lineEditTransaction_2_textChanged(const QString &t)
{
    QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    QWidget * cw = qsw->widget(5);
    QPushButton * qpb = cw->findChild<QPushButton *>("transactionPushButton_4");
    QLineEdit * le1 = cw->findChild<QLineEdit *>("lineEditTransaction");
    QRegExp re1("^((8000)|([1-7]\\d{3})|([1-9]\\d?\\d?))0$");
    QRegExp re2("^\\d{16}$");
    if(t.contains(re2)&&le1->text().contains(re1)){
        qpb->setDisabled(false);
    }
    else{
        qpb->setDisabled(true);
    }
}
