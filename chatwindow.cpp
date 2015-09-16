#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "loginwindow.h"
#include "qfiletrans.h"
#include "findfriend.h"
#include "filereceivedlg.h"
#include <QTextStream>
//#include "calldlg.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <list>
#include <QtWebKit>
#include <QWebFrame>

#include "searchdlg.h"

Chatwindow* Chatwindow::m_instance=NULL;
Chatwindow::Chatwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chatwindow)
{
    ui->setupUi(this);
    ui->webView->setMinimumHeight(150);
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint;
        //setWindowFlags(flags);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QFile source(":/style.html");
    source.open(QIODevice::ReadOnly);
    ui->webView->setHtml(QString::fromUtf8(source.readAll().constData()));
    source.close();
    this->setWindowTitle(LOCAL("聊天窗口"));
    //ui->FindBtt->setText(LOCAL("查找用户"));

    QPixmap pixmap(":/Icon_find.png");
    QIcon icon;
    icon.addPixmap(pixmap);
    ui->FindBtt->setIcon(icon);
    ui->FindBtt->setMaximumWidth( ui->FindBtt->width() + 20);

    //QPixmap pixmap(":/Icon_add.png");
    //icon.addPixmap(pixmap);
    //ui->add_btt->setIcon(icon);
    QPixmap pixmap1(":/Icon_send.png");
    icon.addPixmap(pixmap1);
    ui->call_btt->setIcon(icon);
    QPixmap pixmap2(":/Icon_call.png");
    icon.addPixmap(pixmap2);
    ui->send_btt->setIcon(icon);
    QPixmap pixmap3(":/Icon_call_stop.png");
    icon.addPixmap(pixmap3);
    ui->send_stop->setIcon(icon);
    ui->send_stop->setEnabled(false);
    chat = new chats(this);
    filesend = false;
    filejob = NULL;
    msgflag = true;
    called = false;

    //ui->send_btt->SetButtonText(LOCAL("发起语音"));
    //ui->send_stop->SetButtonText(LOCAL("停止"));
    //ui->call_btt->SetButtonText(LOCAL("发送文件"));

    connect(ui->call_btt,SIGNAL(clicked()),this,SLOT(slotSendfile()));
    connect(ui->bt_chats,SIGNAL(clicked()),this,SLOT(setchats()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(ui->pushButton_2,SIGNAL(clicked()),ui->textEdit_2,SLOT(clear()));
    //connect(ui->add_btt,SIGNAL(clicked()),this,SLOT(addFriend()));
    connect(ui->send_btt,SIGNAL(clicked()),this,SLOT(sendcall()));
    connect(Listwindow::getcallmanager(), SIGNAL(callReceived(QXmppCall*)), this, SLOT(slotcallrecieved(QXmppCall*)));
    connect(ui->send_stop, SIGNAL(clicked()), this, SLOT(slotcallstop()));
    connect(Loginwindow::getclient()->transferManager, SIGNAL(jobStarted(QXmppTransferJob*)), SLOT(slotjobstarted(QXmppTransferJob*)));
    connect(ui->webView->page(),SIGNAL(repaintRequested(QRect)),this,SLOT(slotmessageload(QRect)));

    connect(ui->FindBtt,SIGNAL(clicked()),this,SLOT(slot_findfriend()));

    ui->webView->setStyleSheet("background-color: rgb(238, 237, 255);");
    ui->textEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 237, 255);"));
}
Chatwindow *Chatwindow::Instance()
{
    return m_instance;
}
void Chatwindow::slotcallstop()
{
    call->hangup();
}

//文件发送消息处理
void Chatwindow::slotjobstarted(QXmppTransferJob * job)
{

    qDebug()<<"filesend Start";
    if(!filesend)
        return;
    filesend = false;
    FileReceiveDlg *fileRcv = new FileReceiveDlg(this);
    QString fn = job->fileName();
    QString recver =  Listwindow::Instance()->Jidtonick(chatjid_.split("/").at(0));
    if(recver.isNull())
        recver = chatjid_;
    //QString recver = ui->label->text();
    qint64  size = job->fileSize();
    fileRcv->setWindowTitle(LOCAL("发送文件"));
    connect(job, SIGNAL(progress(qint64,qint64)), fileRcv, SLOT(slotProgress(qint64,qint64)));
    connect(job,SIGNAL(finished()),fileRcv,SLOT(slotfinished()));
    connect(job,SIGNAL(error(QXmppTransferJob::Error)),fileRcv,SLOT(sloterror(QXmppTransferJob::Error)));
    fileRcv->setFileName(fn);
    fileRcv->setbuttonstop();
    fileRcv->setSize(size);
    fileRcv->changetosenddlg(recver);
    fileRcv->setfilejob(job);
    int res = fileRcv->exec();
    if ( res == 11 )
    {
        job->accept(fn);
        fileRcv->show();
    }
}

//发起语音
void Chatwindow::sendcall()
{
    QMessageBox message(QMessageBox::NoIcon, LOCAL("发起语音"), LOCAL("确定向")+chatjid_+LOCAL("发起语音？"),QMessageBox::Yes|QMessageBox::No);
    if(QMessageBox::Yes == message.exec())
    {
        QString body = Listwindow::Instance()->getselfJID() + LOCAL("向") + chatjid_ + LOCAL("发起语音邀请");
        Loginwindow::getclient()->sendMessage(chatjid_, body);
        startcall(chatjid_);
    }
}

void Chatwindow::startcall(QString jid)
{
    call = Listwindow::getcallmanager()->call(jid);
    bool check = connect(call, SIGNAL(stateChanged(QXmppCall::State)),
                    this, SLOT(slotCallStateChanged(QXmppCall::State)));
    Q_ASSERT(check);

    check = connect(call, SIGNAL(audioModeChanged(QIODevice::OpenMode)),
                    this, SLOT(slotAudioModeChanged(QIODevice::OpenMode)));
    Q_ASSERT(check);
    //connect(call, SIGNAL(connected()), this, SLOT(slotcallconnected()));
    //connect(call, SIGNAL(finished()), this, SLOT(slotcallfinished()));
}


void Chatwindow::slotcallrecieved(QXmppCall *call_)
{
    if(called)
        return;
    call = call_;
    QString jid = call->jid();
    if(jid != this->windowTitle())
        return;
    bool check = connect(call, SIGNAL(stateChanged(QXmppCall::State)),
                    this, SLOT(slotCallStateChanged(QXmppCall::State)));
    Q_ASSERT(check);

    check = connect(call, SIGNAL(audioModeChanged(QIODevice::OpenMode)),
                    this, SLOT(slotAudioModeChanged(QIODevice::OpenMode)));
    Q_ASSERT(check);
    called = true;

    if (QMessageBox::Yes == QMessageBox::information(this, LOCAL("语音邀请"), jid + LOCAL("邀请您进行语音通话"),
                                                        QMessageBox::Yes|QMessageBox::No))
    {
        call->accept();
    }
    else
    {
        call->hangup();
    }
}

void Chatwindow::slotCallStateChanged(QXmppCall::State state)
{
    if (state == QXmppCall::ActiveState)
    {
        ui->send_stop->setEnabled(true);
        ui->send_btt->setEnabled(false);
        qDebug("Call active");
    }
    else if (state == QXmppCall::DisconnectingState)
    {
        ui->send_btt->setEnabled(true);
        ui->send_stop->setEnabled(false);
        //QMessageBox::information(this, LOCAL("语音错误"), LOCAL("语音连接断开"), 0);
        called = false;
    }
    else if (state == QXmppCall::FinishedState)
    {
        ui->send_btt->setEnabled(true);
        ui->send_stop->setEnabled(false);
        QMessageBox::information(this, LOCAL("语音结束"), LOCAL("语音通话结束"), 0);
        called = false;
    }
}

void Chatwindow::setcall(QXmppCall *call_)
{
    call = call_;
}

void Chatwindow::slotAudioModeChanged(QIODevice::OpenMode mode)
{
    QXmppCall *call = qobject_cast<QXmppCall*>(sender());
    Q_ASSERT(call);
    QXmppRtpAudioChannel *channel = call->audioChannel();
    // prepare audio format
    QAudioFormat format;
    format.setFrequency(channel->payloadType().clockrate());
    format.setChannels(channel->payloadType().channels());
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    // the size in bytes of the audio buffers to/from sound devices
    // 160 ms seems to be the minimum to work consistently on Linux/Mac/Windows
    const int bufferSize = (format.frequency() * format.channels() * (format.sampleSize() / 8) * 160) / 1000;

    if (mode & QIODevice::ReadOnly) {
        // initialise audio output
        QAudioOutput *audioOutput = new QAudioOutput(format, this);
        audioOutput->setBufferSize(bufferSize);
        audioOutput->start(channel);
    }

    if (mode & QIODevice::WriteOnly) {
        // initialise audio input
        QAudioInput *audioInput = new QAudioInput(format, this);
        audioInput->setBufferSize(bufferSize);
        audioInput->start(channel);
    }
}


// 发送文件
void Chatwindow::slotSendfile()
{
    sf_ = new SendFiles(this);
    sf_->getSendtojid(this->getChatJid());
    sf_->show();
}
 // 发送消息
void Chatwindow::sendMessage()
{
    QString body= ui->textEdit_2->toPlainText();
    if(body.isEmpty())
    {
        QMessageBox::information(this,LOCAL("提示"),LOCAL("不能发送空消息"),0);
        return;
    }
    QString jid = chatjid_;
    Loginwindow::getclient()->sendMessage(jid,body);
    addMessage(LOCAL("我"),body);
}
//设置窗体名称
void Chatwindow::setTitle(QString str)
{
    ui->label->setText(str);
}
//获取时间
QString Chatwindow::getCurrentTime()
{
    QDateTime  dt = QDateTime::currentDateTime();
    QString format = tr("hh:mm:ss");
    QString ret = tr("[ ")+dt.toString(format) + tr(" ]");
    return ret;
}
void Chatwindow::handleMessage(QString fromjid,QString msg)
{
  //  QString nick = Listwindow::getNickFromJid(fromjid);
    if(fromjid.compare(chatjid_) != 0)
        return;
    msgflag = true;
    QFont serifFont("Times", 12, QFont::Bold);
    QString fname = Loginwindow::getloginInstance()->chatpath + chatjid_.split('@').at(0);
    QFile fd(fname);
    if(!fd.open(QIODevice::Append))
    {
        QMessageBox::information(this,LOCAL("警告"),LOCAL("无法打开聊天记录文件"),0);
    }
    //if (getChatType() == CommonChat && fromjid.compare(chatjid_) != 0)
    QString time = getCurrentTime();
    QString message = time;
  //  ui->webView->setTextColor(QColor(170, 0, 127));
    ui->webView->setFont(serifFont);
    QStringList str1=fromjid.split("/");
    QString str =  Listwindow::Instance()->Jidtonick(str1.at(0));
    if(str.isEmpty())
    {
        str = fromjid;
    }
    message += ":";
    message += msg;

    message.replace("\n","<br>");
    message.replace("\\","\\\\");
    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='recver'>");
    html.append(str);
    html.append(QString("</p><p class='triangle-left left'>%1</p></div>\")").arg(message));
    ui->webView->page()->mainFrame()->evaluateJavaScript(html);
    QString m = time + str + ":" + msg + "\n";
    QByteArray b = m.toLocal8Bit().toBase64() + '\n';
    fd.write(b);
    fd.close();
}
 // // 添加消息
void Chatwindow::addMessage(QString fromjid, QString msg)
{
    msgflag = true;
    QString fname = Loginwindow::getloginInstance()->chatpath + chatjid_.split('@').at(0);
    //QDir dir = new QDir;
    QFile fd(fname);
    if(!fd.open(QIODevice::Append))
    {
        QMessageBox::information(this,LOCAL("警告"),LOCAL("无法打开聊天记录文件"),0);
    }

    QString time = getCurrentTime();
    QString m = time + fromjid + ":" + msg + "\n";
    QString message = time + ":" + msg;

    message.replace("\n","<br>");
    message.replace("\\","\\\\");

    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='sender'>");
    html.append(fromjid);
    html.append(QString("</p><p class='triangle-right right'>%1</p></div>\")").arg(message));
    ui->webView->page()->mainFrame()->evaluateJavaScript(html);
    QByteArray b = m.toLocal8Bit().toBase64() + '\n';
    fd.write(b);
    fd.close();
}

void Chatwindow::scrollToBottom()
{
    int h = ui->webView->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    ui->webView->page()->mainFrame()->setScrollBarValue(Qt::Vertical,h);
}
//加好友
/*
void Chatwindow::addFriend()
{
    FindFriend *ff =new FindFriend(this);
    ff->show();
}
*/
Chatwindow::~Chatwindow()
{
    delete chat;
    delete ui;
}
void Chatwindow::closeEvent(QCloseEvent *e)
{
    this->close();
    qDebug()<<"close";
    showed = false;
    if(called)
        call->hangup();
    QString id = this->windowTitle();
    Listwindow::Instance()->setchattray(id.split("/").at(0),true);//接受托盘提示
    Listwindow::Instance()->setChatlist(chatjid_);
}
void Chatwindow::slotclosed()
{
    this->close();
    qDebug()<<"close";
    if(called)
        call->hangup();
    showed = false;//在语音处引用
    QString id = this->windowTitle();
    Listwindow::Instance()->setchattray(id.split("/").at(0),true);//接受托盘提示
    Listwindow::Instance()->setChatlist(chatjid_);
}
void Chatwindow::setWinname(QString s)
{
    qDebug() << s;
    if(s == "")
    {
        ui->label->setText("");
    }
    else
    {
        ui->label->setText("");
    }
}
void Chatwindow::keyPressEvent(QKeyEvent *e)
{
    if (e->type() == QEvent::KeyPress)
       {
           QKeyEvent *event = static_cast<QKeyEvent*>(e);
           if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
           {
               sendMessage();
               ui->textEdit_2->clear();
           }
     }
}

void Chatwindow::setchats()
{
    chat->clear();
    QString fname = Loginwindow::getloginInstance()->chatpath + chatjid_.split('@').at(0);
    QFile fd(fname);
    if(!fd.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,LOCAL("警告"),LOCAL("无法打开聊天记录文件"),0);
    }
    QByteArray allchats = fd.readLine();
    while(!allchats.isNull())
    {
        QString chattext = QString::fromLocal8Bit(QByteArray::fromBase64(allchats));
        chat->setchatsedit(chattext);
        allchats = fd.readLine();
    }
    chat->show();
}

