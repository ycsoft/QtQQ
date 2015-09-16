#ifndef SETDLG_H
#define SETDLG_H

#include <QDialog>
#define LOCAL(x)  QString::fromLocal8Bit(x)
namespace Ui {
class SetDlg;
}

class SetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SetDlg(QWidget *parent = 0);
    ~SetDlg();
    QString getip();
    QString getsvr();
    QString getfshare();
    QString getfserver();
   static   SetDlg *Instance();

public slots:
    void slotclose();
private:
    Ui::SetDlg *ui;
     static SetDlg* m_instance;
};

#endif // SETDLG_H
