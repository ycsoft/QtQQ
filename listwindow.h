#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QDialog>
#include "loginwindow.h"
#include "qfiletrans.h"
#include "mucroom.h"
#include "filereceivedlg.h"
#include <QXmppRosterIq.h>
#include <QXmppRosterManager.h>
#include <QXmppVCardIq.h>
#include <QXmppVCardManager.h>
#include <QXmppRegisterIq.h>
#include <QModelIndex>
#include <QListWidget>
#include <QXmppMucManager.h>
#include <QXmppLogger.h>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSystemTrayIcon>
#include <QXmppCallManager.h>
#include <QCoreApplication>
#include <QAudioInput>
#include <QAudioOutput>
#include <QXmppRtpChannel.h>
#include <QDebug>
#include <QListWidgetItem>
#include <QMultiHash>
#include <QSet>
#include <QResizeEvent>


#include "skin/framelesswin.h"

namespace Ui {
class Listwindow;
}
class Chatwindow;
class RoomChat;
class Mucroom;

class MainDialog;
class Listwindow : public FramelessWin
{
    Q_OBJECT

protected:
    //void paintEvent(QPaintEvent *evt);

    void resizeEvent(QResizeEvent *evt);


public:
    explicit Listwindow(QWidget *parent = 0);
    virtual void SetupUI();
    ~Listwindow();
    typedef enum { GroupNewMsg,DoubleNewMsg,ChatNewMsg}  State;
    static   Listwindow *Instance();
   void contextMenuEvent(QContextMenuEvent*);//重载鼠标右键
    void moveToRightTop();  //显示窗口位置
    void closeEvent(QCloseEvent *e);
    QString Nicktojid(QString nick);
    QString Jidtonick(QString jid);
    void setpassword(QString);
    QSystemTrayIcon *createSysTray(QString fname,QObject *parent);//托盘
    void setChatlist(QString s)
    {
       chatlist_.removeOne(s);
    }
    void setGroupList(QString s)
    {
        groupChatlist.removeOne(s);
    }
    int showlist()
    {
       return chatlist_.size();
    }
    static QXmppMucManager* getMucmanager()
    {
        return mucmanager;
    }
    static QXmppCallManager* getcallmanager()
    {
        return callmanager;
    }
    Ui::Listwindow *getUI()
    {
        return ui;
    }

    QString getselfJID();
    void requestMucroomlist();  //发送查找mucroom的报文
   QMenu* creatTray();//创建右键菜单
   void creategroupwindow(QString);//根据群组id,创建窗口
   void createchatwindow(QString);//根据对方jid，创建聊天窗口
  //  void changeEvent(QEvent *e);
   void refreshgrouplist(QString);

   MainDialog           *m_main;
public slots:
   void insertfilelist();
   void copychatsfile();
   void flushfilelist(RoomChat*);
   void iqReceived(const QXmppIq &iq);
   void handleModifypassmsg(QString);
   void slotaddnew(QString);
   void slotmodify();//修改密码
   void Search();   //搜索用户
   /*RostManager get all other friends' Jid*/
   void fileFinished(QXmppTransferJob*);
   void slotrosterReceived();//获取好友的list
  // void presenceChanged(const QString& bareJid, const QString& resource);
   /*VCardManager get all other friends' Nickname*/
   void slotvCardRecieved(const QXmppVCardIq&);  //接受好友的jid，并推送到ListWidget
   /*VCardManager get self Nickname*/
   void slotclientvCardRecieved();//获取自己的jid
   void fileReceived(QXmppTransferJob*);   //  文件接收
   void doubleClicked(const QModelIndex &index);// 双击
   void messageReceived(const QXmppMessage &msg);//  接受消息
   void handlePrecenseReceive(const QXmppPresence &presence); // 接收Precense
   void addChatWindow(QString jid,QString msg);//    消息添加到窗口
   void getRoom();//       获取组列表
   void getFriend();//      获取好友列表
   void getMucRoom();//    获取聊天室列表
   void clickSession();
   void slotremovefriend();
   void logMessage(QXmppLogger::MessageType,QString);//接收服务器的消息
   void handleGroupList(QString);             //处理组报文
   void handleGroupChat(QModelIndex );           //双击组
   void handleMucroomList(QString);          //处理聊天室组报文
   void doubleclickmucRoom(QModelIndex);    //双击聊天室列表
   void addGroupMessages(QString,QString,QString);                 //接受组消息
  // void slotchangenick();   //修改昵称
   void changenick(QString new_nick);
   void slotNewMsg();
   void slotgroupchanged(QString);

   void trayIconActive(QSystemTrayIcon::ActivationReason reason);//托盘

