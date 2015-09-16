#include "selectmucroom.h"
#include "mucroom.h"
#include "ui_selectmucroom.h"
#include "listwindow.h"
#include <QMessageBox>

SelectMucroom::SelectMucroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMucroom)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint;
        setWindowFlags(flags);
    bool check = connect(ui->Btt_confirm, SIGNAL(clicked()), this, SLOT(confirmClick()));
    Q_ASSERT(check);
}

SelectMucroom::~SelectMucroom()
{
    delete ui;
}


void SelectMucroom::confirmClick()
{
    roomJID = ui->text_roomname->text();
    //qDebug() << objectJID + "" + objectname;
    QXmppMucRoom* room = NULL;
    room = Listwindow::getMucmanager()->addRoom(roomJID);
    if(!room)
    {
        return;
    }
    else{
        if(objectJID == Listwindow::Instance()->getselfJID())
        {
            Mucroom* me = new Mucroom(0);
            me->setparticipantNickname(objectJID);
            me->joinroom(roomJID);
            me->show();
        }
        else
        {
            bool check = room->sendInvitation(objectJID, "Pls add Chatroom" + roomJID);
            if(!check)
            {
                QMessageBox::information(this, "Error", "Invatation Failure, Pls Try Again!");
            }
            else
            {
                qDebug() << "Invitation Success!";
            }
        }
        this->close();
    }
}

void SelectMucroom::tranobjectJID(QString JID)
{
    objectJID = JID;
}

void SelectMucroom::tranobjectname(QString name)
{
    objectname = name;
}
