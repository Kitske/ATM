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

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::CardInputDialog *ui;
};

#endif // CARDINPUTDIALOG_H
