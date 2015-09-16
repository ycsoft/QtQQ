#include "sendfiles.h"
#include "ui_sendfiles.h"
#include "qfiletrans.h"
#include "loginwindow.h"
#include "qfiletrans.h"
#include "chatwindow.h"
#include "listwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFileIconProvider>
SendFiles::SendFiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendFiles)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint;
        setWindowFlags(flags);
    this->setWindowTitle(LOCAL("文件发送"));
    connect(ui->choose,SIGNAL(clicked()),this,SLOT(choosefile()));
    connect(ui->send,SIGNAL(clicked()),this,SLOT(sendfile())); 
}

//选择文件
void SendFiles::choosefile()
{
    QFileDialog *fd = new QFileDialog(this);
    if (fd -> exec() == QDialog::Accepted)
    {
        QString fn = fd->selectedFiles()[0];
        _file_to_send.clear();
        _file_to_send.append(fn);
        setFilePath(fn);
    }
}

void SendFiles::setFilePath(QString txt)
{
   // QFileInfo  info(txt);
  //  QFileIconProvider  ip;
   // QIcon ico = ip.icon(info);
  //  QPixmap  pix = ico.pixmap(30,30);
   // ui->label_ico->setPixmap(pix);
    ui->lineEdit->setText(txt);
}

//发送 文件
void SendFiles::sendfile()
{
    QString jid = tojid;
    Listwindow::Instance()->setwindowsendflag(jid,true);
    Loginwindow::getclient()->sendFile(jid,ui->lineEdit->text());
    close();
}

SendFiles::~SendFiles()
{
    delete ui;
}
