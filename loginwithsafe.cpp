
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QTcpSocket>
#include <QDomDocument>
#include <QDomElement>
#include <QTextCodec>

#include "loginwithsafe.h"

#define LOCAL(x)  QString::fromLocal8Bit(x)

LoginWithSafe::LoginWithSafe(QWidget *parent) :
    FramelessWin(parent)
{

    const char *code = "GBK";
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(code));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(code));
    QTextCodec::setCodecForTr(QTextCodec::codecForName(code));
    resize(430,330);
    QVBoxLayout *vlay = new QVBoxLayout();
    vlay->setSpacing(20);
    vlay->setContentsMargins(10,10,10,40);
    vlay->addWidget(initTop());
    vlay->addStretch();
    IconButton *okButton = new IconButton(this,":/ui/button_login_normal.png",":/ui/button_login_hover.png",
                                          ":/ui/button_login_down.png");
    okButton->AddTxtLabel();
    okButton->SetButtonText(LOCAL("在通行证中单击允许登录"));

    //connect(okButton,SIGNAL(clicked()),this,SLOT(okClick()));

    QLabel *lb = new QLabel();
    lb->setText(LOCAL("等待通行证端确认...."));
    lb->setStyleSheet(LOCAL("font: 75 16pt '楷体';"));
    vlay->addWidget(lb,0,Qt::AlignHCenter);
    vlay->addWidget(okButton,0,Qt::AlignHCenter );
    setLayout(vlay);
    QTimer timer(this);
    timer.singleShot(500,this,SLOT(okClick()));
}

QWidget *LoginWithSafe::initTop()
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

void LoginWithSafe::readyRead()
{
    QTcpSocket *m_sock = m_ping->m_sock;
    char buf[512] = "";
    QString jid,pwd;
    m_sock->read(buf,512);
    qDebug()<<"pong:"<<buf;
    QString res = QString::fromLocal8Bit(buf);
    QDomDocument    dom;
    if ( !dom.setContent(res))
        return ;
    QDomElement     elem = dom.documentElement();
    if ( elem.isNull())
        return ;
    jid = elem.attribute("id");
    pwd = elem.attribute("pwd");
    int pos = jid.indexOf("/");
    jid = jid.left(pos);
    emit LoginWithInfo(jid,pwd);
    accept();
}

void LoginWithSafe::okClick()
{
    //emit LoginSafe();
    //accept();

    QTcpSocket *m_sock = m_ping->m_sock;
    bool bcheck = connect(m_sock,SIGNAL(readyRead()),this,SLOT(readyRead()));
    char buf[512] = "";
    QString jid,pwd;

    sprintf(buf,"<ping app=\"%s\"/>","Q-IM.exe");
    qDebug()<<"ping:"<<buf;
    qint64 qi = m_sock->write(buf,strlen(buf));
    m_sock->waitForBytesWritten();

}

void LoginWithSafe::timerEvent(QTimerEvent *evt)
{

}
