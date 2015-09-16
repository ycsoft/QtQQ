#include "listwindow.h"
#include "ui_listwindow.h"
#include "chatwindow.h"
#include "qfiletrans.h"
#include "loginwindow.h"
#include "searchdlg.h"
#include "findfriend.h"
#include "roomchat.h"
#include "resetnickname.h"
#include "selectmucroom.h"
#include "setdlg.h"
#include "roomchat.h"

#include "passworddlg.h"

#include "maindialog.h"
#include "ui_maindialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QXmppMessage.h>
#include <QXmppLogger.h>
#include <QMenu>
#include <QApplication>
#include <QDesktopWidget>
#include <QXmppUtils.h>
#include <QTextCodec>
#include <Windows.h>
#include <QDir>
#include <QFile>
#include <QXmppElement.h>
#include <QFileDialog>

Listwindow* Listwindow::m_instance=NULL;
QXmppMucManager* Listwindow::mucmanager = NULL;
QXmppCallManager* Listwindow::callmanager = NULL;
Listwindow::Listwindow(QWidget *parent) :
    FramelessWin(parent),
    ui(new Ui::Listwindow)
{
    //ui->setupUi(this);
    SetupUI();
    //
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    //this->setWindowFlags(Qt::WindowSystemMenuHint);//这个是只剩下关闭按钮
   // Qt::WindowFlags flags=Qt::Dialog;
   //     flags |=Qt::WindowMinimizeButtonHint;
     //   setWindowFlags(flags);
    setWindowTitle(selfJID);
    //this->setFixedSize(243,473);
    QPixmap log(":/Icon_logger.png");

    QImage i = log.toImage();
    int x = i.width();
    int y = i.height();
    //ui->LoggerIcon->setFixedSize(x,y);
    QPixmap pixmap(":/Icon_find.png");
    QIcon icon;
    icon.addPixmap(pixmap);
    //ui->FindBtt->setIcon(icon);
    this->setWindowTitle(LOCAL("财政即时聊天"));
    m_instance = this;
    //fr_ =new QTreeView(this);
    //fr_->hide();

    //muc_ = new QTreeView(this);
   // muc_->setFixedSize(241,321);
  // muc_->move(QPoint(0,120));
  //  model = new QStandardItemModel(this->muc_);
    //muc_->hide();

    ui->stackedWidget->setCurrentIndex(0);

    currentpath = QDir::currentPath();
    online = true;
    grouplistfinished = false;
    /*托盘设置*/
    trayMenu_ = creatTray(); //托盘菜单
    trayIcon_ = createSysTray(QString(":Icon_tray.png"),this);
    trayIcon_->setContextMenu(trayMenu_);
    msgState_ = DoubleNewMsg;
   // msgState_list.insert(0, DoubleNewMsg);
   // msgState_list.append(DoubleNewMsg);
    /*在离线托盘图标设置*/
    pixmap_tray_on.load(":/Icon_tray.png");
    QImage image_t = pixmap_tray_on.toImage();
    QRgb col_t;
    int gray_t;
    int width_t = pixmap_tray_on.width();
    int height_t = pixmap_tray_on.height();
    for(int i=0; i< width_t; ++i)
    {
        for(int j = 0; j<height_t;++j)
        {
            col_t = image_t.pixel(i, j);
            gray_t = qGray(col_t);
            image_t.setPixel(i, j, qRgb(gray_t, gray_t, gray_t));
        }
    }
    pixmap_tray_off = pixmap_tray_on.fromImage(image_t);
    icon_tray.addPixmap(pixmap_tray_on);
    setWindowIcon(icon_tray);
    /*在离线好友图标设置*/
    pixmap_on.load(":/Icon_frd");
    QImage image = pixmap_on.toImage();
    QRgb col;
    int gray;
    int width = pixmap_on.width();
    int height = pixmap_on.height();
    for(int i=0; i< width; ++i)
    {
        for(int j = 0; j<height;++j)
        {
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    pixmap_off = pixmap_on.fromImage(image);

    filesend = true;

    /*聊天室管理*/
    mucmanager = new QXmppMucManager();
    Loginwindow::getclient()->addExtension(mucmanager);

    /*语音管理*/
    callmanager = new QXmppCallManager();
    Loginwindow::getclient()->addExtension(callmanager);

    /*接受加入聊天室邀请消息 和 room添加消息
    bool check = connect(mucmanager, SIGNAL(roomAdded(QXmppMucRoom*)), this,
                         SLOT(slotroomAdded(QXmppMucRoom*)));
    Q_ASSERT(check);
    check = connect(mucmanager, SIGNAL(invitationReceived(QString,QString,QString)), this,
                       SLOT(lostacceptMucchat(QString,QString,QString)));
    Q_ASSERT(check);*/

    //查找好友
    //connect(ui->FindBtt, SIGNAL(clicked()), this, SLOT(Search()));
    bool check = connect(&Loginwindow::getclient()->rosterManager(), SIGNAL(rosterReceived()),this,
                         SLOT(slotrosterReceived()));
    Q_ASSERT(check);
    //文件传输
    check= connect(Loginwindow::getclient()->transferManager,SIGNAL(fileReceived(QXmppTransferJob*)),this,SLOT(fileReceived(QXmppTransferJob*)));
    Q_ASSERT(check);
    check = connect(Loginwindow::getclient()->transferManager,SIGNAL(jobFinished(QXmppTransferJob*)),this,SLOT(fileFinished(QXmppTransferJob*)));
    Q_ASSERT(check);
    //p2p聊天
    connect(ui->NameList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleClicked(QModelIndex)));
    check=connect(Loginwindow::getclient(), SIGNAL(messageReceived(const QXmppMessage)), this,
                        SLOT(messageReceived(const QXmppMessage)));

    Q_ASSERT(check);
    connect(Loginwindow::getclient(),SIGNAL(presenceReceived(QXmppPresence)),this,SLOT(handlePrecenseReceive(QXmppPresence)));
    connect(this,SIGNAL(addChatWindows(QString,QString)),this,SLOT(addChatWindow(QString,QString)));
    //会议室单击
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(getMucRoom()));
    //群组按钮单击
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(getRoom()));
    //好友列表单击
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(getFriend()));
    connect(Loginwindow::getclient(),SIGNAL(logMessage(QXmppLogger::MessageType,QString)),this,SLOT(logMessage(QXmppLogger::MessageType,QString)));
    check=connect(this,SIGNAL(handleGroup(QString)),this,SLOT(handleGroupList(QString)));
    Q_ASSERT(check);
    check=connect(this, SIGNAL(handleMucroom(QString)), this, SLOT(handleMucroomList(QString)));
    Q_ASSERT(check);
    connect(this,SIGNAL(addGroupMessage(QString,QString,QString)),this,SLOT(addGroupMessages(QString,QString,QString)));
    check= connect(this,SIGNAL(SigNewMsg()),this,SLOT(slotNewMsg()));
    Q_ASSERT(check);
    connect(this,SIGNAL(SigNewMsgs()),this,SLOT(slotNewMsg()));
    connect(trayIcon_,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayIconActive(QSystemTrayIcon::ActivationReason)));
    check = connect(ui->NameList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotListItemClick(QModelIndex)));
    Q_ASSERT(check);
    connect(this,SIGNAL(addMucroomWindow(QString,QString,QString,QString)),this,SLOT(addMucroomWindows(QString,QString,QString,QString)));
    //connect(Loginwindow::getclient(),SIGNAL(call))
    connect(callmanager, SIGNAL(callReceived(QXmppCall*)), this, SLOT(slotcallrecieved(QXmppCall*)));
    check = connect(Loginwindow::getclient(),SIGNAL(iqReceived(QXmppIq)),this,SLOT(iqReceived(QXmppIq)));
    Q_ASSERT(check);
    connect(this,SIGNAL(groupchanged(QString)),this,SLOT(slotgroupchanged(QString)));
    connect(this,SIGNAL(handleModifypass(QString)),this,SLOT(handleModifypassmsg(QString)));
    //双击组
    connect(ui->fr_,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(handleGroupChat(QModelIndex)));
    connect(Loginwindow::getloginInstance(),SIGNAL(sdownload()),this,SLOT(copychatsfile()));
    connect(this,SIGNAL(roomchatshow(RoomChat*)),this,SLOT(flushfilelist(RoomChat*)));
    connect(Loginwindow::getloginInstance(),SIGNAL(filedownload()),this,SLOT(insertfilelist()));
    connect(this,SIGNAL(recvMsg(QString,QString)),MainDialog::getInstance(),SLOT(recvchat(QString,QString)));
    connect(this,SIGNAL(recvGroup(QString,QString,QString)),MainDialog::getInstance(),SLOT(recvgroup(QString,QString,QString)));

    //ui->session_tabs->addTab(MainDialog::getInstance(),LOCAL("会话"));
    MainDialog::getInstance()->setListWindow(this);
    ui->session_lay->addWidget(MainDialog::getInstance());
    //connect(ui->session_button,SIGNAL(clicked()),this,SLOT(clickSession()));
    //ui->session_button->setVisible(false);

    ui->pushButton->SetButtonText(LOCAL("我的好友"));
    ui->pushButton_2->SetButtonText(LOCAL("我的群组"));
    ui->pushButton_3->SetButtonText(LOCAL("技术支持"));

    resize(350,600);


}
Listwindow::~Listwindow()
{
    delete ui;
}

