#include "mucroom.h"
#include "ui_mucroom.h"
#include "ui_widget.h"
#include "session.h"

#include <QtWebKit>
#include <QMenu>
#include <QWebFrame>
#include <QTextCodec>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFile>



Mucroom::Mucroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mucroom)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    //flags |=Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint;
    //setWindowFlags(flags);
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QFile source(":/style.html");
    source.open(QIODevice::ReadOnly);
    ui->webView->setHtml(QString::fromUtf8(source.readAll().constData()));
    source.close();
    msgflag = true;
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(sendMucMessage()));
    connect(ui->pushButton_2,SIGNAL(clicked()),ui->textEdit_2,SLOT(clear()));
    connect(ui->webView->page(),SIGNAL(repaintRequested(QRect)),this,SLOT(slotloadmessage(QRect)));
//    connect(ui->bt_pull,SIGNAL(clicked()),this,SLOT(slotpull()));
//    connect(ui->bt_push,SIGNAL(clicked()),this,SLOT(slotcommit()));
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(flushfilelist(int)));
//    connect(ui->file_list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(openfile(QModelIndex)));
//    connect(ui->bt_add,SIGNAL(clicked()),this,SLOT(slotaddfile()));

    connect(ui->bt_chat,SIGNAL(clicked()),this,SLOT(getchats()));
//    set_path(Listwindow::Instance()->getcurrentpath() + "/fileshare/");
//    set_remotepath(Loginwindow::getloginInstance()->getfileshare());

//    ui->version_list->setHeaderLabels(QStringList()<<LOCAL("时间")<<LOCAL("提交信息")<<LOCAL("提交者")<<LOCAL("版本号"));
//    ui->file_list->setColumnWidth(0,ui->version_list->width()/4);
//    ui->version_list->show();
//    ui->file_list->setColumnCount(3);
//    ui->file_list->setHeaderLabels(QStringList()<<LOCAL("时间")<<LOCAL("提交者")<<LOCAL("提交信息"));
//    ui->file_list->setColumnWidth(0,ui->file_list->width()/4);
//    ui->file_list->show();

    chat = new chats(this);

    connect( ui->file_wid->ui->pushButton,SIGNAL(clicked()),this,SLOT(filepush()));
    connect(ui->file_wid->ui->returnButton,SIGNAL(clicked()),this,SLOT(slotpull()));

}

Mucroom::~Mucroom()
{
    delete ui;
}

void Mucroom::setparticipantNickname(QString name)
{
    participantNickname = name;
}

void Mucroom::slotclosed()
{
}

void Mucroom::setroomname(QString name)
{
    roomname_ = name;
    //ui->label_roomname->setText(name);
}
void Mucroom::joinroom(QString roomJid)
{
    roomJid_ = roomJid;
    this->setWindowTitle(roomJid);
    QXmppMucRoom* room = Listwindow::getMucmanager()->addRoom(roomJid);
    mucroom_addr = room;
    bool check = connect(room, SIGNAL(participantAdded(QString)), this,
                         SLOT(showlist(QString)));
    check = connect(room,SIGNAL(participantRemoved(QString)),this,SLOT(removelist(QString)));
    Q_ASSERT(check);
    room->setNickName(participantNickname);
    room->join();
}
void Mucroom::removelist(QString paticipantJID)
{
    QStringList str1 = paticipantJID.split("/");
    QString str = str1.at(1);
    QList<QListWidgetItem*> l = ui->list_chatroom->findItems(str,0);
    if(l.isEmpty())
        return;
    int i = ui->list_chatroom->row(l.at(0));
    if(i < 0)
        return;
    QListWidgetItem* item =  ui->list_chatroom->takeItem(i);
    delete item;
}
void Mucroom::showlist(QString participantJID)
{
    QStringList str1=participantJID.split("/");
    QString str = str1.at(1);
    ui->list_chatroom->addItem(str);
}

