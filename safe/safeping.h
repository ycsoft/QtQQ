#ifndef SAFEPING_H
#define SAFEPING_H

#include <QTcpSocket>
#include <QObject>

class SafePing : public QObject
{
    Q_OBJECT
public:
    explicit SafePing(QObject *parent = 0);

    QString Ping(QString &jid,QString &pwd);
    bool    ConnectToHost();
    void    Close()             { m_sock->close();}
signals:


public slots:

    void   safe_connected();
public:
    QTcpSocket      *m_sock;

};

#endif // SAFEPING_H