void Listwindow::SetupUI()
{
    ui->setupUi(this);
}

void Listwindow::slotcallrecieved(QXmppCall *call)
{
    QString jid = call->jid();
    if(winmap_.find(jid) == winmap_.end())
    {
        createchatwindow(jid);
    }
    else if(!winmap_[jid]->getshowd())
    {
        createchatwindow(jid);
    }
    else
        return;

    winmap_.value(jid)->slotcallrecieved(call);
}



void Listwindow::requestMucroomlist()
{
    QString svr = SetDlg::Instance()->getsvr();
    QString body = "<iq id=\"requestMucroomlist\" to=\"conference.";
    body+=svr;
    body+= "\" type=\"get\">";
    body += "<query xmlns=\"http://jabber.org/protocol/disco#items\"/>";
    body += "</iq>";
    Loginwindow::getclient()->sendData(body.toLocal8Bit());
}

void Listwindow::handleMucroomList(QString m)
{
    QDomDocument dom;
    if(!dom.setContent(m))
        return;
    QDomElement root = dom.firstChildElement();
    if(root.isNull())
        return;
    if(root.attribute("id", "0") != "requestMucroomlist")
        return;
    QDomElement query = root.firstChildElement();
    if(query.isNull())
        return;
    QDomElement mucitem = query.firstChildElement();
    if(mucitem.isNull())
        return;
    for(;!mucitem.isNull(); mucitem = mucitem.nextSiblingElement())
    {
        QString muc_jid = mucitem.attribute("jid", "0");
        QString muc_name = mucitem.attribute("name", "0");
        hash_mucnameAndjid.insert(muc_name, muc_jid);

        QString name = Loginwindow::getloginInstance()->chatpath + muc_name;

        QFile fd(name);
        if(fd.exists(name))
        {
            fd.remove();
            fd.close();
        }
    }
}

/**
 * @brief Listwindow::getMucRoom
 * 显示聊天室
 */
void Listwindow::getMucRoom()
{
    //ui->muc_->setFixedSize(241,321);
    //muc_->move(QPoint(0,120));
//    if ( MainDialog::getInstance()->tabwidget->count() > 0)
//        ui->session_button->setVisible(true);
//    else ui->session_button->setVisible(false);

    MainDialog::getInstance()->GetUI()->stack->setVisible(false);
    ui->stackedWidget->setVisible(true);
    ui->stackedWidget->setCurrentIndex(2);
    model = new QStandardItemModel(ui->muc_);

    QHash<QString, QString>::iterator it = hash_mucnameAndjid.begin();
    for(; it != hash_mucnameAndjid.end(); ++it)
    {
        QStandardItem* mucitem = new QStandardItem(it.key());
        model->appendRow(mucitem);
        mucitem->setEditable(false);
    }
    model->setHeaderData(0,Qt::Horizontal,LOCAL("聊天室列表"));
    ui->muc_->setModel(model);
    //ui->NameList->hide();
    //fr_->hide();
    //muc_->show();
    bool check = connect(ui->muc_,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleclickmucRoom(QModelIndex)));
    Q_ASSERT(check);
}

void Listwindow::clickSession()
{
    ui->stackedWidget->setVisible(false);
    ui->session_Widget->setVisible(true);
}

//双击会议室
void Listwindow::doubleclickmucRoom(QModelIndex index)
{
    QString roomname = index.data().toString();
    QString roomid;


    if(hash_mucnameAndjid.find(roomname) != hash_mucnameAndjid.end())
        roomid = hash_mucnameAndjid[roomname];
    else
        return;
    if(hash_mucjidAndmucwin.find(roomid) != hash_mucjidAndmucwin.end())
    {
        MainDialog::getInstance()->addwindow(hash_mucjidAndmucwin[roomid],roomname,0,roomname);
    }
    else
    {
        Mucroom* me = new Mucroom(0);
        me->setparticipantNickname(nickNameSelf);
        me->setroomname(roomname);
        me->joinroom(roomid);
        hash_mucjidAndmucwin.insert(roomid, me);
        connect(this,SIGNAL(recvMucMsg(QString,QString)),me,SLOT(handleMessage(QString,QString)));
        connect(this,SIGNAL(recvMucMsg(QString,QString)),MainDialog::getInstance(),SLOT(recvmuc(QString,QString)));
        MainDialog::getInstance()->addwindow(me,roomname,0,roomname);
    }


    MainDialog::getInstance()->GetUI()->stack->setVisible(false);

    ui->stackedWidget->setVisible(true);
    ui->session_Widget->setVisible(true);
}

/**
 * @brief Listwindow::slotListItemClick
 * @param index  单击
 */
void Listwindow::slotListItemClick(QModelIndex index)
{
    QString objectname = index.data().toString();
    if(hash_nameAndjid.find(objectname) != hash_nameAndjid.end())
    {
        objectJID = hash_nameAndjid[objectname];
    }
}

 // 重载鼠标右键
void Listwindow::contextMenuEvent(QContextMenuEvent *e)
{

    QMenu  *menu = new QMenu(this);
    QAction *act_mutiChat = new QAction(this);
    bool check = connect(act_mutiChat, SIGNAL(triggered()), this, SLOT(slotQAction()));
    Q_ASSERT(check);
    QIcon   icon(":/Icon_add.png");
    act_mutiChat->setIcon(icon);
    act_mutiChat->setText(LOCAL("修改昵称"));
    menu->addAction(act_mutiChat);
    QAction* modify_password = new QAction(this);
    check = connect(modify_password,SIGNAL(triggered()),this,SLOT(slotmodify()));
    Q_ASSERT(check);
    modify_password->setIcon(icon);
    modify_password->setText(LOCAL("修改密码"));
    menu->addAction(modify_password);
    int x= e->x();
    int y =e->y();
    if(x>1 && x<51 && y> 81 && y<115){
    menu->exec(this->cursor().pos());
    }
}


void Listwindow::slotQAction()
{
    //SelectMucroom * selectroom = new SelectMucroom();
  //  selectroom->tranobjectJID(objectJID); //-------->
    //selectroom->tranobjectname(objectname); //----------->
  //  selectroom->show();
    ResetNickname* resetwin = new ResetNickname(this);
    resetwin->show();
}

Listwindow *Listwindow::Instance()
{
    if (m_instance == NULL ){
        m_instance = new Listwindow(0);
    }
    return m_instance;
}