QString Mucroom::getmucroomJid(QString roomJid)
{
    return roomJid_;
}
void Mucroom::sendMucMessage()
{
    QString msg = ui->textEdit_2->toPlainText();
    mucroom_addr->sendMessage(msg);
    addMessage(LOCAL("我"),msg);
}
void Mucroom::addMessage(QString fromjid, QString msg)
{
    msgflag = true;
    QFont  font = ui->webView->font();
    QString time = getCurrentTime();
    ui->webView->setFont(font);
    QString message = time + ":" + msg;
    message.replace("\n","<br>");
    message.replace("\\","\\\\");
    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='sender'>");
    html.append(fromjid);
    html.append(QString("</p><p class='triangle-right right'>%1</p></div>\")").arg(message));
    ui->webView->page()->mainFrame()->evaluateJavaScript(html);

    QString fname = Loginwindow::getloginInstance()->chatpath + roomname_;
    QFile fd(fname);

    if(!fd.open(QIODevice::Append))
    {
        QMessageBox::information(this,LOCAL("警告"),LOCAL("无法记录聊天记录"),0);
        return;
    }

    QString m = time + fromjid + ":" + msg + "\n";
    QByteArray b = m.toLocal8Bit().toBase64() + '\n';
    fd.write(b);
    fd.close();
}
void Mucroom::scrollToBottom()
{
    int h = ui->webView->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    ui->webView->page()->mainFrame()->setScrollBarValue(Qt::Vertical,h);
}
QString Mucroom::getCurrentTime()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString format = tr("hh:mm:ss");
    QString ret = tr("[ ")+dt.toString(format) + tr(" ]");
    return ret;
}
void Mucroom::handleMessage(QString fromjid,QString msg)
{
    msgflag = true;
    QFont serifFont("Times", 12, QFont::Bold);
    QString time = getCurrentTime();
    ui->webView->setFont(serifFont);
    QString message = time;
    message += ":";
    message += msg;
    message.replace("\n","<br>");
    message.replace("\\","\\\\");
    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='recver'>");
    html.append(fromjid);
    html.append(QString("</p><p class='triangle-left left'>%1</p></div>\")").arg(message));
    ui->webView->page()->mainFrame()->evaluateJavaScript(html);

    QString fname = Loginwindow::getloginInstance()->chatpath + roomname_;
    QFile fd(fname);

    if(!fd.open(QIODevice::Append))
    {
        QMessageBox::information(this,LOCAL("警告"),LOCAL("无法记录聊天记录"),0);
        return;
    }

    QString m = time + fromjid + ":" + msg + "\n";
    qDebug()<<m;
    QByteArray b = m.toLocal8Bit().toBase64() + '\n';
    fd.write(b);
    fd.close();
}
void Mucroom::keyPressEvent(QKeyEvent *e)
{
    if (e->type() == QEvent::KeyPress)
       {
           QKeyEvent *event = static_cast<QKeyEvent*>(e);
           if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
           {
               sendMucMessage();
               ui->textEdit_2->clear();
           }
      }
}

void Mucroom::slotloadmessage(QRect)
{
    if(msgflag)
    {
        scrollToBottom();
        msgflag = false;
    }
}

