#include "addfiles.h"
#include "ui_addfiles.h"
#include <QFileDialog>
#include "roomchat.h"
#include <QDebug>
#include <QTextCodec>
addfiles::addfiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addfiles)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    setWindowTitle(LOCAL("添加文件"));
    connect(ui->bt_cofirm,SIGNAL(clicked()),this,SLOT(slotconfirm()));
    connect(ui->bt_select,SIGNAL(clicked()),this,SLOT(slotselect()));
}

addfiles::~addfiles()
{
    delete ui;
}

void addfiles::slotconfirm()
{
    if(!(ui->line_path->text().isEmpty()))
    {
        RoomChat::GetInstance()->get_filename(ui->line_path->text());
        this->close();
    }
}
void addfiles::slotselect()
{
    QFileDialog* fdlg = new QFileDialog(this);
    fdlg -> setFileMode(QFileDialog::DirectoryOnly);
    if(fdlg->exec() == QDialog::Accepted)
    {
        QString path = fdlg->selectedFiles()[0];
        ui->line_path->setText(path);
    }
    delete fdlg;
}

QString addfiles::getfilename()
{
    return ui->line_path->text();
}