//消息添加到窗口
void Listwindow::addChatWindow(QString jid,QString msg)
{
    //如果没有与某人进行过通信，那么消息会存储在hash_chatmsg中
    if(!hash_chatclicked[jid])
        hash_chatmsg[jid].append(msg);
}

void Listwindow::createchatwindow(QString jid)
{
    wd =NULL;
    QString strjid = Jidtonick(jid.split("/").at(0));
    if ( winmap_.empty()||winmap_.find(jid) == winmap_.end())
    {
        //QHash <QString,Chatwindow*>  winmap_;   //聊天窗口   成员jid+窗口句柄
        chatlist_.append(jid);
        qDebug()<<"gggs"<<chatlist_.size();
        wd = new Chatwindow(0);
        winmap_.insert(jid,wd);
       // QString s = Jidtonick(jid);
        wd->setWindowTitle(jid);
        wd->setChatJid(jid);
        wd->setWinname(strjid);
        wd->chat_initwindow();
        //绑定单人聊天信息槽
       connect(this,SIGNAL(recvMsg(QString,QString)),wd,SLOT(handleMessage(QString,QString)));
        if(!hash_chatmsg[jid].empty() && !hash_chatclicked[jid])
        {
            QStringList list_jid = hash_chatmsg.keys();
            QStringList::iterator r = list_jid.begin();
            for(;r != list_jid.end();++r)
            {
                QString sjid = *r;
                if(sjid == jid)
                {
                    QStringList list_msg = hash_chatmsg.value(jid);
                    //QStringList msglist;
                    QStringList::iterator ls = list_msg.begin();
                    for(;ls != list_msg.end();++ls)
                    {                      
                        QString msgbody = *ls;
                        //msglist.append(msgbody);//将msg倒序
                        emit recvMsg(jid,msgbody);
                    }
/*                    ls = msglist.begin();
                    for(;ls != msglist.end();++ls)
                    {
                        QString msgbody = *ls;
                        emit recvMsg(jid,msgbody);
                    }*/
                    break;
                }
            }
        }
        hash_chatclicked[jid] = true;
    }
    wd = winmap_[jid];
    hash_chattray[jid.split("/").at(0)] = false;
    int a = notifyList.indexOf(jid);
    if(a >= 0)
    {
        notifyList.removeAt(a);
        QIcon ico(":/Icon_tray.png");
        trayIcon_->setIcon(ico);
        if(!notifyList.isEmpty())
        {
            emit SigNewMsg();
            msgState_ = ChatNewMsg;
        }
        else if(!notifyGroupList.isEmpty())
        {
            emit SigNewMsgs();
            msgState_ = GroupNewMsg;
        }
        else
        {
            msgState_ = DoubleNewMsg;
        }
    }
    //wd->show();
    wd->setshowd(true);
    MainDialog::getInstance()->addwindow(wd,strjid,1,jid);
    //MainDialog::getInstance()->addwindow(wd,jid,strjid);
    //MainDialog::getInstance()->show();

}
//搜索用户
void Listwindow::Search()
{
   SearchDlg *sd = new SearchDlg(this);
   sd->show();
}

//  文件接收
void Listwindow::fileReceived(QXmppTransferJob* job)
{
    qDebug()<<"fileReceived";
    filesend = false;
    FileReceiveDlg* fileRcv = new FileReceiveDlg(this);
    QString fn = job->fileName();
    QString from = job->jid();
    from = Listwindow::Instance()->Jidtonick(from.split("/").at(0));
    qint64  size = job->fileSize();
    fileRcv->setWindowTitle(LOCAL("文件接收"));
    connect(job,SIGNAL(progress(qint64,qint64)),fileRcv,SLOT(slotProgress(qint64,qint64)));
    connect(job,SIGNAL(finished()),fileRcv,SLOT(slotfinished()));
    connect(job,SIGNAL(error(QXmppTransferJob::Error)),fileRcv,SLOT(sloterror(QXmppTransferJob::Error)));
    fileRcv->setFileName(fn);
    fileRcv->setSize(size);
    fileRcv->setFrom(from);
    fileRcv->setfilejob(job);
    int res = fileRcv->exec();
    if ( res == 11 )
    {
        job->accept(fn);
        fileRcv->show();
    }
}
void Listwindow::iqReceived(const QXmppIq &iq)
{
    QString xml;
    QXmlStreamWriter *write = new QXmlStreamWriter(&xml);
    iq.toXml(write);
    qDebug()<<xml;
}

// 双击
void Listwindow::doubleClicked(const QModelIndex &index)
{

    QString name= index.data().toString();
    QString jid = Nicktojid(name);
    jid+="/FT";
    createchatwindow(jid);

    MainDialog::getInstance()->GetUI()->stack->setVisible(false);

    ui->stackedWidget->setVisible(true);
    ui->session_Widget->setVisible(true);

}

//接收服务器的消息
void Listwindow::logMessage(QXmppLogger::MessageType type,QString msg)
{
    //msg中可能出现粘包问题,我们需要对msg进行分隔,得到相应的iQ包。
    qDebug()<<"---------------------up-----------------------";
    qDebug()<<msg;
    qDebug()<<"---------------------down---------------------";
    if (msg.isEmpty())
      return;
    if(!msg.contains("<iq"))
        return;
    QStringList msg_list = msg.split("</iq>");
    int i = msg_list.count();
    qDebug()<<i<<endl;

    for(int j = 0;j<i;++j)
    {
        QString splitmsg = msg_list.at(j) + "</iq>";//得到一个尾部是iq的报文
        QStringList msg_list2 = splitmsg.split("<iq");
        QString splitmsg2 = "<iq" + msg_list2.at(msg_list2.count() - 1);
        if (type == QXmppLogger::ReceivedMessage)
        {
            emit handleSearch(splitmsg2);
            emit handleModifypass(splitmsg2);
            emit handleGroup(splitmsg2);
            emit handleMucroom(splitmsg2);
        }
    }
}

//  接受消息
void Listwindow::messageReceived(const QXmppMessage &msg)
{
    //"<message to="baohua@test.xmpp60/FT" type="chat" from="gao@test.xmpp60/FT"><body>nihao</body></message>"
    //"<message type="chat" to="baodong@test.xmpp60" id="后方软件" from="baohua@test.xmpp60/FT"><body>nihao</body></message>"
    //<message id="grouptest1" to="9d4d6204ee943564637f06093236b181@fenh-pc" from="2269f1a61a40d300977536550de4aae4@fenh-pc/FT" type="chat"><body>sssssssssssssssssss</body><x xmlns="jabber:x:delay" stamp="20150116T10:23:25"/></message>
    QString stringxml;
    QXmlStreamWriter xml(&stringxml);
    msg.toXml(&xml);
    QString body = msg.body();
    if (body.isNull())
        return;
    QString type =msg.type();


    if(msg.type() == QXmppMessage::Chat)
    {
       QString fromjid = msg.from();
       QString tojid = msg.to();
       QString id = msg.id();
       qDebug() << body + " " + fromjid + " " + id;
       if((hash_wingroup.find(id) != hash_wingroup.end())&&!(id.isNull()))
       {
//            int a= groupChatlist.size();
 //           int index = groupChatlist.indexOf(id);
            if(hash_grouptray[id])
            {
               //#######################################
               emit SigNewMsgs();
               msgState_= GroupNewMsg;
               notifyGroupList.append(id);
               notifyGroupList = notifyGroupList.toSet().toList();//去重
               emit addGroupMessage(id,fromjid,body);
            }
            QString str = fromjid;
            str += "/FT";
            if(fromjid != str && hash_groupclicked[id])
            {
                emit recvGroup(id,fromjid,body);
            }
       }
       else{
           if(hash_chattray[fromjid.split("/").at(0)])
           {
                emit SigNewMsg();//托盘显示
                msgState_= ChatNewMsg;
                notifyList.append(fromjid);
                notifyList = notifyList.toSet().toList();//去重
                emit addChatWindows(fromjid,body);
           }
           if(hash_chatclicked[fromjid])
           {
               emit recvMsg(fromjid,body);
           }
       }
   }

  if(msg.type()==QXmppMessage::GroupChat){
      QString tojid = msg.to();
      QString str =msg.from();
/*      QDomDocument dom;
      if(!dom.setContent(stringxml))
          return;
      QDomElement root = dom.documentElement();
      if(root.isNull())
          return;*/

      QStringList str1=str.split("/");
      QString roomstr = str1.at(0);
      QString fromjid = str1.at(1);
      //QString ss = selfJID;
     // ss+= "/FT";
      QString ss = Nicktojid(fromjid);
      qDebug()<<ss<<"LLLLLLL";
      qDebug()<<tojid<<body<<fromjid<<roomstr;
      if(nickNameSelf.split("/").at(0) != fromjid){
       emit addMucroomWindow(tojid,fromjid,roomstr,body);
       emit recvMucMsg(fromjid,body);
      }
   }
}