void Mucroom::filepush()
{/*
    v_list.clear();
    f_list.clear();
    ui->version_list->clear();
    ui->file_list->clear();
    list<string> vlist = //Git_client::getclient()->history(path);
    if(vlist.empty())
        return;
    list<string>::iterator i = vlist.begin();
    for(; i != vlist.end(); ++i)
    {
        v_list.append(QString::fromStdString(*i));
    }
    QHash<QString,QStringList> h_info;
    QList<QString>::iterator it = v_list.begin();
    int j = 0;
    for(; it!=v_list.end(); ++it)
    {
        qDebug() << *it;
        QString content = *it;
        QStringList arr = content.split(",");
        QString author = arr.at(0);
        QString msg = arr.at(1);
        QString time = arr.at(2);
        QString version = arr.at(4);
        QStringList info_str;
        info_str.append(time);
        info_str.append(LOCAL(author.toLocal8Bit()));
        info_str.append(LOCAL(msg.toLocal8Bit()));
        h_info.insert(version,info_str);
        QStringList str;
        str.append(time);
        str.append(LOCAL(msg.toLocal8Bit()));
        str.append(LOCAL(author.toLocal8Bit()));
        str.append(version);
        QVariant var0(version);
        QTreeWidgetItem* itemroot = new QTreeWidgetItem(str);
        ui->version_list->addTopLevelItem(itemroot);
        itemroot->setData(0,Qt::UserRole,var0);
        ++j;
    }
    qDebug()<<"the length is:"<<j<<endl;
    ui->version_list->show();
    //QMessageBox::information(this,"","",0);
    list<string> flist = //Git_client::getclient()->file_history(path);
    if(flist.empty())
        return;
    list<string>::iterator t = flist.begin();
    for(;t!=flist.end();++t)
    {
        f_list.append(QString::fromStdString(*t));
    }
    QList<QString>::iterator itr = f_list.begin();
    for(;itr != f_list.end();++itr)
    {
        QString content = *itr;
        qDebug()<<content<<endl;
        QStringList arr = content.split(',');
        QString fname = arr.at(0);
        QTreeWidgetItem* itemroot = new QTreeWidgetItem(QStringList()<<LOCAL(fname.toStdString().c_str()));
        QVariant var(fname);
        itemroot->setData(0,Qt::UserRole,var);
        ui->file_list->addTopLevelItem(itemroot);
        for(int j = 1;j<arr.count();++j)
        {
            if(h_info.isEmpty() || (h_info.find(arr.at(j)) == h_info.end()))
                return;
            QStringList str = h_info.value(arr.at(j));
            QString file_info = fname+','+arr.at(j);
            QVariant var0(file_info);
            QTreeWidgetItem* children = new QTreeWidgetItem(str);
            children->setData(0,Qt::UserRole,var0);
            itemroot->addChild(children);
        }
    }
    ui->file_list->show();
    */
    QUrl url = Session::Instance()->getURL() + QString("/file/upload/") + roomname_ + ":" + Session::Instance()->getJID();
    ui->file_wid->loadURL(url);
}

void Mucroom::slotcommit()
{
    /*
    if(qp != NULL)
    {
        delete qp;
        qp = NULL;
    }
    qp = new QThreadPush(remote_url,path);
    connect(qp,SIGNAL(finished()),this,SLOT(slotpushfinished()));
    ui->bt_push->setDisabled(true);
    ui->bt_add ->setDisabled(true);
    ui->bt_pull->setDisabled(true);
    //QMessageBox::information(this,LOCAL("提示"),LOCAL("正在提交,请稍后..."),0);
    Sleep(1);
    qp->start();
    */
}

void Mucroom::slotaddfile()
{

    //QMessageBox message(QMessageBox::NoIcon,LOCAL("提示"),LOCAL("要提交所有的更改吗？"),QMessageBox::Yes | QMessageBox::No);
    /*
    if(true)
    {
        QFileDialog* dlg = new QFileDialog(this);
        dlg->setDirectory(QDir(QDir::currentPath() + "/fileshare/"));
        if(dlg->exec() == QDialog::Accepted)
        {
            QString fname = dlg->selectedFiles()[0];
            QStringList dirlist = fname.split('/');
            if(dirlist.count() <= 0)
                return;
            QString name = dirlist.at(dirlist.count() - 1);
            QString destname = Listwindow::Instance()->getcurrentpath() + "/fileshare/" + name;
            if(fname.isEmpty() || destname.isEmpty())
                return;

            bool flag;
            if(fname != destname)
            {
                if(QFile::exists(destname))
                    QFile::remove(destname);
                flag = QFile::copy(fname,destname);
            }

            if(!flag)
            {
                //QMessageBox::information(this,LOCAL("提示"),LOCAL("文件添加失败！"),0);
            }
        }
        else
        {
            //QMessageBox::information(this,LOCAL("警告"),LOCAL("没有选择添加！"),0);
            commit = false;
        }
        //Git_client::getclient()->add(path);
        commitdlg* c = new commitdlg(this);
        c->setmucroom(this);
        c->exec();
        if(commit)
        {
            int i = //Git_client::getclient()->commit(path,commit_msg,commitor,"test@fenh.com");
            if(-1 == i)
            {
                //QMessageBox::information(this,LOCAL("提示"),LOCAL("添加失败"),0);
                commit = false;
                return;
            }
            else
            {
                //QMessageBox::information(this,LOCAL("提示"),LOCAL("添加文件成功"),0);
            }
        }
        else
        {
            QMessageBox::information(this,LOCAL("警告"),LOCAL("取消添加文件！"),0);
        }
        commit = false;
    }
    filepush();
    */
}

