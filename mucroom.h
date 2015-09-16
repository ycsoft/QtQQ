#ifndef MUCROOM_H
#define MUCROOM_H

#include <QDialog>
#include "listwindow.h"
#include <QXmppMucManager.h>
#include <QList>
#include <list>
#include "chats.h"

#include <QModelIndex>


namespace Ui {
class Mucroom;
}

class Mucroom : public QDialog
{
    Q_OBJECT

public:
    explicit Mucroom(QWidget *parent = 0);
    ~Mucroom();
    QString getmucroomJid(QString);
    void joinroom(QString);
    void keyPressEvent(QKeyEvent *e);
    void setparticipantNickname(QString);
    QString getCurrentTime();
    void scrollToBottom();
    void setroomname(QString);
    void set_remotepath(QString);
    bool commit;

public slots:
    void slotclosed();
    void slotloadmessage(QRect);
    void showlist(QString);
    void addMessage(QString fromjid, QString msg);
    void sendMucMessage();
    void handleMessage(QString fromjid,QString msg);
    //打开文件列表
    void slotpull();
    void slotcommit();
    void filepush();
    void flushfilelist(int);
    void slotQActionfile();
    void slotQAction();
    void slotQActionopenfile();
    void setcommitor(QString);
    void setcommit_msg(QString);
    void getchats();
    void slotpushfinished();
    void removelist(QString);
    void slotfiledownfinished();
    void slotQActionopendir();
    void openfile(QModelIndex);
    void slotaddfile();

private slots:
    void on_file_list_customContextMenuRequested(const QPoint &pos);
    void on_version_list_customContextMenuRequested(const QPoint &pos);

private:
    void set_path(QString);
    char path[256];
    bool flushflag;
    Ui::Mucroom *ui;
    QString roomJid_;
    QString participantNickname;
    QString roomname_;
//    QStringList list;
    QXmppMucRoom* mucroom_addr;
    bool msgflag;
    QList<QString> v_list;
    QList<QString> f_list;
    bool file_reset;
    bool version_reset;
    QString ver;
    QString fname_fversion;
    QString head;
    chats* chat;
    char commitor[256];//
    char commit_msg[256];//
    char file_name[256];//
    char remote_url[256];

};

#endif // MUCROOM_H