//再接收所有roster消息后,请求获取好友(vcard 信息)的list
void Listwindow::slotrosterReceived()
{
    disconnect(&Loginwindow::getclient()->rosterManager(), SIGNAL(rosterReceived()),this,
                             SLOT(slotrosterReceived()));
    qDebug()<<"Roster Recieved";
     rosterList_ = Loginwindow::getclient()->rosterManager().getRosterBareJids();

    bool check = connect(&(Loginwindow::getclient())->vCardManager(),SIGNAL(vCardReceived(QXmppVCardIq)), this,
                                 SLOT(slotvCardRecieved(QXmppVCardIq)));
    Q_ASSERT(check);

    check = connect(&(Loginwindow::getclient())->vCardManager(),SIGNAL(clientVCardReceived()), this,
                               SLOT(slotclientvCardRecieved()));
    Q_ASSERT(check);

    /*send signal of request of vCard self*/
    Loginwindow::getclient()->vCardManager().requestClientVCard();

    /*send signal of request of vCard others*/
    for(int i = 0; i < rosterList_.size(); ++i)
    {
        Loginwindow::getclient()->vCardManager().requestVCard(rosterList_.at(i));
        hash_chattray.insert(rosterList_.at(i),true);
        hash_chatclicked.insert(rosterList_.at(i),false);
        hash_nameAndjid.insert(rosterList_.at(i), rosterList_.at(i));
        hash_jidAndname.insert(rosterList_.at(i), rosterList_.at(i));
    }
}

/**
 * show friend list
 */

//接受好友的jid，并推送到ListWidget
void Listwindow::slotvCardRecieved(const QXmppVCardIq &vCard)
{

    QString name = vCard.nickName();
    QString jid = vCard.from();

    qDebug()<<"vCard Entry Recieved"<<name<<":"<<jid;
    if(name.isNull()){
        hash_nameAndjid.insert(jid, jid);
        hash_jidAndname.insert(jid, jid);
    }else{
        hash_nameAndjid.insert(name, jid);
        hash_jidAndname.insert(jid, name);
    }
    refreshgrouplist(jid);
    getFriend();
}

//获取自己的jid
void Listwindow::slotclientvCardRecieved()
{
    qDebug()<<"vCard Self Recieved";

   //nickNameSelf = Loginwindow::getclient()->vCardManager().clientVCard().nickName();
    selfJID = Loginwindow::getclient()->vCardManager().clientVCard().to();
    nickNameSelf = Loginwindow::getclient()->vCardManager().clientVCard().nickName();
    if (nickNameSelf.isEmpty() )
        nickNameSelf = selfJID;
    QStringList str1=selfJID.split("/");
     selfJID = str1.at(0);
     QString str = Jidtonick(selfJID);
     if(nickNameSelf.isNull()){
         ui->label_jid->setText(selfJID);
         ui->tip_lb->setText(selfJID);
        setWindowTitle(LOCAL("即时通信----")+selfJID);
     }else
     {
         setWindowTitle(LOCAL("即时通信----")+nickNameSelf);
         ui->label_jid->setText(nickNameSelf);
         ui->tip_lb->setText(nickNameSelf);
     }
   ui->label_jid->setText(nickNameSelf);
   ui->tip_lb->setText(nickNameSelf);
    //qDebug()<<"selfJID"<<selfJID;
}

// 接收Precense
// 先接收所有roster报文,再接受precense报文，最后接收vcard报文
void Listwindow::handlePrecenseReceive(const QXmppPresence &pres)
{
    QString jid = pres.from();
    QString tojid = pres.to();
    QString type =pres.type();
    qDebug()<<"jid"<<jid<<"tojid"<<tojid<<"type"<<type<< "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr";
    //QMessageBox::information(this, "123", selfJID, 0);

   if (jid == tojid) return;
    switch(pres.type()){
        //用户在线
        case  QXmppPresence::Available:{
            QStringList l = jid.split("/");
            QString jid_noFT = l.at(1);
            if(usrst_.find(jid) == usrst_.end()){
                usrst_.insert(jid,true);
            }else{
                usrst_[jid] = true;
            }
            getFriend();
            break;
        }
        case  QXmppPresence::Unavailable:{
            if(usrst_.find(jid) == usrst_.end()){
                usrst_.insert(jid,false);
            }else{
                usrst_[jid] = false;
            }
            getFriend();
            break;
        }
        //添加好友请求
        case  QXmppPresence::Subscribe:{
        qDebug()<<"Subscribe";
        str_addFriend = jid;
        str_addFriend+="add you";

      //  if (QMessageBox::Yes ==  QMessageBox::information(this,"box",str1,QMessageBox::Yes | QMessageBox::No))
        //{
            QString str = "<presence from=\"";
               // str +=  pres.to() ;
                str +=  "\" to=\"";
                str += jid;
                str += "\" type=\"";
                str += "subscribed";
                str += "\"/>";
                qDebug()<<str;
          Loginwindow::getclient()->sendData(str.toLocal8Bit());
            /* }
            else{ QString str3 = "<presence from=\"";
            str3 +=  "\" to=\"";
            str3 += jid;
            str3 += "\" type=\"";
            str3 += "unsubscribed";
            str3 += "\"/>";
            qDebug()<<str3;
            Loginwindow::getclient()->sendData(str3.toLocal8Bit());
            }*/
         break;
    }
        case  QXmppPresence::Unsubscribed:{
            //拒绝添加好友删除好友
            int index = rosterList_.indexOf(jid);
            rosterList_.removeAt(index);
            getFriend();
            break;
        }
            case  QXmppPresence::Subscribed:{
            //成功添加好友
            QString str = "<presence from=\"\" to=\"";
            str +=jid;
            str += "\" type=\"subscribed\"> </presence>";
            Loginwindow::getclient()->sendData(str.toLocal8Bit());
            usrst_.insert(pres.from(),true);
            rosterList_.append(jid);
            hash_chattray.insert(jid,true);
            Loginwindow::getclient()->vCardManager().requestVCard(jid);
            getFriend();
            break;
        }
    default:
        break;
    }
 }

/*void FreindListWidget::closeEvent(QCloseEvent *e)
{
    hide();
    e->ignore();
}
*/

