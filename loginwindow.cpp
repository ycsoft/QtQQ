
//QT includes
#include <QMessageBox>
#include <QTextCodec>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QMovie>
#include <QLabel>
#include <QCheckBox>

//Custom includes
#include "loginwindow.h"
#include "listwindow.h"
#include "ui_loginwindow.h"
#include "qfiletrans.h"

#include "setdlg.h"
#include "skin/iconbutton.h"
#include "safe/safeping.h"

#include "loginwithsafe.h"

#include "session.h"



//QXmppClient* Loginwindow::client = NULL;
QFileTrans* Loginwindow::client = NULL;
Loginwindow* Loginwindow::instance_login = NULL;
Loginwindow::Loginwindow(QWidget *parent) :
    ShadowDlg(parent),
    ui(new Ui::Loginwindow)
{
    //ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    this->resize(435,330);
    QWidget *Top = initTopSkin();
    QVBoxLayout *mainLay = new QVBoxLayout();

    mainLay->setSpacing(0);

    mainLay->addWidget(Top);
    QWidget *midw = new QWidget(this);
    midw->setObjectName("midw");
    midw->setStyleSheet("background-color: rgb(173, 215, 241);");
    midw->setLayout( initMiddle());
    //mainLay->addItem(initMiddle());
    mainLay->addWidget(midw);
    setLayout(mainLay);

    QIcon   ico(":/Icon_tray.png");
    setWindowIcon(ico);
    //ui->passwordLine->setEchoMode(QLineEdit::Password);

    /*
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint;
        setWindowFlags(flags);
        */
   setWindowTitle(LOCAL("登陆"));
   readConfig();
   // client = new QXmppClient();
   client = new QFileTrans(this);
   instance_login = this;

    bool check = false;/* = connect(ui->loginBtt, SIGNAL(clicked()), this,
            SLOT(slotloginclick()));
    Q_ASSERT(check);*/
    check = connect(Loginwindow::getclient(), SIGNAL(disconnected()),this,
                        SLOT(slotdisconnected()));
    Q_ASSERT(check);
    check = connect(Loginwindow::getclient(), SIGNAL(error(QXmppClient::Error)), this,
                        SLOT(slotconnectError(QXmppClient::Error)));
    Q_ASSERT(check);
    /*connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(SetServer()));
    connect(ui->usernameLine,SIGNAL(textEdited(QString)),this,SLOT(userChange(QString)));
    connect(ui->passwordLine,SIGNAL(textEdited(QString)),this,SLOT(pwdChange(QString)));
    */
    check = connect(Loginwindow::getclient(),SIGNAL(connected()),this,
                       SLOT(slotconnected()));
    Q_ASSERT(check);
    chatserror = true;
    downloadflag = false;
    fileerror = true;
    connect(this,SIGNAL(slogined()),this,SLOT(logined()));
    QFile::remove(QDir::currentPath() + "/pyout.txt");


    SafePing    ping(this);
    if ( ping.ConnectToHost())
    {
        m_login_safe = new LoginWithSafe();
        m_login_safe->SetSafePing(&ping);
        connect(m_login_safe,SIGNAL(LoginWithInfo(QString,QString)),this,SLOT(LoginWithInfo(QString,QString)));
        m_login_safe->exec();
    }

    QString url = Session::Instance()->getURL();

}
Loginwindow::~Loginwindow()
{
    delete ui;
}
void Loginwindow::LoginWithInfo(QString jid, QString pwd)
{
    QString ip = SetDlg::Instance()->getip();
    QString svr = SetDlg::Instance()->getsvr();
    m_edit_user->setText(jid);
    m_edit_pwd->setText(pwd);
    client->login(jid,pwd,svr,ip);
}

