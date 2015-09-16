#include "filereceivedlg.h"
#include "ui_filereceivedlg.h"
#include "loginwindow.h"
#include <QCloseEvent>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

//文件接受
FileReceiveDlg::FileReceiveDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileReceiveDlg)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint;
        setWindowFlags(flags);
    this->setWindowTitle("File Reccieve");
    connect(ui->pushButtonAccept,SIGNAL(clicked()),this,SLOT(slotAccept()));
    connect(ui->pushButtonReject,SIGNAL(clicked()),this,SLOT(slotReject()));
    connect(ui->bt_selectpath,SIGNAL(clicked()),this,SLOT(slotselectpath()));
    QIcon   ico(":Icon_send.png");
    setWindowIcon(ico);
    ui->progressBar->setVisible(true);
    abortflag = false;
    sendflg = true;
}

FileReceiveDlg::~FileReceiveDlg()
{
    delete ui;
}

void FileReceiveDlg::setFileName(const QString name)
{
    ui->lineEdit_FileName->setText(name);
}
void FileReceiveDlg::setFrom(const QString from)
{
    ui->lineEditSender->setText(from);
}

void FileReceiveDlg::setSize(qint64 size)
{
    int flag = 0;
    qint64 mod = 0;
    if(size > 1024)
    {
        mod = size % 1024;
        size/=1024;
        flag = 1;
    }
    if(size > 1024)
    {
        mod = size % 1024;
        size/=1024;
        flag = 2;
    }

    mod/=10;

    char sz[20] = {0};
    sprintf(sz,"%ld",size);
    QString qs = QString::fromAscii(sz);
    memset(sz,'\0',20);
    sprintf(sz,"%ld",mod);
    QString qmod = QString::fromAscii(sz);

    if(flag == 2)
        ui->lineEditSize->setText(qs + "." + qmod + "MB");
    else if(flag == 1)
        ui->lineEditSize->setText(qs + "." + qmod +  "KB");
    else
        ui->lineEditSize->setText(qs + "." + qmod +  "byte");
}
void FileReceiveDlg::slotAccept()
{
    hide();
    ui->bt_selectpath->hide();
    ui->pushButtonAccept->hide();
    ui->pushButtonReject->setText(LOCAL("停止"));
    setResult(11);
}
void FileReceiveDlg::slotReject()
{
    filejob->abort();
    hide();
    setResult(12);
}
void FileReceiveDlg::closeEvent(QCloseEvent *e)
{
    hide();
    e->ignore();
}
void FileReceiveDlg::slotProgress(qint64 transed, qint64 total)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(transed);
    if(total==transed)
    this->close();
}
void FileReceiveDlg::changetosenddlg(QString recver)
{
    ui->label->setText(LOCAL("接收者"));
    ui->lineEditSender->setText(recver);
    ui->pushButtonAccept->hide();
    sendflg = false;
    ui->bt_selectpath->hide();
}

void FileReceiveDlg::slotselectpath()
{
    QFileDialog* fdlg = new QFileDialog(this);
    fdlg -> setFileMode(QFileDialog::DirectoryOnly);
    QString path;
    if(fdlg->exec() == QDialog::Accepted)
    {
        path = fdlg->selectedFiles()[0];
    }

    QDir::setCurrent(path);
    delete fdlg;
}

void FileReceiveDlg::setfilejob(QXmppTransferJob* job)
{
    filejob = job;
}

void FileReceiveDlg::slotfinished()
{
    if(abortflag)
        return;
    if(sendflg)
        QMessageBox::information(this,LOCAL("提示"),filejob->fileName()+LOCAL("接收成功"),0);
    else
        QMessageBox::information(this,LOCAL("提示"),filejob->fileName()+LOCAL("发送成功"),0);
}

void FileReceiveDlg::sloterror(QXmppTransferJob::Error)
{
    abortflag = true;
    if(sendflg)
        QMessageBox::information(this,LOCAL("提示"),filejob->fileName()+LOCAL("文件接收中止"),0);
    else
        QMessageBox::information(this,LOCAL("提示"),filejob->fileName()+LOCAL("文件发送中止"),0);
    hide();
}
void FileReceiveDlg::setbuttonstop()
{
    ui->pushButtonReject->setText(LOCAL("停止"));
}