//显示好友列表
void Listwindow::getFriend()
{
//    if ( MainDialog::getInstance()->tabwidget->count() > 0)
//        ui->session_button->setVisible(true);
//    else ui->session_button->setVisible(false);
    ui->stackedWidget->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
    MainDialog::getInstance()->GetUI()->stack->setVisible(false);

    //ui->session_Widget->setMaximumHeight(50);
    //ui->session_Widget->setVisible(false);

    ui->NameList->clear();
    rosterList_.removeDuplicates();
    int row = ui->NameList->count();
    QStringList::Iterator it = rosterList_.begin();
      for (;it != rosterList_.end(); it++){
          if(*it != selfJID){
            QString str= Jidtonick(*it);
            //ui->NameList->item(row)->setIcon(QIcon(":/Icon_frd"));
            QString j = *it + "/FT";
            QIcon icon;
            if(usrst_[j])
            {
                icon.addPixmap(pixmap_on);
                ui->NameList->insertItem(0,str);
                ui->NameList->item(0)->setIcon(icon);
            }
            else
            {
                icon.addPixmap(pixmap_off);
                ui->NameList->addItem(str);
                ui->NameList->item(row)->setIcon(icon);
            }
            ++row;
            QDir* dir = new QDir;
            if(!dir->exists(Loginwindow::getloginInstance()->chatpath))
            {
                dir->mkdir(Loginwindow::getloginInstance()->chatpath);
            }
            //dir->setCurrent(Loginwindow::getloginInstance()->chatpath);
            QString str_md5 = hash_nameAndjid.value(str);
            QString fname = Loginwindow::getloginInstance()->chatpath + str_md5.split('@').at(0);
            QFile fd(fname);
            fd.open(QFile::Append);
            fd.close();
            delete dir;
          }
     }
      //fr_->hide();
      //muc_->hide();
      ui->NameList->show();
}

//       群聊天列表
void Listwindow::getRoom()
{

//    if ( MainDialog::getInstance()->tabwidget->count() > 0)
//        ui->session_button->setVisible(true);
//    else ui->session_button->setVisible(false);

    MainDialog::getInstance()->GetUI()->stack->setVisible(false);
    ui->stackedWidget->setVisible(true);
    ui->stackedWidget->setCurrentIndex(1);
    //ui->session_Widget->setVisible(false);
    model = new QStandardItemModel(ui->fr_);
    QHash<QString, QStringList>::iterator i = hash_wingroup.begin();
       for(;i != hash_wingroup.end();i++)
       {
           QString key = i.key();
           QStandardItem* group_number = new QStandardItem(key);
           model->appendRow(group_number);
           model->setHeaderData(0,Qt::Horizontal,LOCAL("群列表"));
           group_number->setEditable(false);

           /**
             *遍历每个组下面的成员*/
           QStringList list = i.value();
           QStringList::iterator it = list.begin();

           for(; it != list.end(); ++it)
           {
               if(*it != selfJID)
               {
               QString name = Jidtonick(*it);
               if(name.isEmpty())
                   name = *it;
               QStandardItem* name_number = new QStandardItem(name);
               group_number->appendRow(name_number);
               name_number->setEditable(false);
               }
           }
       }
    //ui->NameList->hide();
    //muc_->hide();
    ui->fr_->setModel(model);
    //fr_->show();
}

//显示窗口位置
void Listwindow::moveToRightTop()
{
    int wid = QApplication::desktop()->width();
    int hei = QApplication::desktop()->height();
    int cw = this->width();
    int ch = this->height();
    this->move(wid-cw-100,40);
}

     //处理组报文
 void  Listwindow::handleGroupList(QString m)
{
     //"group prensece:++++++
     //<iq type="result" id="qxmpp7" to="baohua@test.xmpp60/FT">
     //<query xmlns="jabber:iq:roster">
     //<item jid="kongliang@test.xmpp60" name="kongliang" subscription="both"><group>后方软件</group></item>
     //<item jid="baodong@test.xmpp60" name="baodong" subscription="both"><group>后方软件</group></item>
     //<item jid="chu@test.xmpp60" name="chu" subscription="both"><group>后方软件</group></item>
     //<item jid="yinhao@test.xmpp60" name="yinhao" subscription="both"><group>后方软件</group></item>
     //<item jid="gao@test.xmpp60" name="gao" subscription="both"><group>后方软件</group></item>
     //<item jid="yang@test.xmpp60" name="yang" subscription="both"><group>后方软件</group></item>
     //<iq type="set" id="975-4165" to="ad1164be328f3ec9e5b3b41b96499594@test.xmpp60/FT">
     //<query xmlns="jabber:iq:roster">
     //<item jid="e8a3d5f4ee98f8817215bb169b6fce08@test.xmpp60" ask="subscribe" subscription="none"/></query></iq>
     //</query></iq>"
        QDomDocument dom;
        qDebug()<<m<<endl;
        QString err;
        int row,col;
        if(!dom.setContent(m,&err,&row,&col))
        {
            //char buff[128];
            //sprintf(buff,"row:%d,col:%d",row,col);
            //QMessageBox::information(this,"info",err + buff,0);
            return;
        }
        bool bclear = true;
        QDomElement iq = dom.firstChildElement("iq");
        if(iq.isNull())
            return;
        if(iq.attribute("type","0") == "result")
            bclear = true;
        if(iq.attribute("type","0") == "set")
            bclear = false;

        QDomElement root = dom.documentElement();
        if(root.isNull())
            return;
        QDomElement query = root.firstChildElement("query");
        if(query.isNull())
            return;
        if(query.attribute("xmlns", "0") == "jabber:iq:roster")
        {
            if(bclear)
                hash_wingroup.clear();
            QDomElement item = query.firstChildElement("item");
            for(; !item.isNull(); item = item.nextSiblingElement("item"))
            {
                QString jid = item.attribute("jid", "0");
                QDomElement group = item.firstChildElement("group");
                //if(group.isNull())
                   // return;
                QString subscription = item.attribute("subscription","0");
                if((!subscription.isNull()) && (!bclear))
                {
                    if("remove" == subscription)
                    {
                        return;
                    }
                    if("both" == subscription)
                    {
                        QStringList grouplist = m.split("</group>");
                        //当只是单纯的添加好友，也会收到这样的iq报文,但是没有group项，在这里进行排除
                        if(m == grouplist.at(0))
                            return;
                        int numgroup = grouplist.count() - 1;
                        QStringList strgroup;
                        for(int j = 0;j < numgroup ;++j)
                        {
                            strgroup.append(grouplist.at(j).split("<group>").at(1));
                        }
                        //如果这个jid没有在jidAndgroup中，那么他是刚添加进来的，只会有一个组,可以直接添加.
                        if(hash_jidAndgroup.value(jid).isEmpty())
                        {
                            QSet<QString> groupset;
                            groupset.insert(strgroup.at(0));
                            QStringList jid_list;
                            jid_list.append(jid);
                            //
                            if(hash_wingroup.find(strgroup.at(0)) == hash_wingroup.end())
                            {
                                hash_wingroup.insert(strgroup.at(0),jid_list);
                                hash_groupclicked.insert(strgroup.at(0),false);
                                hash_grouptray.insert(strgroup.at(0),true);
                            }
                            else
                            {
                                QStringList jidlist = hash_wingroup.value(strgroup.at(0));
                                jidlist.append(jid);
                                hash_wingroup.insert(strgroup.at(0),jidlist);
                            }

                            hash_jidAndgroup.insert(jid,groupset);
                            groupadd = true;

                            QString path = currentpath + "/chat/";

                             QDir* dir = new QDir;
                             if(!dir->exists(path))
                                 dir->mkdir(path);
                             QString chatpath = Loginwindow::getloginInstance()->chatpath;
                             if(!dir->exists(chatpath))
                                 dir->mkdir(chatpath);

                             QString fserver = SetDlg::Instance()->getfserver();
                             QString fpath = currentpath+ "/chat/" + "group/";
                             if(!dir->exists(fpath + ".git/"))
                             {
                                 dir->mkdir(fpath);
                                 //if(!Loginwindow::getloginInstance()->getchatsflag())
                                    //Git_client::getclient()->clone(fserver.toStdString().c_str(),fpath.toStdString().c_str());
                             }
                             else
                             {
                                 //if(!Loginwindow::getloginInstance()->getchatsflag())
                                    ////Git_client::getclient()->pull(fpath.toStdString().c_str(),fserver.toStdString().c_str());
                             }

                             QString fname = chatpath + strgroup.at(0);
                             QFile fd(fname);
                             fd.open(QFile::Append);
                             fd.close();
                             delete dir;
                        }
                        else
                        {
                            int oldcount = hash_jidAndgroup.value(jid).count();
                            int newcount = strgroup.count();
                            if(oldcount > newcount)//可能删除了组员或者自己，异组共同好友。
                            {
                                return;//这里不能响应删除同组好友，不做处理
                            }
                            else
                            {
                                groupadd = true;//这样才是添加
                                int groupcount = strgroup.count();
                                QSet<QString> groupset;
                                while(groupcount--)
                                {
                                    groupset.insert(strgroup[groupcount]);
                                    QStringList jid_list;
                                    if(hash_wingroup.find(strgroup[groupcount]) == hash_wingroup.end())
                                    {
                                        jid_list.append(jid);
                                        hash_wingroup.insert(strgroup[groupcount],jid_list);
                                        hash_groupclicked.insert(strgroup[groupcount],false);
                                        hash_grouptray.insert(strgroup[groupcount],true);
                                        //添加聊天记录
                                        QString path = currentpath + "/chat/";

                                         QDir* dir = new QDir;
                                         if(!dir->exists(path))
                                             dir->mkdir(path);
                                         QString chatpath = Loginwindow::getloginInstance()->chatpath;
                                         if(!dir->exists(chatpath))
                                             dir->mkdir(chatpath);

                                         QString fserver = SetDlg::Instance()->getfserver();
                                         QString fpath = currentpath + "/chat/" + "group/";
                                         if(!dir->exists(fpath + ".git/"))
                                         {
                                             dir->mkdir(fpath);
                                             //if(!Loginwindow::getloginInstance()->getchatsflag())
                                                ////Git_client::getclient()->clone(fserver.toStdString().c_str(),fpath.toStdString().c_str());
                                         }
                                         else
                                         {
                                            // if(!Loginwindow::getloginInstance()->getchatsflag())
                                                ////Git_client::getclient()->pull(fpath.toStdString().c_str(),fserver.toStdString().c_str());
                                         }

                                         QString fname = chatpath + strgroup.at(0);
                                         QFile fd(fname);
                                         fd.open(QFile::Append);
                                         fd.close();
                                         delete dir;
                                    }
                                }
                                hash_jidAndgroup.insert(jid,groupset);
                            }
                        }
                        emit groupchanged(jid);
                        return;
                    }
                }
                for(;!group.isNull(); group = group.nextSiblingElement("group"))
                {
                    QString group_string = group.text();
                    qDebug() << "+++++++++++++" << group_string;
                    if(hash_wingroup.find(group_string) == hash_wingroup.end())
                    {
                        QStringList group_list;
                        group_list.append(jid);
                        QSet<QString> groupset;
                        if(hash_jidAndgroup.find(jid) == hash_jidAndgroup.end())
                            groupset.insert(group_string);
                        else
                        {
                            groupset = hash_jidAndgroup.value(jid);
                            groupset.insert(group_string);
                        }
                        hash_jidAndgroup.insert(jid,groupset);
                        hash_wingroup.insert(group_string, group_list);
                        hash_groupclicked.insert(group_string,false);//添加群组,并且设置其点击为false
                        QDir* dir = new QDir;
                        if(!dir->exists(Loginwindow::getloginInstance()->chatpath))
                        {
                            dir->mkdir(Loginwindow::getloginInstance()->chatpath);
                        }
                        QString fname = Loginwindow::getloginInstance()->chatpath + group_string;
                        QFile fd(fname);
                        hash_grouptray.insert(group_string,true);
                        fd.open(QFile::Append);
                        fd.close();
                        delete dir;
                    }
                    else
                    {
                        hash_wingroup[group_string].append(jid);
                        QSet<QString> groupset;
                        groupset = hash_jidAndgroup[jid];
                        groupset.insert(group_string);
                        hash_jidAndgroup.insert(jid,groupset);
                    }
                }
            }
            requestMucroomlist();
        }
        grouplistfinished = true;
        copychatsfile();
        //更新群聊天纪录
}

 //双击组
