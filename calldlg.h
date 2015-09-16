#ifndef CALLDLG_H
#define CALLDLG_H

#include <QDialog>
#include <QXmppCallManager.h>

namespace Ui {
class CallDlg;
}

class CallDlg : public QDialog
{
    Q_OBJECT

    void setjid(QString s)
    {
        selfjid = s;
    }
public:
    explicit CallDlg(QWidget *parent = 0);
    ~CallDlg();
public slots:
    void startCall();
    QXmppCall *call (const QString &jid);
private:
    Ui::CallDlg *ui;
    QString selfjid;
};

#endif // CALLDLG_H
