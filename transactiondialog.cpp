#include "transactiondialog.h"
#include "ui_transactiondialog.h"
#include "mainwindow.h"
#include <qstackedwidget.h>
#include <QPushButton>
#include <QLineEdit>

TransactionDialog::TransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionDialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags& (~Qt::WindowContextHelpButtonHint));
}

TransactionDialog::~TransactionDialog()
{
    delete ui;
}

void TransactionDialog::changeLabels(QString& inputCard1,QString& inputSum,QString& inputCard2){
    QLabel * card1 = findChild<QLabel*>("transactionDialCard1Label");
    Q_ASSERT(card1);
    QLabel * card2 = findChild<QLabel*>("transactionDialCard2Label");
    Q_ASSERT(card2);
    QLabel * sum = findChild<QLabel*>("transactionDialSumLabel");
    Q_ASSERT(sum);
    card1->setText(inputCard1);
    card2->setText(inputCard2);
    sum->setText(inputSum);
}

void TransactionDialog::on_transactionDialog_finished(int result)
{
    QStackedWidget * qsw = (static_cast<MainWindow *>(parent()))->findChild<QStackedWidget*>("stackedWidget");
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

    (static_cast<MainWindow *>(parent()))->backToLastMenu();
}
