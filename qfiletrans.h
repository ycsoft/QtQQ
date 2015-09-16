#ifndef QFILETRANS_H
#define QFILETRANS_H

//#include <QAbstractSocket>
#include <QXmppClient.h>
#include <QXmppTransferManager.h>
#include <QXmppLogger.h>

class Dialog;
class QFileTrans : public QXmppClient
{
public:
    enum LoginType {Common,CA};
    QFileTrans(QObject *parent = 0);

    void setRecipient( const QString &recipient);

    QXmppTransferJob* sendFile(const QString recipient,const QString file);

    void login(QString usr,QString pwd,QString domain,QString host,LoginType type = Common);
private slots:
    void slotError(QXmppTransferJob::Error error);
    void slotFileReceived(QXmppTransferJob *job);
    void slotFinished();
    void slotPresenceReceived(const QXmppPresence &presence);
    void slotProgress(qint64 done, qint64 total);

    void    qxmpp_sendMessage(QString to ,QString msg);
    void    qxmpp_sendData(QString data);

private:
    QString m_recipient;
    Dialog  *m_parent;

public:
    QXmppTransferManager *transferManager;

};

#endif // QFILETRANS_H
