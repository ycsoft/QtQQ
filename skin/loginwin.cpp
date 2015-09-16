
#include <QLabel>
#include <QMovie>
#include <QCheckBox>
#include <QApplication>

#include "loginwin.h"
#include "iconbutton.h"


LoginWin::LoginWin(QWidget *parent) :
    ShadowDlg(parent)
{
    this->resize(435,330);
    QWidget *Top = initTopSkin();
    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->addWidget(Top);
    mainLay->addItem(initMiddle());
    setLayout(mainLay);
}


QWidget* LoginWin::initTopSkin()
{
    QWidget  *topSkin = new QWidget(this);
    topSkin->setMinimumHeight(160);
    IconButton *setb = new IconButton(this,":/ui/btn_set_normal.png",":/ui/btn_set_hover.png",":/ui/btn_set_press.png");
    //IconButton *minb = new IconButton(this,":/ui/btn_mini_normal.png",":/ui/btn_mini_highlight.png",":/ui/btn_mini_down.png");
    IconButton *closeb = new IconButton(this,":/ui/btn_close_normal.png",":/ui/btn_close_highlight.png",":/ui/btn_close_down.png");
    topSkin->setStyleSheet("border-image: url(:/ui/morning.jpg);");

    QHBoxLayout *topLay = new QHBoxLayout();
    topLay->setMargin(0);
    topLay->addStretch();
    topLay->addWidget(setb,0,Qt::AlignRight | Qt::AlignTop);
    //topLay->addWidget(minb,0,Qt::AlignRight | Qt::AlignTop);
    topLay->addWidget(closeb,0,Qt::AlignRight | Qt::AlignTop);
    topSkin ->setLayout(topLay);

    connect(closeb,SIGNAL(clicked()),qApp,SLOT(quit()));
    //connect(minb,SIGNAL(clicked()),this,SLOT(showMinimized()));
    return topSkin;
}

QHBoxLayout* LoginWin::initMiddle()
{
    QVBoxLayout *photoLay = new QVBoxLayout();
    QLabel *lb_photo = new QLabel(this);
    QMovie  *movie = new QMovie(":/ui/head.gif");
    movie->setScaledSize(QSize(80,80));
    lb_photo->setMovie(movie);
    movie->start();
    photoLay->addWidget(lb_photo,0,Qt::AlignTop);
    photoLay->addStretch();

    //用户名密码
    m_edit_user = new QLineEdit(this);
    m_edit_pwd  = new QLineEdit(this);
    m_edit_user->setPlaceholderText("用户账号");
    m_edit_pwd->setPlaceholderText("密码");
    m_edit_pwd->setEchoMode(QLineEdit::Password);

    m_edit_user->setMinimumWidth(200);
    m_edit_user->setMaximumWidth(200);
    m_edit_pwd->setMinimumWidth(200);

    //提示标签
    QLabel *lb_regusr = new QLabel("注册用户");
    lb_regusr->setStyleSheet("color: rgb(85, 85, 255);");

    //找回密码
    QLabel *lb_findpwd = new QLabel("找回密码");
    lb_findpwd->setStyleSheet("color: rgb(85, 85, 255);");
    IconButton *okButton = new IconButton(this,":/ui/button_login_normal.png",":/ui/button_login_hover.png",
                                          ":/ui/button_login_down.png");
    okButton->AddTxtLabel();
    okButton->SetTextStyle("color: rgb(255, 255, 255);font: 75 9pt 'Aharoni';");
    okButton->SetButtonText("登      录");

    //用户账号输入
    QHBoxLayout  *layUser = new QHBoxLayout();
    layUser->setMargin(0);
    layUser->setSpacing(10);
    layUser->addWidget(m_edit_user,0,Qt::AlignLeft | Qt::AlignTop);
    //layUser->addWidget(lb_regusr);

    //用户密码输入
    QHBoxLayout *layPwd = new QHBoxLayout();
    layPwd->setMargin(0);
    layPwd->setSpacing(10);
    layPwd->addWidget(m_edit_pwd,0,Qt::AlignLeft | Qt::AlignTop);
    //layPwd->addWidget(lb_findpwd);

    //合并用户名密码布局
    QVBoxLayout *inputLay = new QVBoxLayout();
    inputLay->setSpacing(0);
    inputLay->addStretch();
    inputLay->addItem(layUser);
    inputLay->addItem(layPwd);

    //复选框
    QCheckBox *remPwd = new QCheckBox("记住密码",this);
    QCheckBox *autoLogin = new QCheckBox("自动登录",this);
    QString   style = "color: rgb(141, 141, 141);";

    remPwd->setStyleSheet(style);
    autoLogin->setStyleSheet(style);

    QHBoxLayout *checkLay = new QHBoxLayout();
    checkLay->setContentsMargins(0,10,0,0);
    checkLay->addWidget(remPwd);
    checkLay->addStretch();
    checkLay->addWidget(autoLogin);
    checkLay->addStretch();
    inputLay->addItem(checkLay);
    //添加按钮
    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->setContentsMargins(0,10,0,0);
    btnLay->addWidget(okButton,0,Qt::AlignLeft | Qt::AlignTop);
    okButton->setMinimumWidth(m_edit_user->width());
    okButton->setMaximumWidth(m_edit_user->width());

    //btnLay->addStretch();
    inputLay->addItem(btnLay);

    //总布局
    QHBoxLayout *contentLay = new QHBoxLayout();
    contentLay->setMargin(20);
    contentLay->setSpacing(20);
    contentLay->addItem(photoLay);
    contentLay->addItem(inputLay);
    return contentLay;
}
