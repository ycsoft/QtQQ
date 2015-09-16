#ifndef LOGINWITHSAFE_H
#define LOGINWITHSAFE_H

#include <QWidget>
#include <QTimerEvent>


#include "skin/framelesswin.h"
#include "skin/iconbutton.h"
#include "safe/safeping.h"

class LoginWithSafe : public FramelessWin
{
    Q_OBJECT
public:
    explicit LoginWithSafe(QWidget *parent = 0);

    void    SetSafePing(SafePing *ping)             { m_ping = ping;}
    QWidget *initTop();

    void    timerEvent(QTimerEvent *);

    void    SetupUI() {}


signals:
    void    LoginSafe();
    void    LoginWithInfo(QString jid,QString pwd);
public slots:
    void    okClick();
    void    readyRead();

private:
    SafePing    *m_ping;

};

#endif // LOGINWITHSAFE_H
