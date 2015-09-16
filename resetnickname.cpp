#include "resetnickname.h"
#include "ui_resetnickname.h"
#include "listwindow.h"
#include <QMessageBox>

ResetNickname::ResetNickname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetNickname)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint;
        setWindowFlags(flags);
    setWindowTitle(LOCAL("ÐÞ¸ÄêÇ³Æ"));
    //this->setFixedSize(220,80);
    bool check = connect(ui->Btt_confirm, SIGNAL(clicked()), this, SLOT(confirmClick()));
    Q_ASSERT(check);
}

ResetNickname::~ResetNickname()
{
    delete ui;
}

QString ResetNickname::getNickname()
{
    return Nickname;
}

void ResetNickname::confirmClick()
{
    Nickname = ui->text_newNickname->text();
  //  QMessageBox::information(this, "resetNickName", "success£¡");
     Listwindow::Instance()->changenick(Nickname);
    this->hide();
}
