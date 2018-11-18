#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),cardDial(this)
{
    ui->setupUi(this);
    //setWindowIcon(QIcon(":/path/to/atm.svg"));
    QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    std::cout<<" Clicked ";
    qsw->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::cout<<" Clicked ";
    cardDial.show();
    //QStackedWidget *qsw = findChild<QStackedWidget*>("stackedWidget");
    //Q_ASSERT(qsw);
    //qsw->setCurrentIndex(1);

}