void Chatwindow::chat_initwindow()
{
    QString fname = chatjid_.split('@').at(0);
    QFile fd(Loginwindow::getloginInstance()->chatpath + fname);
    chat->clear();
    if(!fd.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,LOCAL("警告"),LOCAL("无法打开聊天记录文件"),0);
        return;
    }
    QTextStream ts(&fd);
    QString str_chat = ts.readAll();
    QStringList chatlist = str_chat.split('\n');
    if(chatlist.isEmpty())
    {
        return;
    }
    int i = chatlist.count();
    if(i > 20)
        i = 20;
    while(--i)
    {
        QString strtext = chatlist.at(chatlist.count() - i);
        QString strtext1 = QString::fromLocal8Bit(QByteArray::fromBase64(strtext.toLocal8Bit()));
        if(strtext1.isEmpty())
            return;
        QString senderinfo = strtext1.split("]").at(1);
        QString message = strtext1.split("]").at(0) + "]";
        QString sender = senderinfo.split(":").at(0);
        message += ":";
        message += senderinfo.split(":").at(1);
        message.replace("\n","<br>");
        message.replace("\\","\\\\");
        if(sender == LOCAL("我"))
        {
            QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='sender'>");
            html.append(sender);
            html.append(QString("</p><p class='triangle-right right'>%1</p></div>\")").arg(message.split('\n').at(0)));
            ui->webView->page()->mainFrame()->evaluateJavaScript(html);
        }
        else
        {
            QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='recver'>");
            html.append(sender);
            html.append(QString("</p><p class='triangle-left left'>%1</p></div>\")").arg(message.split('\n').at(0)));
            ui->webView->page()->mainFrame()->evaluateJavaScript(html);
        }
    }
    fd.close();
}

void Chatwindow::setsendflag(bool flag)
{
    filesend = flag;
}
void Chatwindow::slotmessageload(QRect)
{
    if(msgflag)
    {
        scrollToBottom();
        msgflag = false;
    }
}

void Chatwindow::slot_findfriend()
{
    SearchDlg *sd = new SearchDlg(this);
    sd->show();
}

void Chatwindow::setshowd(bool flag)
{
    showed = flag;
}

bool Chatwindow::getshowd()
{
    return showed;
}
void Chatwindow::calling()
{
    ui->send_stop->setEnabled(true);
    ui->send_btt->setEnabled(false);
}
