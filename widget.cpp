#include "widget.h"
#include "ui_widget.h"


#include <QDebug>
#include <QWebFrame>
#include <QFileInfo>
#include <QMessageBox>

#define LOCAL(x)    QString::fromLocal8Bit(x)

Downloader::Downloader(QObject *parent, QString filename)
    :QObject(parent)
    ,m_fname(filename),m_file(NULL)
{

}

Downloader::~Downloader()
{

}

void Downloader::finished()
{
    if ( m_file )
    {
        m_file->flush();
        m_file->close();
        m_reply->deleteLater();
        QMessageBox::information(0,LOCAL("提示"),LOCAL("文件:") + QFileInfo(m_fname).fileName() + LOCAL("下载完成"),0);
    }
}

void Downloader::readyRead()
{
    if( m_file )
        m_file->write(m_reply->readAll());
}

void Downloader::start()
{
    QFileInfo info(m_fname);
    QString fname = info.fileName();

    if (QFile::exists(fname))
        QFile::remove(fname);
    m_file = new QFile(fname);
    if ( !m_file->open(QIODevice::WriteOnly) )
    {
        QMessageBox::warning(0,LOCAL("警告"),LOCAL("无法保存文件"),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    m_reply = m_nam.get(QNetworkRequest(QUrl(m_fname)));

    connect( m_reply,SIGNAL(finished()),this,SLOT(finished()));
    connect( m_reply,SIGNAL(readyRead()),this,SLOT(readyRead()));
}



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QUrl    url("http://127.0.0.1:8000/file"/*"http://www.hao123.com"*/);
    ui->setupUi(this);
    ui->returnButton->setText(LOCAL("返回文件列表"));

    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(ui->webView,SIGNAL(linkClicked(QUrl)),this,SLOT(urlChange(QUrl)));
    //connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(urlChange(QUrl)));
}

void Widget::urlChange(const QUrl &url)
{
    qDebug()<<url.toString();
    ui->webView->load(url);
    download(url.toString());
}

void Widget::finished()
{

}
void Widget::readyRead()
{

}

Widget::~Widget()
{
    delete ui;
}

void Widget::download(QString file)
{
    Downloader *down = new Downloader(this,file);
    down->start();
}
void Widget::loadURL(QUrl &url)
{
    ui->webView->load(url);
}