void Mucroom::slotpushfinished()
{
    /*
    int i = //Git_client::getclient()->getRet();
    if(i == 5)
        QMessageBox::information(this,LOCAL("提示"),LOCAL("提交成功"),0);
    else
    {
        Loginwindow::getloginInstance()->setfileflag(true);
        QMessageBox::information(this,LOCAL("提示"),LOCAL("提交成功"),0);
    }
    ui->bt_push->setDisabled(false);
    ui->bt_add ->setDisabled(false);
    ui->bt_pull->setDisabled(false);
    //Git_client::getclient()->setRet(0);
    filepush();
    */
}
void Mucroom::slotpull()
{
    /*
    //QMessageBox::information(this,LOCAL("提示"),LOCAL("请稍等..."),0);
    qfd = new QfiledownloadThread(Loginwindow::getloginInstance()->getfileshare(),Listwindow::Instance()->getcurrentpath() + "/fileshare/",2);
    connect(qfd,SIGNAL(finished()),this,SLOT(slotfiledownfinished()));
    qfd->start();
    */
    QUrl url = Session::Instance()->getURL() + "/file/group/" + roomname_;

    ui->file_wid->loadURL(url);
}

void Mucroom::slotfiledownfinished()
{
    /*
    Loginwindow::getloginInstance()->setfileflag(false);
    if(Loginwindow::getloginInstance()->getfileflag())
    {
        QMessageBox::information(this,LOCAL("提示"),LOCAL("网络错误,文件更新失败!"),0);
        ui->bt_pull->setEnabled(true);
        ui->bt_push->setEnabled(true);
        ui->bt_add ->setEnabled(true);
        return;
    }
    else
    {
        filepush();
        QMessageBox::information(this,LOCAL("提示"),LOCAL("更新成功!"),0);
    }
    */
}

void Mucroom::set_path(QString s_path)
{
    strcpy_s(path,s_path.toStdString().c_str());
}

void Mucroom::flushfilelist(int)
{
    QUrl url = Session::Instance()->getURL() + "/file/group/" + roomname_;

    ui->file_wid->loadURL(url);
}

void Mucroom::on_file_list_customContextMenuRequested(const QPoint &pos)
{
    /*
    QTreeWidgetItem* item = ui->file_list->itemAt(pos);
    if(item==NULL)
    {
        return;           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    }
    file_reset = true;
    QMenu* menu = new QMenu(this);
    QAction* act_mutiChat = new QAction(this);
    QAction* act_openfile = new QAction(this);
    QAction* act_opendir  = new QAction(this);
    QVariant var = item->data(0,Qt::UserRole);
    fname_fversion = var.toString();

    bool check = connect(act_mutiChat, SIGNAL(triggered()), this, SLOT(slotQActionfile()));
    Q_ASSERT(check);
    check = connect(act_openfile,SIGNAL(triggered()),this,SLOT(slotQActionopenfile()));
    Q_ASSERT(check);
    check = connect(act_opendir,SIGNAL(triggered()),this,SLOT(slotQActionopendir()));
    act_mutiChat->setText(LOCAL("恢复本文件到此版本"));
    act_openfile->setText(LOCAL("打开此版本文件"));
    act_opendir ->setText(LOCAL("打开文件夹"));
    menu->addAction(act_mutiChat);
    menu->addAction(act_openfile);
    menu->addAction(act_opendir);
    menu->exec(QCursor::pos());
    delete menu;
    delete act_mutiChat;
*/
}

