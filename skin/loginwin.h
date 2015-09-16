#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>


#include "shadowdlg.h"

class LoginWin : public ShadowDlg
{
    Q_OBJECT
public:
    explicit LoginWin(QWidget *parent = 0);

private:
    QWidget             *initTopSkin();
    QHBoxLayout         *initMiddle();

    QLineEdit           *m_edit_user;
    QLineEdit           *m_edit_pwd;

signals:

public slots:

};

#endif // LOGINWIN_H
