#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class TransactionDialog;
}

class TransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionDialog(QWidget *parent = 0);
    ~TransactionDialog();
    void changeLabels(QString&,QString&,QString&);
private slots:
    void on_transactionDialog_finished(int result);

private:
    Ui::TransactionDialog *ui;
};

#endif // TRANSACTIONDIALOG_H