   //void slotroomAdded(QXmppMucRoom*);
   //void lostacceptMucchat(QString,QString,QString);
   void slotQAction(); /**右键弹出菜单单击事件槽函数*/
   void Exet();
   void Disable();
   void Online();
   void slotListItemClick(QModelIndex); /*左键单击*/
   //聊天室

   void addMucroomWindows(QString tojid,QString fromjid,QString roomname,QString msg);
   void on_NameList_customContextMenuRequested(const QPoint &pos);
   void uploadchats();//将群聊天记录上传至服务器

   //语音
   void slotcallrecieved(QXmppCall*);
  // void slotCallStateChanged(QXmppCall::State);
  // void slotAudioModeChanged(QIODevice::OpenMode);
signals:
    void recvMsg(QString frommsg,QString msg);  //收到消息
    void addChatWindows(QString,QString);    //消息添加到聊天窗口
    void flashfilelist(RoomChat*);
// void setRosters(QStringList);
//void updateRosters();
    void handleSearch(QString);           //所有注册用户
    void handleModifypass(QString);
    void handleGroup(QString);             //查找组
    void handleMucroom(QString);            //查找聊天室信号
    void recvGroup(QString,QString,QString);
    void addGroupMessage(QString,QString,QString);  //添加组消息
    void SigNewMsg();    //   新消息
    void SigNewMsgs();
    void groupchanged(QString);//增加或者删除群成员发出信号
    void roomchatshow(RoomChat*);
//聊天室
    void recvMucMsg(QString fromjid,QString msg);
    void addMucroomWindow(QString tojid,QString fromjid,QString roomname,QString msg );
public:
    QString getself();
    QString getcurrentpath();
    QHash <QString, QString> hash_nameAndjid;
    QHash <QString, QString> hash_jidAndname;
    QHash <QString, Mucroom*> hash_mucjidAndmucwin;
    QHash <QString, QString> hash_mucnameAndjid;
    void setchattray(QString,bool);
    void setgrouptray(QString,bool);
    void setwindowsendflag(QString,bool);
private:
   Ui::Listwindow *ui;
   QString currentpath;
   QHash <QString,Chatwindow*>  winmap_;   //聊天窗口   成员jid+窗口句柄
   QHash <QString,RoomChat*>  roommap_;   //组聊天窗口  组名+组窗口句柄
   QString nickNameSelf;     //自己的nick
   QString selfJID;          //自己的jid
   QString                  objectJID;
   QXmppVCardIq vCardself;
   QXmppRegisterIq registeriq;
   QStringList                 chatlist_;//聊天列表
   QStringList               rosterList_;//好友列表
   static Listwindow* m_instance;
   QStringList                   roomlist;//聊天室列表
   QHash <QString,bool>    usrst_;//用户是否在线
   //QTreeView    *fr_;           //群列表窗口
   //QTreeView  *muc_;          //聊天室tree列表
   QHash <QString,QStringList>   hash_wingroup;  //组信息 组名+成员列表
   QStandardItemModel* model;
   QStandardItemModel* model_muc;
   QSystemTrayIcon             *trayIcon_;//托盘
   QMenu                       *trayMenu_;
   State                       msgState_;
  // QList<State>                msgState_list;
   Chatwindow *wd;
   RoomChat *rc;
   QString  str_addFriend;
   QString  str_removeFriend;

   QPixmap pixmap_on;
   QPixmap pixmap_off;
   QPixmap pixmap_tray_on;
   QPixmap pixmap_tray_off;
   QIcon   icon_tray; //托盘图标

   QStringList    notifyList;
   QStringList    notifyGroupList;
   QStringList     groupChatlist; //组名列表
   static QXmppMucManager* mucmanager; //聊天室管理
   static QXmppCallManager* callmanager;
   QListWidgetItem* item;
   QHash<QString,bool> hash_groupclicked;//用来记录是否双击群组,用来辨认是否将消息加入到离线消息中
   QHash<QString,QStringList> hash_groupmsg;//存储离线群组消息
   QHash<QString,bool> hash_chatclicked;//用来记录是否与特定jid进行通信,同上
   QHash<QString,QStringList> hash_chatmsg;//用来存储离线单人消息
   QHash<QString,QSet<QString>> hash_jidAndgroup;//存储jid与组的关系
   QHash<QString,bool> hash_chattray;//用来托盘是否显示
   QHash<QString,bool> hash_grouptray;//同上
   bool groupadd;//标志变量,标志组信息改变的原因
   bool filesend;//标志是否接受文件
   QString password;//用来存储password
   bool online;//用来记录是否在线
   bool grouplistfinished;
};

#endif // LISTWINDOW_H