void Listwindow::handleGroupChat(QModelIndex inx)
{
    QString str = inx.data().toString();
    if(hash_wingroup.find(str)!=hash_wingroup.end())
    {
        creategroupwindow(str);
    }
    else{
        doubleClicked(inx);
    }

    MainDialog::getInstance()->GetUI()->stack->setVisible(false);

    ui->stackedWidget->setVisible(true);
    ui->session_Widget->setVisible(true);
}

void Listwindow::creategroupwindow(QString str)
{
    bool filedownloadflag;
    if(hash_wingroup.find(str)!=hash_wingroup.end())
    {
        RoomChat *rcs =NULL;
        if ( roommap_.empty() || roommap_.find(str) == roommap_.end())
        {
            rcs = new RoomChat(0);
            /*
            groupChatlist.append(str);
            QStringList ls;
            ls.clear();
            ls= hash_wingroup[str];
            rcs->setSelfJid(selfJID);
            rcs->setGrouplist(ls);
            rcs->pushFriend(ls);

            roommap_.insert(str,rcs);
            rcs->setWindowTitle(str);
            //绑定接受组信息槽
            connect(this,SIGNAL(recvGroup(QString,QString,QString)),rcs,SLOT(handleMessage(QString,QString,QString)));
            rcs->chat_initwindow(str);
            filedownloadflag = true;
            */
            rcs->setKey(str);
            roommap_.insert(str,rcs);

      }
      rcs = roommap_[str];
      if(!hash_groupmsg[str].isEmpty())
      {
          QList<QString> list_id = hash_groupmsg.keys();
          QList<QString>::iterator r = list_id.begin();

          for(;r != list_id.end();++r)
          {
              if((*r == str) && (!hash_groupclicked[*r]))
              {
                  QStringList list_msginfo = hash_groupmsg.value(str);
                  QStringList::iterator lr = list_msginfo.begin();
                  for(;lr != list_msginfo.end();++lr)
                  {
                      QString msgfrom = lr->split("<group>").at(0);
                      QString msgbody = lr->split("<group>").at(1);
                      emit recvGroup(str,msgfrom,msgbody);
                  }
                  break;
              }
          }
      }
      hash_groupclicked[str] = true;
      hash_grouptray[str] = false;
      int a = notifyGroupList.indexOf(str);
      if(a >= 0)
      {
          notifyGroupList.removeAt(a);
          QIcon ico(":/Icon_tray.png");
          trayIcon_->setIcon(ico);
          if(!notifyList.isEmpty())
          {
              emit SigNewMsg();
              msgState_ = ChatNewMsg;
          }
          else if(!notifyGroupList.isEmpty())
          {
              emit SigNewMsgs();
              msgState_ = GroupNewMsg;
          }
          else
          {
              msgState_ = DoubleNewMsg;
          }
      }
      MainDialog::getInstance()->addwindow(rcs,str,2,str);
      }
    ui->stackedWidget->setVisible(true);
}
void Listwindow::addGroupMessages(QString id,QString from,QString body)
{
    if (roommap_.empty() || roommap_.find(id) == roommap_.end())
    {
        QString msgid = id;
        QString msginfo = from + "<group>" + body;
        hash_groupmsg[msgid].append(msginfo);
    }
}
void Listwindow::changenick(QString new_nick)
{
    QString old_nick = nickNameSelf;
    QString data_jid = selfJID;
    vCardself.setNickName(new_nick);
    Loginwindow::getclient()->vCardManager().setClientVCard(vCardself);
    nickNameSelf = new_nick;
    hash_nameAndjid.remove(old_nick);
    hash_jidAndname.remove(data_jid);
    hash_nameAndjid.insert(new_nick,data_jid);
    hash_jidAndname.insert(data_jid,new_nick);
    //ui->label_jid->setText(new_nick);

}

