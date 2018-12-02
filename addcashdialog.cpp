#include "addcashdialog.h"
#include "ui_addcashdialog.h"
#include "mainwindow.h"
#include <qstackedwidget.h>
#include <qlineedit.h>

AddCashDialog::AddCashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCashDialog)
{
    ui->setupUi(this);
}

AddCashDialog::~AddCashDialog()
{
    delete ui;
}
void AddCashDialog::changeLabels(QString& n,int v){
    QLabel * addCashCardNumLabel = findChild<QLabel*>("addCashDialLabelCardNum");
    QLabel * addCashIssuingCashValueLabel = findChild<QLabel*>("addCashDialIssuingCashValue");
    addCashCardNumLabel->setText(n);
    addCashIssuingCashValueLabel->setText(QString::number(v)+" грн.");
}

void AddCashDialog::on_AddCashDialog_finished(int result)
{
    QStackedWidget * qsw = (static_cast<MainWindow *>(parent()))->findChild<QStackedWidget*>("stackedWidget");
    Q_ASSERT(qsw);
    QWidget * cw = qsw->widget(3);
    QLineEdit * le = cw->findChild<QLineEdit *>("lineEditAddCash");
    Q_ASSERT(le);
    le->setText("");
    (static_cast<MainWindow *>(parent()))->backToLastMenu();

}
