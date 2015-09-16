#include "setdlg.h"
#include "ui_setdlg.h"
#include <QSettings>
#include <QFileDialog>

SetDlg* SetDlg::m_instance=NULL;
SetDlg::SetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDlg)
{
    ui->setupUi(this);
     m_instance = this;
     Qt::WindowFlags flags=Qt::Dialog;
         flags |=Qt::WindowMinimizeButtonHint;
         setWindowFlags(flags);
    // this->setFixedSize(222,100);
     this->setWindowTitle(LOCAL("·þÎñÆ÷ÉèÖÃ"));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slotclose()));
    QSettings set;
    QString ip,svr,fshare;
    ip = set.value("ip",ip).toString();
    svr = set.value("svr",svr).toString();
    fshare = set.value("fserver",fshare).toString();
    ui->lineEditip->setText(ip);
    ui->lineEditname->setText(svr);
    ui->line_fileshare->setText(fshare);
}

SetDlg::~SetDlg()
{
    delete ui;
}
void SetDlg::slotclose()
{
    QSettings set;
    set.setValue("ip",ui->lineEditip->text());
    set.setValue("svr",ui->lineEditname->text());
    set.setValue("fserver",ui->line_fileshare->text());
    this->close();
}
QString SetDlg::getip()
{
    return ui->lineEditip->text();
}
QString SetDlg::getsvr(){
    return ui->lineEditname->text();
}
QString SetDlg::getfshare()
{
    QString fshare = "git://" + ui->line_fileshare->text();
    fshare += "/file/";
    return fshare;
}
QString SetDlg::getfserver()
{
    QString chat = "git://" + ui->line_fileshare->text();
    chat += "/chat/";
    return chat;
}
SetDlg *SetDlg::Instance()
{
    if(m_instance == NULL){
        m_instance = new SetDlg(0);
    }
    return m_instance;
}
