#ifndef CARDINPUTDIALOG_H
#define CARDINPUTDIALOG_H
#include <QDialog>

namespace Ui {
class CardInputDialog;
}

class CardInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CardInputDialog(QWidget *parent = 0);
    ~CardInputDialog();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::CardInputDialog *ui;
    bool isUserSigningInIsServerApproved(QString &,QString &);
};

#endif // CARDINPUTDIALOG_H
