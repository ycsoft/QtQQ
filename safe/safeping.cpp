
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>

#include "safeping.h"

SafePing::SafePing(QObject *parent) :
    QObject(parent)
{
    m_sock = new QTcpSocket(this);
    bool check = false;
    check = connect(m_sock,SIGNAL(connected()),this,SLOT(safe_connected()));


}

void SafePing::safe_connected()
{
    qDebug()<<"Connected!";
}

bool SafePing::ConnectToHost()
{
    m_sock->connectToHost("127.0.0.1",5033);
    bool b =  m_sock->waitForConnected();
    return b;
}

QString SafePing::Ping(QString &jid, QString &pwd)
{
    char buf[512] = "";

    if (!m_sock ->isOpen())
        return "";
    sprintf(buf,"<ping app=\"%s\"/>","Q-IM.exe");
    qDebug()<<"ping:"<<buf;
    qint64 qi = m_sock->write(buf,strlen(buf));
    m_sock->waitForBytesWritten();
    memset(buf,0,512);
    m_sock->waitForReadyRead();
    qi =   m_sock->read(buf,512);
    qDebug()<<"pong:"<<buf;
    QString res = QString::fromLocal8Bit(buf);
    QDomDocument    dom;
    if ( !dom.setContent(res))
        return "";
    QDomElement     elem = dom.documentElement();
    if ( elem.isNull())
        return "";
    jid = elem.attribute("id");
    pwd = elem.attribute("pwd");
    int pos = jid.indexOf("/");
    jid = jid.left(pos);
    return jid;

}