/*void Listwindow::slotchangenick()
{
    QString data_name = nickNameSelf;
    QString old_name = data_name;
    QString data_jid = selfJID;

        if (data_name == nickNameSelf)
        {
           // QMessageBox::information(this,"ChangeNickname", "Confirm");
            ResetNickname* it = new ResetNickname(0);
           it->exec();
            QString newNickname = it->getNickname();
            vCardMyself.setNickName(newNickname);
            nickNameSelf = newNickname;
            hash_nameAndjid.remove(old_name);
            hash_jidAndname.remove(data_jid);
            hash_nameAndjid.insert(newNickname,data_jid);
            hash_jidAndname.insert(data_jid,newNickname);

            ui->label_jid->setText(newNickname);
            it->close();
        }
}*/
//nick  转jid
QString Listwindow::Nicktojid(QString nick)
{
    return hash_nameAndjid[nick];
}
//jid 转nick
QString Listwindow::Jidtonick(QString jid)
{
    return hash_jidAndname[jid];
}
QSystemTrayIcon *Listwindow::createSysTray(QString fname,QObject *parent)
{
    QSystemTrayIcon *tray = new QSystemTrayIcon( parent );
    QIcon   ico(fname);
    QString  titlec = LOCAL("财政即时通讯");
    QString  text = LOCAL("已登陆！");
    tray->setIcon(ico);
    tray->setToolTip(titlec);
    tray->show();
    tray->showMessage(titlec,text,QSystemTrayIcon::Information,5000);
    return tray;
}
void Listwindow::slotNewMsg()
{
    QString  titlec =LOCAL("财政即时通讯");
    QString  text = LOCAL("你有新的消息！");
    QIcon   ico(":/Icon_tray_msg.png");
    trayIcon_->setIcon(ico);
    trayIcon_->showMessage(titlec,text,QSystemTrayIcon::Information,5000);
}

//双击托盘信息
void Listwindow::trayIconActive(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
      case QSystemTrayIcon::Trigger:
            break;

      case QSystemTrayIcon::DoubleClick:
            if(msgState_== ChatNewMsg)
            {

                QString from = notifyList[0];
                notifyList.removeAt(0);
                //msgState_list.removeAt(0);
                createchatwindow(from);

                MainDialog::getInstance()->GetUI()->stack->setVisible(true);
                ui->stackedWidget->setVisible(false);
                ui->session_Widget->setVisible(true);

                MainDialog::getInstance()->ClickTabButton(from);
                m_instance->show();
                QIcon ico(":/Icon_tray.png");
                trayIcon_->setIcon(ico);
                if(!notifyList.isEmpty())
                {
                    emit SigNewMsg();
                    msgState_ = ChatNewMsg;
                }
                else if(!notifyGroupList.isEmpty())
                {
                    emit SigNewMsgs();
                    msgState_ = GroupNewMsg;
                }
                else
                {
                    msgState_ = DoubleNewMsg;
                }
                return;
            }
            if(msgState_ == GroupNewMsg)
            {
                QString from = notifyGroupList[0];
                notifyGroupList.removeAt(0);
                //msgState_list.removeAt(0);
                //##########################
                creategroupwindow(from);
                MainDialog::getInstance()->GetUI()->stack->setVisible(true);
                ui->stackedWidget->setVisible(false);
                ui->session_Widget->setVisible(true);

                MainDialog::getInstance()->ClickTabButton(from);

                QIcon ico(":/Icon_tray.png");
                trayIcon_->setIcon(ico);
                //msgState_ = DoubleNewMsg;
                if(!notifyList.isEmpty())
                {
                    emit SigNewMsg();
                    msgState_ = ChatNewMsg;
                }
                else if(!notifyGroupList.isEmpty())
                {
                    emit SigNewMsgs();
                    msgState_ = GroupNewMsg;
                }
                else
                {
                    msgState_ = DoubleNewMsg;
                }
                return;
            }
            if(msgState_ == DoubleNewMsg)
            {
                m_instance->show();
                msgState_ = DoubleNewMsg;
                return;
            }
            break;
        default:
            break;
    }
}

QString Listwindow::getselfJID()
{
    return selfJID;
}
void Listwindow::addMucroomWindows(QString tojid,QString fromjid,QString roomname,QString msg)
{
    //qDebug()<<tojid<<fromjid<<roomname<<msg<<"AAAAAAAAAAAAAAAA";
    if(hash_mucjidAndmucwin.find(roomname) != hash_mucjidAndmucwin.end())
    {
        hash_mucjidAndmucwin[roomname]->show();
    }
    else
    {
        Mucroom* me = new Mucroom(0);
        me->setparticipantNickname(selfJID);
        me->joinroom(roomname);
        hash_mucjidAndmucwin.insert(roomname, me);
        connect(this,SIGNAL(recvMucMsg(QString,QString)),me,SLOT(handleMessage(QString,QString)));
        me->show();
    }
}
 void Listwindow::closeEvent(QCloseEvent *e)
  {
         if(trayIcon_->isVisible())
         {
             this->hide();
             e->ignore();
         }
  }
QMenu* Listwindow::creatTray()
{
    QMenu  *menu = new QMenu(this);
    QIcon   icon(":/exit.png");
    QAction *act_online = new QAction(this);
    act_online->setIcon(icon);
    act_online->setText(LOCAL("上线"));
    menu->addAction(act_online);
    QAction *act_disabled = new QAction(this);
    act_disabled->setIcon(icon);
    act_disabled->setText(LOCAL("离线"));
    menu->addAction(act_disabled);
    QAction *act_mutiChat = new QAction(this);
    act_mutiChat->setIcon(icon);
    act_mutiChat->setText(LOCAL("安全退出"));
    menu->addAction(act_mutiChat);
    connect(act_mutiChat, SIGNAL(triggered()), this, SLOT(Exet()));
    connect(act_disabled, SIGNAL(triggered()), this, SLOT(Disable()));
    connect(act_online, SIGNAL(triggered()), this, SLOT(Online()));
    return menu;
}
void Listwindow::Exet()
{
    QApplication::exit(0);
    //qApp->quit();
}
void Listwindow::Disable()
{
    online = false;
    Loginwindow::getclient()->disconnectFromServer();
    icon_tray.addPixmap(pixmap_tray_off);
    setWindowIcon(icon_tray);
    trayIcon_->setIcon(icon_tray);
}
void Listwindow::Online()
{
    online = true;
    Loginwindow::getclient()->login(Loginwindow::getloginInstance()->getjid_md5(),
                                    Loginwindow::getloginInstance()->getpwd(),
                                    Loginwindow::getloginInstance()->getsvr(),
                                    Loginwindow::getloginInstance()->getip());
    icon_tray.addPixmap(pixmap_tray_on);
    setWindowIcon(icon_tray);
    trayIcon_->setIcon(icon_tray);
}
//添加新好友
void Listwindow::slotaddnew(QString newfriend)
{
    ui->NameList->addItem(newfriend);
    rosterList_.append(newfriend);
    hash_chattray.insert(newfriend,true);

    QString remind = LOCAL("成功添加");
    remind += newfriend;
    remind += LOCAL("为好友");
    QMessageBox::information(this, LOCAL("提示"), remind);
    Loginwindow::getclient()->vCardManager().requestVCard(newfriend);
    getFriend();
}
//鼠标右键处理好友
void Listwindow::on_NameList_customContextMenuRequested(const QPoint &pos)
{
    item = ui->NameList->itemAt(pos);
    if(item == NULL)
    {
        return;
    }

    QString name = item->text();
    str_removeFriend = hash_nameAndjid.value(name);

    QMenu* menu = new QMenu(this);
    QAction* act_mutiChat = new QAction(this);
    act_mutiChat->setText(LOCAL("删除好友"));
    connect(act_mutiChat,SIGNAL(triggered()),this,SLOT(slotremovefriend()));
    menu->addAction(act_mutiChat);
    menu->exec(QCursor::pos());
}
//处理删除好友
void Listwindow::slotremovefriend()
{
    QMessageBox message(QMessageBox::NoIcon,LOCAL("提示"),LOCAL("确定要删除此好友"),
                        QMessageBox::Yes | QMessageBox::No);
    if(message.exec() == QMessageBox::Yes)
    {
        QHash<QString, QStringList>::iterator i = hash_wingroup.begin();
        for(;i != hash_wingroup.end();i++)
        {
            QStringList namelist = i.value();
            if(namelist.contains(str_removeFriend))
            {
                QMessageBox::information(this,LOCAL("警告"),LOCAL("这个好友是组成员,不能删除！"),0);
                return;
            }
        }
        Loginwindow::getclient()->rosterManager().removeItem(str_removeFriend);
        rosterList_.removeOne(str_removeFriend);
        getFriend();
    }
}
//处理组信息变更
void Listwindow::slotgroupchanged(QString jid)
{
    Loginwindow::getclient()->vCardManager().requestVCard(jid);
    QSet<QString> groupset = hash_jidAndgroup.value(jid);
    QStringList groupname = groupset.toList();
    if(groupadd)
    {
        rosterList_.append(jid);
        hash_chattray.insert(jid,true);
        rosterList_ = rosterList_.toSet().toList();
    }
    else
    {
        return;//暂时不做处理
//        int index = rosterList_.indexOf(jid);
//        rosterList_.removeAt(index);
//        hash_jidAndgroup.remove(jid);
    }
    int namecount = groupname.count();
    for(int i = 0;i<namecount;++i)
    {
        hash_wingroup[groupname[i]].append(jid);
        //将jid加入到hash_wingroup中，并且去除重复值
        hash_wingroup[groupname[i]] = hash_wingroup[groupname[i]].toSet().toList();
        QStringList ls = hash_wingroup[groupname[i]];
        RoomChat* rc = NULL;
        if(roommap_.isEmpty())//如果当前没有创建群窗口
        {
            break;
        }
        rc = roommap_[groupname[i]];
        if(!rc)//如果当前rc群窗口没有创建
        {
            continue;
        }
        else
        {
            rc->pushFriend(ls);
            rc->setGrouplist(ls);
        }
    }
    getFriend();//更新好友列表
    getRoom();//更新组列表
}

