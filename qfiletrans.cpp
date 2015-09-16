#include "qfiletrans.h"
#include "session.h"

#include <QBuffer>
#include <QXmppUtils.h>
#include <QTextCodec>


QFileTrans::QFileTrans(QObject *parent):QXmppClient(parent),transferManager(0)
{
    bool check;
    Q_UNUSED(check);

    // add transfer manager
    transferManager = new QXmppTransferManager();
    addExtension(transferManager);
    //transferManager->setSupportedMethods(QXmppTransferJob::SocksMethod);
    transferManager->setSupportedMethods(QXmppTransferJob::InBandMethod);

}
void QFileTrans::setRecipient(const QString &recipient)
{
    m_recipient = recipient;
}

/// A file transfer failed.

void QFileTrans::slotError(QXmppTransferJob::Error error)
{
    qDebug() << "Transmission failed:" << error;
}

/// A file transfer request was received.

void QFileTrans::slotFileReceived(QXmppTransferJob *job)
{

}

/// A file transfer finished.

void QFileTrans::slotFinished()
{
    qDebug() << "Transmission finished";
}

/// A presence was received

void QFileTrans::slotPresenceReceived(const QXmppPresence &presence)
{/*
    bool check;
    Q_UNUSED(check);

    // if we don't have a recipient, or if the presence is not from the recipient,
    // do nothing
    if (m_recipient.isEmpty() ||
        QXmppUtils::jidToBareJid(presence.from()) != m_recipient ||
        presence.type() != QXmppPresence::Available)
        return;

    // send the file and connect to the job's signals
    QXmppTransferJob *job = transferManager->sendFile(presence.from(), ":/example_3_transferHandling.cpp", "example source code");

    check = connect(job, SIGNAL(error(QXmppTransferJob::Error)),
                    this, SLOT(slotError(QXmppTransferJob::Error)));
    Q_ASSERT(check);

    check = connect(job, SIGNAL(finished()),
                    this, SLOT(slotFinished()));
    Q_ASSERT(check);

    check = connect(job, SIGNAL(progress(qint64,qint64)),
                    this, SLOT(slotProgress(qint64,qint64)));
    Q_ASSERT(check);*/
}

/// A file transfer has made progress.

void QFileTrans::slotProgress(qint64 done, qint64 total)
{
    qDebug() << "Transmission progress:" << done << "/" << total;
}
QXmppTransferJob* QFileTrans::sendFile(const QString recipient, const QString file)
{
    bool check;
    Q_UNUSED(check);
    QXmppTransferJob *job = transferManager->sendFile(recipient, file, "");

    return job;
}
void QFileTrans::login(QString usr, QString pwd, QString domain, QString host,LoginType type)
{
    QString jid;
    jid = usr + tr("@") + domain + "/FT";
    if ( type == CA)
    {
         pwd = usr + ":" + pwd;
    }
    Session::Instance()->setJID(jid);
    logger()->setLoggingType(QXmppLogger::StdoutLogging);
    configuration().setDomain(domain);
    configuration().setHost(host);
    configuration().setJid(jid);
    configuration().setPassword(pwd);
    configuration().setPort(5222);

    configuration().setSaslAuthMechanism("PLAIN");
    connectToServer( configuration());
}

void QFileTrans::qxmpp_sendMessage(QString to, QString msg)
{
    sendMessage(to,msg);
}
void QFileTrans::qxmpp_sendData(QString data)
{
    sendData(data.toLocal8Bit());
}
