#include "set_dirpath.h"
#include "ui_set_dirpath.h"
#include <qfiledialog>
#include <QDebug>
#include <QTextCodec>
#define LOCAL(x) QString::fromLocal8Bit(x)
Set_dirpath::Set_dirpath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set_dirpath)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    setWindowTitle(LOCAL("设置路径"));
    connect(ui->Bt_select,SIGNAL(clicked()),this,SLOT(slot_select()));
    connect(ui->Bt_ok, SIGNAL(clicked()), this, SLOT(slot_setpath()));
    connect(ui->Bt_cancel, SIGNAL(clicked()), this, SLOT(slot_close()));
}

Set_dirpath::~Set_dirpath()
{
    delete ui;
}

void Set_dirpath::slot_setpath()
{
    RoomChat::GetInstance()->set_path(ui->lineEdit->text());
    RoomChat::GetInstance()->set_remotepath(ui->comboBox->currentText());
    RoomChat::GetInstance()->set_downloadflag();
    this->hide();
}
void Set_dirpath::slot_close()
{
    this->close();
}
void Set_dirpath::slot_select()
{
    QFileDialog* openFilePath = new QFileDialog( this, LOCAL("请选择文件夹"), LOCAL("file"));     //打开一个目录选择对话框
    openFilePath->setFileMode(QFileDialog::DirectoryOnly);
    if ( openFilePath->exec() == QDialog::Accepted)
    {
        QString path = openFilePath->selectedFiles()[0];
        path += '/';

        ui->lineEdit->setText(path);
    }
    delete openFilePath;
}
