#ifndef ROOMCHAT_H
#define ROOMCHAT_H

#include <QDialog>
#include <QKeyEvent>
#include <QStringList>
#include <QList>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QTreeWidget>
#include <QByteArray>


#include "set_dirpath.h"

#include "chats.h"


namespace Ui {
class RoomChat;
}

class RoomChat : public QDialog
{
    Q_OBJECT

public:
    enum ChatType { CommonChat, GroupChat};
    explicit RoomChat(QWidget *parent = 0);


    ~RoomChat();
    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void setSelfJid(QString s)
    {
        selfjid_=s;
    }

    void setChatType(int t){
        chatType_ = t;
    }
    int getChatType() {
        return chatType_;
    }
    //?????????
    void setGrouplist(QStringList &s)
    {
        groupchatlist=s;
    }
    void setKey(QString s)
    {
        key = s;
    }
    static RoomChat* GetInstance()
    {
        if(!instance)
        {
            instance = new RoomChat;
        }
        return instance;
    }
    void clearList();
    void pushFriend(QStringList &list);   //
    void  scrollToBottom();
    QString getCurrentTime();           //
public slots:
    void slotclosed();
    void slotloadmessage(QRect);
    void flushfilelist(int);
    void sendMessages(); //
    void setchats();
    void addMessage(QString fromjid, QString msg);//
    void handleMessage(QString id,QString fromjid,QString body);
    void download();
    void push();
    void pull();
    void filepush();
    void slotQAction();
    void slotQActionfile();
    void slotQActionopenfile();
    void slotQActionopendir();
    void slotaddfriend();
    void slotpushfinished();
    void slotfiledownloadfinished();
    void slotaddfile();

    ////
    void upload();
public:
    void repostatus();
    void set_remotepath(QString);//
    void set_path(QString);//
    void set_downloadflag();
    void get_filename(QString);
    void chat_initwindow(QString);
    void setfilename(QString);
    void releasebutton();
    QString getpath();
    void timerEvent(QTimerEvent *event);
    void setcommitor(QString);
    void setcommit_msg(QString);
    int timer;
    bool commit;
    char commitor[256];//
    char commit_msg[256];//
    char file_name[256];//
    QString head;
private slots:
    void on_version_list_customContextMenuRequested(const QPoint &pos);
    void on_file_list_customContextMenuRequested(const QPoint &pos);
    void on_listWidget_customContextMenuRequested(const QPoint &pos);
    void on_file_list_doubleClicked(const QModelIndex &index);

signals:
    void addnewfreind(QString);

private:
    Ui::RoomChat *ui;
    QString  selfjid_;
    int         chatType_;
    chats* chat;
    QStringList groupchatlist;
    QString key;
    QString version;
    QString fname_fversion;
    QString str_addFriend;
    QString addJID;
    bool version_reset;
    bool file_reset;
    static RoomChat* instance;
    char remote_url[256];//
    char path[256];//
    int flag_down;//
    QString chatspath;
    QString chatsremote;
    QList<QString> v_list;//
    QList<QString> f_list;//
    bool msgflag;
    bool flushflag;
};

#endif // ROOMCHAT_H
