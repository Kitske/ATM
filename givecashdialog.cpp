#include "givecashdialog.h"
#include "ui_givecashdialog.h"
#include "mainwindow.h"
#include <qstackedwidget.h>
#include <qlineedit.h>

GiveCashDialog::GiveCashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GiveCashDialog)
{
    ui->setupUi(this);
}

GiveCashDialog::~GiveCashDialog()
{
    delete ui;
}

void GiveCashDialog::changeLabels(const int sumProcessed,const int allValuesProcessed,const int * nominalValueCountProcessed){
    QLabel * sumValue = findChild<QLabel*>("labelDialGiveCash_2");
    QLabel * allValues = findChild<QLabel*>("labelDialGiveCash_3");
    QLabel * valueCount1 = findChild<QLabel*>("label1DialGiveCash_8");
    QLabel * valueCount2 = findChild<QLabel*>("label1DialGiveCash_9");
    QLabel * valueCount3 = findChild<QLabel*>("label1DialGiveCash_10");
    QLabel * valueCount4 = findChild<QLabel*>("label1DialGiveCash_11");
    QLabel * valueCount5 = findChild<QLabel*>("label1DialGiveCash_12");
    QLabel * valueCount6 = findChild<QLabel*>("label1DialGiveCash_13");
    sumValue->setText(QString::number(sumProcessed));
    allValues->setText(QString::number(allValuesProcessed));
    valueCount1->setText(QString::number(nominalValueCountProcessed[0]));
    valueCount2->setText(QString::number(nominalValueCountProcessed[1]));
    valueCount3->setText(QString::number(nominalValueCountProcessed[2]));
    valueCount4->setText(QString::number(nominalValueCountProcessed[3]));
    valueCount5->setText(QString::number(nominalValueCountProcessed[4]));
    valueCount6->setText(QString::number(nominalValueCountProcessed[5]));
}

void GiveCashDialog::on_GiveCashDialog_finished(int result)
{
    QStackedWidget * qsw = (static_cast<MainWindow *>(parent()))->findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(2);
    QLineEdit * le = cw->findChild<QLineEdit *>("lineEditGiveCashMenu");
    Q_ASSERT(le);
    le->setText("");
    (static_cast<MainWindow *>(parent()))->backToLastMenu();
}
