#include "setstate.h"
#include "ui_setstate.h"
#include "maindialog.h"

setstate::setstate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setstate)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("提示"));
    connect(ui->bt_closecurrent,SIGNAL(clicked()),this,SLOT(slotclosecurrent()));
    connect(ui->bt_closeall,SIGNAL(clicked()),this,SLOT(slotcloseall()));
}

setstate::~setstate()
{
    delete ui;
}
void setstate::slotclosecurrent()
{
    MainDialog::getInstance()->setclosestate(1);
    this->close();
}
void setstate::slotcloseall()
{
    MainDialog::getInstance()->setclosestate(2);
    this->close();
}