///
/// \brief Loginwindow::slotloginclick
///
///原版：使用MD5算法对用户JID进行加密，使用加密后的串就行登录
///
///现版：不再使用MD5进行加密
///
///修改时间：2015-05-29
///
void Loginwindow::slotloginclick()
{
    QString jid = m_edit_user->text();
    qDebug() << jid;
    QString jid_md5 = jid;
    //QByteArray bb;
    //bb = QCryptographicHash::hash(jid.toAscii(), QCryptographicHash::Md5);
    //jid_md5.append(bb.toHex());
    //qDebug() << jid_md5;
    QString ip = SetDlg::Instance()->getip();
    QString svr = SetDlg::Instance()->getsvr();
    //"@conference.win-86k694khk26";
    QString pwd = m_edit_pwd->text();
    path = QDir::currentPath() + "/chat/";
    //client->login(jid,pwd,"win-86k694khk26","192.168.1.101");
     jid_md5_ = jid_md5;
     pwd_ = pwd;
     svr_ = svr;
     ip_ = ip;

     QDir* dir = new QDir;
     if(!dir->exists(path))
         dir->mkdir(path);
     chatpath = path + jid_md5_ + "/";
     if(!dir->exists(chatpath))
         dir->mkdir(chatpath);
     filepath = QDir::currentPath() + "/fileshare/";
     fserver = SetDlg::Instance()->getfserver();
     fileshare = SetDlg::Instance()->getfshare();
     fpath = path + "group/";
     client->login(jid_md5,pwd,svr,ip);
     delete dir;
     emit slogined();
     //logined();
}
void Loginwindow::slotconnected()
{
    disconnect(Loginwindow::getclient(),SIGNAL(connected()),this,
                          SLOT(slotconnected()));
    Listwindow* listwindow = new Listwindow();
    listwindow->moveToRightTop();
    listwindow->show();
    this->hide();

}

void Loginwindow::slotdisconnected()
{
    QMessageBox::information(0, LOCAL("消息提示"), LOCAL("连接断开"), 0);
    //client->login(jid_md5_, pwd_, svr_, ip_);
}

void Loginwindow::slotconnectError(QXmppClient::Error)
{

    QMessageBox::information(0, LOCAL("错误提示"), LOCAL("登陆失败"), 0);
    this->close();
}
//设置服务器
void Loginwindow::SetServer()
{
    SetDlg *sd = new SetDlg(0);
    sd->show();
}
void Loginwindow::readConfig()
{
    QSettings   set;
    QString usr = set.value("usr","").toString();
    QString svr = set.value("svr","").toString();
    QString ip  = set.value("ip","").toString();
    QString pwd = set.value("pwd","").toString();
    QString fserver = set.value("fserver","").toString();
    QString fpath = set.value("fpath","").toString();
    if (ip.isEmpty())
    {
        ip = "127.0.0.1";
        set.setValue("ip",ip);
    }
    if ( !usr.isEmpty())
        //ui->usernameLine->setText(usr);
        m_edit_user->setText(usr);
    if ( !pwd.isEmpty())
        //ui->passwordLine->setText(pwd);
        m_edit_pwd->setText(pwd);
}
void Loginwindow::closeEvent(QCloseEvent *e)
 {
     QApplication::exit(0);
 }
void Loginwindow::userChange(QString str)
{
   QSettings set;
    set.setValue("usr",str);
}
void Loginwindow::pwdChange(QString str)
{
    QSettings set;
    set.setValue("pwd",str);
}
QString Loginwindow::getjid_md5()
{
    return jid_md5_;
}
QString Loginwindow::getpwd()
{
    return pwd_;
}
QString Loginwindow::getsvr()
{
    return svr_;
}
QString Loginwindow::getip()
{
    return ip_;
}

QString Loginwindow::getfpath()
{
    return fpath;
}

QString Loginwindow::getfserver()
{
    return fserver;
}
QString Loginwindow::getfileshare()
{
    return fileshare;
}
bool Loginwindow::getchatsflag()
{
    return chatserror;
}
void Loginwindow::setchatsflag(bool flag)
{
    chatserror = flag;
}
void Loginwindow::setchatsstate(int s)
{
    chatsstate = s;
}
void Loginwindow::logined()
{

}
void Loginwindow::setfileflag(bool flag)
{
    fileerror = flag;
}
void Loginwindow::setfilestate(int s)
{
    filestate = s;
}
bool Loginwindow::getfileflag()
{
    return fileerror;
}
bool Loginwindow::getdownloadflag()
{
    return downloadflag;
}
void Loginwindow::chatthreadfinished()
{

}
void Loginwindow::filethreadfinished()
{}

