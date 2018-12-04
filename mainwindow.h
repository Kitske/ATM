#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardinputdialog.h"
#include "givecashdialog.h"
#include "addcashdialog.h"
#include "transactiondialog.h"
#include "errordialog.h"
#include <QMainWindow>
#include <stack>

#include <QtNetwork/QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startSessionWithCard(const QString&);
    void backToLastMenu();
    QNetworkAccessManager * getMgr();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void nextMenu(int previous,int next);
    void on_pushButton1GiveCashMenu_clicked();
    void on_pushButton2GiveCashMenu_clicked();
    void processGivingCash(int value);
    void processAddingCash(int value);
    void onFinish(QNetworkReply*);
    void on_lineEditGiveCashMenu_textChanged(const QString &arg1);

    void on_pushButton_7_clicked();

    void on_addCashPushButton_3_clicked();

    void on_addCashPushButton_4_clicked();

    void on_lineEditAddCash_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_checkBalancePushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_transactionPushButton_3_clicked();

    void on_transactionPushButton_4_clicked();

    void on_lineEditTransaction_textChanged(const QString &arg1);

    void on_lineEditTransaction_2_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    int * moneyNominalValueCount;
    CardInputDialog cardDial;
    GiveCashDialog giveCashDial;
    TransactionDialog transactionDial;
    ErrorDialog errorDial;
    std::stack<int> menusStack;
    QString currentCardNum;
    AddCashDialog addCashDial;
    QNetworkAccessManager * mgr;
};

#endif // MAINWINDOW_H
