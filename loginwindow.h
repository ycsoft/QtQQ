#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QXmppClient.h>
#include <QXmppLogger.h>
#include <QString>
#include <QXmppCallManager.h>
#include <QCryptographicHash>
#include <QByteArray>
#include <QHBoxLayout>
#include <QLineEdit>

#include "skin/shadowdlg.h"
#include "skin/iconbutton.h"
#include "loginwithsafe.h"

#define LOCAL(x)  QString::fromLocal8Bit(x)
class QFileTrans;
namespace Ui {
class Loginwindow;
}

class Loginwindow : public ShadowDlg
{
    Q_OBJECT

public:
    explicit Loginwindow(QWidget *parent = 0);

    static QFileTrans * getclient()
    {
        return client;
    }

    ~Loginwindow();
     void closeEvent(QCloseEvent *e);
     void readConfig();
     static Loginwindow* getloginInstance()
     {
         return instance_login;
     }
     QString getjid_md5();
     QString getpwd();
     QString getsvr();
     QString getip();
     QString chatpath;
     QString getfileshare();
public slots:
     //登录按钮单击槽
    void slotloginclick();
    //用户已成功连接
    void slotconnected();
    //用户断开连接
    void slotdisconnected();
    //连接出错
    void slotconnectError(QXmppClient::Error);
    void SetServer();//设置服务器
    void userChange(QString str);
    void pwdChange(QString str);
    QString getfpath();
    QString getfserver();
    bool getchatsflag();
    void setchatsflag(bool);
    void setchatsstate(int);
    bool getfileflag();
    void setfilestate(int);
    void setfileflag(bool);
    void logined();
    bool getdownloadflag();
    void chatthreadfinished();
    void filethreadfinished();
    //通过通行证进行登录
    void LoginWithInfo(QString jid,QString pwd);

private:
    Ui::Loginwindow *ui;
   static     QFileTrans* client;
  // static QXmppClient *client;
   QString jid_md5_;
   QString pwd_;
   QString svr_;
   QString ip_;
   static Loginwindow* instance_login;
   QString fserver;
   QString fpath;
   QString path;
   QString fileshare;
   QString filepath;
   bool chatserror;
   int chatsstate;
   bool fileerror;
   int filestate;
   bool downloadflag;
signals:
   void slogined();
private:
   //Added BY X.D Yang
   QWidget             *initTopSkin();
   QHBoxLayout         *initMiddle();

   QLineEdit           *m_edit_user;
   QLineEdit           *m_edit_pwd;
   LoginWithSafe       *m_login_safe;
};

#endif // LOGINWINDOW_H