//Added By X.D Yang
QWidget* Loginwindow::initTopSkin()
{
    QWidget  *topSkin = new QWidget(this);
    topSkin->setMinimumHeight(160);
    IconButton *setb = new IconButton(this,":/ui/btn_set_normal.png",":/ui/btn_set_hover.png",":/ui/btn_set_press.png");
    //IconButton *minb = new IconButton(this,":/ui/btn_mini_normal.png",":/ui/btn_mini_highlight.png",":/ui/btn_mini_down.png");
    IconButton *closeb = new IconButton(this,":/ui/btn_close_normal.png",":/ui/btn_close_highlight.png",":/ui/btn_close_down.png");
    topSkin->setStyleSheet("border-image: url(:/ui/logo-main.png);");

    QHBoxLayout *topLay = new QHBoxLayout();
    topLay->setMargin(0);
    topLay->addStretch();
    topLay->addWidget(setb,0,Qt::AlignRight | Qt::AlignTop);
    //topLay->addWidget(minb,0,Qt::AlignRight | Qt::AlignTop);
    topLay->addWidget(closeb,0,Qt::AlignRight | Qt::AlignTop);
    topSkin ->setLayout(topLay);

    connect(closeb,SIGNAL(clicked()),qApp,SLOT(quit()));

    connect(setb,SIGNAL(clicked()),this,SLOT(SetServer()));


    //connect(minb,SIGNAL(clicked()),this,SLOT(showMinimized()));
    return topSkin;
}

QHBoxLayout* Loginwindow::initMiddle()
{
    QVBoxLayout *photoLay = new QVBoxLayout();
    QLabel *lb_photo = new QLabel(this);
    QMovie  *movie = new QMovie((":/ui/head.gif"));
    movie->setScaledSize(QSize(80,80));
    lb_photo->setMovie(movie);
    movie->start();
    photoLay->addWidget(lb_photo,0,Qt::AlignTop);
    photoLay->addStretch();

    //用户名密码
    m_edit_user = new QLineEdit(this);
    m_edit_pwd  = new QLineEdit(this);
    m_edit_user->setPlaceholderText(LOCAL("用户账号"));
    m_edit_pwd->setPlaceholderText(LOCAL("密码"));
    m_edit_pwd->setEchoMode(QLineEdit::Password);

    m_edit_user->setMinimumWidth(200);
    m_edit_user->setMaximumWidth(200);
    m_edit_pwd->setMinimumWidth(200);
    connect(m_edit_user,SIGNAL(textEdited(QString)),this,SLOT(userChange(QString)));
    connect(m_edit_pwd,SIGNAL(textEdited(QString)),this,SLOT(pwdChange(QString)));

    //提示标签
    QLabel *lb_regusr = new QLabel(LOCAL("注册用户"));
    lb_regusr->setStyleSheet("color: rgb(85, 85, 255);");

    //找回密码
    QLabel *lb_findpwd = new QLabel(LOCAL("找回密码"));
    lb_findpwd->setStyleSheet("color: rgb(85, 85, 255);");
    IconButton *okButton = new IconButton(this,":/ui/button_login_normal.png",":/ui/button_login_hover.png",
                                          ":/ui/button_login_down.png");
    okButton->AddTxtLabel();
    okButton->SetTextStyle("color: rgb(255, 255, 255);font: 75 9pt 'Aharoni';");
    okButton->SetButtonText(LOCAL("登      录"));
    bool bcheck = connect(okButton,SIGNAL(clicked()), this,SLOT(slotloginclick()));
    Q_ASSERT(bcheck);
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
    QCheckBox *remPwd = new QCheckBox(LOCAL("记住密码"),this);
    QCheckBox *autoLogin = new QCheckBox(LOCAL("自动登录"),this);
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
