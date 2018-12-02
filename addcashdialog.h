#ifndef ADDCASHDIALOG_H
#define ADDCASHDIALOG_H

#include <QDialog>

namespace Ui {
class AddCashDialog;
}

class AddCashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCashDialog(QWidget *parent = 0);
    ~AddCashDialog();
    void changeLabels(QString&,int);

private slots:
    void on_AddCashDialog_finished(int result);

private:
    Ui::AddCashDialog *ui;
};

#endif // ADDCASHDIALOG_H
