#ifndef FILERECEIVEDLG_H
#define FILERECEIVEDLG_H

#include <QDialog>
#include <QCloseEvent>
#include <QXmppTransferManager.h>
#define LOCAL(x)  QString::fromLocal8Bit(x)
namespace Ui {
class FileReceiveDlg;
}

class FileReceiveDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FileReceiveDlg(QWidget *parent = 0);
    void     setFileName(const QString name);//文件名
    void     setFrom( const QString from);// 谁发的
    void     setSize(qint64 size);// 文件大小
    void     setbuttonstop();
    void     closeEvent( QCloseEvent *e);
    void     setfilejob(QXmppTransferJob*);
    void     changetosenddlg(QString);
    ~FileReceiveDlg();
public slots:
    void    slotAccept();
    void    slotReject();
    void    slotselectpath();
    void    slotfinished();
    void    sloterror(QXmppTransferJob::Error);
    void    slotProgress(qint64 transed,qint64 total);//进度条
private:
    Ui::FileReceiveDlg *ui;
    bool sendflg;//标志是否发送文件
    QXmppTransferJob* filejob;
    bool abortflag;//标志是否被中止
};

#endif // FILERECEIVEDLG_H