//在接收到vCard信息之后,更新组成员列表,组窗口内的成员列表
void Listwindow::refreshgrouplist(QString jid)
{
    QStringList grouplist = hash_jidAndgroup.value(jid).toList();
    if(grouplist.isEmpty())//这个用户没有在任何组中。
    {
        return;
    }
    int groupcount = grouplist.count();
    while(groupcount--)
    {
        if(roommap_.find(grouplist.at(groupcount)) == roommap_.end() || roommap_.isEmpty())
            break;

        rc = roommap_[grouplist.at(groupcount)];
        QStringList jidlist = hash_wingroup[grouplist.at(groupcount)];
        rc->pushFriend(jidlist);
        rc->setGrouplist(jidlist);
    }
    getRoom();
}
void Listwindow::uploadchats()
{
    QString chatspath = Loginwindow::getloginInstance()->chatpath;
    QStringList chatlist = hash_wingroup.keys();
    QStringList::iterator it = chatlist.begin();
    while(it != chatlist.end())
    {
        QString filename = *it;
        QString srcpath = chatspath + filename;
        QString destpath = RoomChat::GetInstance()->getpath();
        QFile fds(srcpath);

        if(srcpath == destpath)
            return;
        fds.copy(destpath);
        fds.close();
    }
}
QString Listwindow::getself()
{
    return ui->label_jid->text();
}
void Listwindow::setchattray(QString id, bool flag)
{
    if(hash_chattray.contains(id))
        hash_chattray[id] = flag;
}
void Listwindow::setgrouptray(QString id, bool flag)
{
    if(hash_grouptray.contains(id))
        hash_grouptray[id] = flag;
}

void Listwindow::fileFinished(QXmppTransferJob *job)
{
    QDir* dir = new QDir;
    dir->setCurrent(currentpath);
    delete dir;
}

void Listwindow::setwindowsendflag(QString jid, bool flag)
{
    if(jid.isEmpty() || winmap_.find(jid) == winmap_.end())
        return;

    Chatwindow* cwd = winmap_.value(jid);
    cwd->setsendflag(flag);
}

void Listwindow::slotmodify()
{
    if(!online)
    {
        QMessageBox::information(this,LOCAL("提示"),LOCAL("请确保您在上线状态!"),0);
        return;
    }
    passworddlg* plg = new passworddlg(this);
    plg->exec();

    if(password.isEmpty())
        return;

    QString msg = "<iq type='set' to=";
    msg += "'";
    msg += SetDlg::Instance()->getsvr();
    msg += "'";
    msg += " id='change1'><query xmlns='jabber:iq:register'><username>";
    msg += selfJID.split("@").at(0);
    msg += "</username><password>";
    msg += password;
    msg += "</password></query></iq>";

/*  QString msg = "<iq type='set' to='test.xmpp60' id='change1'>";
    msg+= "<query xmlns='jabber:iq:register'>";
    msg+= "<username>b04083e53e242626595e2b8ea327e525</username>";
    msg+= "<password>1</password>";
    msg+= "</query></iq>";*/

    qDebug()<<msg;
    Loginwindow::getclient()->sendData(msg.toLocal8Bit());

    password = "";
}

void Listwindow::setpassword(QString pass)
{
    password = pass;
}

void Listwindow::handleModifypassmsg(QString msg)
{
    QDomDocument dom;
    msg = msg.split("</iq>").at(0);
    QString err;
    int row,col;
    if(!dom.setContent(msg,&err,&row,&col))
    {
        return;
    }

    QDomElement iq = dom.firstChildElement("iq");
    if(iq.isNull())
        return;
    if(iq.attribute("type","0") == "result" && iq.attribute("id","0") == "change1")
        QMessageBox::information(this,LOCAL("提示"),LOCAL("密码修改成功!"),0);
}

void Listwindow::copychatsfile()
{
    if(Loginwindow::getloginInstance()->getdownloadflag() && grouplistfinished)
    {
        if(Loginwindow::getloginInstance()->getchatsflag())
            return;
        QStringList groupname = hash_wingroup.keys();
        int size = groupname.count();
        while(size--)
        {
            QString fname = Loginwindow::getloginInstance()->chatpath + hash_wingroup.keys()[size];
            QString srcfile = currentpath + "/chat/group/" + hash_wingroup.keys()[size];
            if(!QFile::exists(srcfile))
                return;
            else
                QFile::remove(fname);
            QFile::copy(srcfile,fname);
        }
    }
}

void Listwindow::flushfilelist(RoomChat *rcs)
{
    rcs->filepush();
}
void Listwindow::insertfilelist()
{
    if(Loginwindow::getloginInstance()->getfileflag())
        return;
    QHash<QString,RoomChat*>::iterator it = roommap_.begin();
    for(;it != roommap_.end();++it)
    {
        it.value()->filepush();
        it.value()->releasebutton();
    }
    QHash<QString,Mucroom*>::iterator mit = hash_mucjidAndmucwin.begin();
    for(;mit != hash_mucjidAndmucwin.end();++mit)
    {
        mit.value()->filepush();
        //mit.value()->releasebutton();
    }
}

QString Listwindow::getcurrentpath()
{
    return currentpath;
}

void Listwindow::resizeEvent(QResizeEvent *evt)
{
    int indent = 2;
    int wid = rect().width();
    //ui->pushButton->setMinimumWidth(wid/3-indent);
    ui->pushButton->setMaximumWidth(wid/3-indent);

    //ui->pushButton_2->setMinimumWidth(wid/3-indent);
    ui->pushButton_2->setMaximumWidth(wid/3-indent);

    //ui->pushButton_3->setMinimumWidth(wid/3-indent);
    ui->pushButton_3->setMaximumWidth(wid/3-indent);
}
