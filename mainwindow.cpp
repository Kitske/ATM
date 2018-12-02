#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRegExpValidator>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),moneyNominalValueCount(new int[6]),cardDial(this),giveCashDial(this)
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
    QPushButton * qpb = cw->findChild<QPushButton *>("pushButton2GiveCashMenu");
    qpb->setDisabled(true);
    qsw->setCurrentIndex(0);
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
    QWidget * services = qsw->widget(1);
    QLabel * cardNumLabel = services->findChild<QLabel*>("label_5");
    QString cardNumWithSpaces = cardNum.mid(0,4)+" "+cardNum.mid(4,4)+" "+cardNum.mid(8,4)+" "+cardNum.mid(12,4);
    cardNumLabel->setText(cardNumWithSpaces);
    QWidget * cw = qsw->widget(2);
    QLabel * cardNumLabel1 = cw->findChild<QLabel *>("label3GiveCashMenu");
    cardNumLabel1->setText(cardNumWithSpaces);
    QLineEdit * qle = cw->findChild<QLineEdit*>("lineEditGiveCashMenu");
    QRegExp re1("^(10000)|([1-9]\\d?\\d?0)$");
    QRegExpValidator *validator1 = new QRegExpValidator(re1, this);
    qle->setValidator(validator1);
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

void MainWindow::on_lineEditGiveCashMenu_textChanged(const QString &arg1)
{
    QStackedWidget * qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(2);
    QPushButton * qpb = cw->findChild<QPushButton *>("pushButton2GiveCashMenu");
    QRegExp re1("(((1\\d{2})|([1-9]\\d?))\\d?0)");
    QLineEdit *le = cw->findChild<QLineEdit*>("lineEditGiveCashMenu");
    Q_ASSERT(le);
    if((le->text()).contains(re1)){
        qpb->setDisabled(false);
    }else{
        qpb->setDisabled(true);
    }
}
