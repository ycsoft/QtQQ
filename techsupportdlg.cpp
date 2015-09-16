#include "techsupportdlg.h"
#include "ui_techsupportdlg.h"
#include "chatwindow2.h"
#include "dlgcontainter.h"
#include "listwindow.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QFileDialog>

TechSupportDlg::TechSupportDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TechSupportDlg)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    ui->setupUi(this);

//   mainw = Listwindow::Instance();
}

TechSupportDlg::~TechSupportDlg()
{
    delete ui;
}
void TechSupportDlg::setDlgContainer(DlgContainter *cont)
{
    dlgcontainer_ = cont;
    connect(dlgcontainer_,SIGNAL(tabClosed(QString)),this,SLOT(tabClosed(QString)));
    /*
    dlgcontainer_->getTabWidget()->clear();
    dlgcontainer_->getTabWidget()->addTab(this,LOCAL("支持人员列表"));
    dlgcontainer_->getTabWidget()->addTab(single_,LOCAL("用户交流区"));
    dlgcontainer_->getTabWidget()->setCurrentWidget(this);
    dlgcontainer_->setMaximumSize(280,450);
    */
}

void TechSupportDlg::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}
void TechSupportDlg::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu  *menu = new QMenu(this);
    QAction *act_send = new QAction(this);
    QIcon   icon(":/UI/upload.png");
    bool    bcheck;
   // bcheck =  connect(act_send,SIGNAL(triggered()),this,SLOT(slotSendFile()));
   // Q_ASSERT(bcheck);


}
/*void TechSupportDlg::slotSendFile()
{
    QModelIndex index = ui->treeView->currentIndex();
    QString     tonick = index.data().toString();
    QString     tojid = MainWindow::getJidFromNick(tonick);
    QString     sfile = QFileDialog::getOpenFileName(this);
    QUtil::Instance()->sendFile(sfile,tojid+"/FT");

}*/

void TechSupportDlg::addChatWindow(QString jid,QString body)
{
  ChatWindow2 *wd =NULL;
  if ( winmap_.empty() || winmap_.find(jid) == winmap_.end())
  {
      chatList_.append(jid);
      wd = new ChatWindow2(mainw);
      winmap_.insert(jid,wd);

      wd->setWindowTitle(jid);
      wd->setChatJid(jid);
      wd->setChatType(ChatWindow2::CommonChat);
      wd->addMessage(jid,body);
      connect(wd,SIGNAL(sendMsg(QString,QString)),mainw,SLOT(sendMsg(QString,QString)));
      connect(mainw,SIGNAL(recvMsg(QString,QString)),wd,SLOT(handleMessage(QString,QString)));
  }
  wd = winmap_[jid];
  dlgcontainer_->getTabWidget()->setCurrentWidget(wd);

}
void TechSupportDlg::tabClosed(QString str)
{
    //winmap_.erase(winmap_.find(str.toStdString()));
    QString jid ;//= MainWindow::getJidFromNick(str);
    chatList_.removeOne(jid);
}

void TechSupportDlg::listDoubleClicked(QModelIndex index)
{

}
/*QStringList TechSupportDlg::getTechList()
{
    QStringList list;
    QString     str;
    QFile       conffile("config/techsupport.conf");
    if (!conffile.exists()){
        return list;
    }
    conffile.open(QIODevice::ReadOnly);
    while (!conffile.atEnd()){
        str = LOCAL(conffile.readLine().data());
        str = str.trimmed();
        if ( str.isEmpty() || str.at(0) == '#')
            continue;
        list.append(str.trimmed());
    }
    conffile.close();
    return list;
}*/
void TechSupportDlg::resetChatWindow()
{
   // getSingleWindow()->clearTabs();
}
