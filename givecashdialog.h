#ifndef GIVECASHDIALOG_H
#define GIVECASHDIALOG_H

#include <QDialog>

namespace Ui {
class GiveCashDialog;
}

class GiveCashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GiveCashDialog(QWidget *);
    ~GiveCashDialog();
    void changeLabels(const int,const int,const int *);

private slots:
    void on_GiveCashDialog_finished(int result);

private:
    Ui::GiveCashDialog *ui;
};

#endif // GIVECASHDIALOG_H