void Mucroom::slotQActionopendir()
{
    QString currentpath = QString("file:///") + Listwindow::Instance()->getcurrentpath() + "/fileshare/";
    bool is_open = QDesktopServices::openUrl(QUrl(currentpath, QUrl::TolerantMode));

    if(!is_open)
    {
        QMessageBox::information(this,LOCAL("提示"),LOCAL("打开文件夹失败！"));
    }
}

void Mucroom::on_version_list_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* item = ui->version_list->itemAt(pos);
    if(item==NULL)
    {
        return;           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    }
    version_reset = true;
    QMenu* menu = new QMenu(this);
    QAction* act_mutiChat = new QAction(this);
    QVariant var = item->data(0,Qt::UserRole);
    ver = var.toString();
    bool check = connect(act_mutiChat, SIGNAL(triggered()), this, SLOT(slotQAction()));
    Q_ASSERT(check);
    act_mutiChat->setText(LOCAL("恢复此版本"));
    menu->addAction(act_mutiChat);
    menu->exec(QCursor::pos());
    delete menu;
    delete act_mutiChat;
}

void Mucroom::slotQAction()
{
    if(version_reset)
    {
        //Git_client::getclient()->reset(path,ver.toStdString().c_str());
        head = ver;
        QMessageBox::information(this,LOCAL("提示"),LOCAL("恢复成功"),0);
    }
    version_reset = false;
}
void Mucroom::slotQActionfile()
{
    if(file_reset)
    {
        QStringList file_info = fname_fversion.split(',');
        if(file_info.count() < 2)
            return;
//        //Git_client::getclient()->file_rollback(path,file_info.at(0).toStdString().c_str(),
//                                               file_info.at(1).toStdString().c_str()
//                                               ,head.toStdString());
        QMessageBox::information(this,LOCAL("提示"),LOCAL("恢复成功"),0);
    }
    file_reset = false;
}

void Mucroom::slotQActionopenfile()
{
    QString name;
    if(file_reset)
    {
        QStringList file_info = fname_fversion.split(',');
        if(file_info.count()==2)
        {
//            //Git_client::getclient()->file_rollback(path,file_info.at(0).toStdString().c_str(),
//                                               file_info.at(1).toStdString().c_str()
//                                               ,head.toStdString());
            name = file_info.at(0);
        }
        else
            name = fname_fversion;
    }
    file_reset = false;

    QString filepath = Listwindow::Instance()->getcurrentpath() + "/fileshare/"+name;
    bool is_open = QDesktopServices::openUrl(QUrl(QString("file:///") + filepath, QUrl::TolerantMode));

    if(!is_open)
    {
        QMessageBox::information(this,LOCAL("提示"),LOCAL("此文件不能被打开,请检查相应的应用程序"));
    }
}
void Mucroom::set_remotepath(QString remotepath)
{
    memset(remote_url,0,256);
    strcpy_s(remote_url,remotepath.toStdString().c_str());
}

void Mucroom::setcommitor(QString msg)
{
    memset(commitor,0,256);
    if(!msg.isEmpty())
        strcpy_s(commitor,msg.toStdString().c_str());
}

void Mucroom::setcommit_msg(QString msg)
{
    memset(commit_msg,0,256);
    if(!msg.isEmpty())
        strcpy_s(commit_msg,msg.toStdString().c_str());
}

void Mucroom::getchats()
{
    chat->clear();
    QString fname = Loginwindow::getloginInstance()->chatpath + roomname_;
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

void Mucroom::openfile(QModelIndex index)
{
    QString name;
    QModelIndex parent = index.parent();
    if(parent.isValid())
    {
        name = parent.data().toString();
    }
    else
        name = index.data().toString();
    QString currentpath = QString("file:///") + Listwindow::Instance()->getcurrentpath() + "/fileshare/" + name;
    bool is_open = QDesktopServices::openUrl(QUrl(currentpath, QUrl::TolerantMode));

    if(!is_open)
    {
        QMessageBox::information(this,LOCAL("提示"),LOCAL("打开文件夹失败！"));
    }
}
