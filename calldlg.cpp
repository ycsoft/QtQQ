#include "calldlg.h"
#include "ui_calldlg.h"
#include "qfiletrans.h"
#include "listwindow.h"

CallDlg::CallDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallDlg)
{
    ui->setupUi(this);
    ui->lineEdit->setText(selfjid);
}

CallDlg::~CallDlg()
{
    delete ui;
}
void CallDlg::startCall()
{
//Loginwindow::getclient()->
}
QXmppCall *CallDlg::call (const QString &jid)
{

}
