#include "chats.h"
#include "ui_chats.h"
#include <Qtextcodec>

chats::chats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chats)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    setWindowTitle(LOCAL("ÏûÏ¢¼ÇÂ¼"));
    ui->textEdit->setReadOnly(true);
}

chats::~chats()
{
    delete ui;
}

void chats::setchatsedit(QString text)
{
    ui->textEdit->insertPlainText(text);
    scrollToBottom();
}

void chats::clear()
{
    ui->textEdit->clear();
}

void chats::scrollToBottom()
{
    QTextCursor  txtcur = ui->textEdit->textCursor();
    txtcur.movePosition(txtcur.End);
    ui->textEdit->setTextCursor(txtcur);
}
