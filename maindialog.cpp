#include "maindialog.h"
#include "ui_maindialog.h"
#include "setstate.h"
#include "chatwindow.h"
#include "roomchat.h"
#include "mucroom.h"
#include "listwindow.h"
#include "ui_listwindow.h"
#include "skin/tabbutton.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QMessagebox>

MainDialog* MainDialog::Instance = NULL;
MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    setWindowTitle(LOCAL("会话"));

    //tabwidget = new QTabWidget(this);
    //QGridLayout* mainlayout = new QGridLayout(this);
    //mainlayout->addWidget(tabwidget,0,0,1,1);

    tabwidget = ui->tabWidget;
//    ui->tabWidget->setTabsClosable(true);
//    ui->tabWidget->setMovable(true);
//    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(slotclosechildwindow(int)));
//    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabchanged(int)));
//    closestate = 0;
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::ClickTabButton(QString txt)
{
    QWidget *widget = hash_tabwin[txt];
    ui->stack->setCurrentWidget(widget);
    //ui->stack->setVisible(true);
    QList<QString> keys = hash_btn.keys();
    int count = keys.count();
    for ( int i = 0 ; i < count; ++i)
    {
        TabButton   *btn = (TabButton*)hash_btn[ keys[i] ];
        if ( keys[i] != txt )
            btn->setButtonDown(false);
        else
            btn->setButtonDown(true);

    }
}

void MainDialog::tabButtonClick(QString txt)
{
    //qDebug()<<"TabButton Click"<<txt;

    m_listwindow->getUI()->stackedWidget->setVisible(false);
    QWidget *widget = hash_tabwin[txt];
    ui->stack->setCurrentWidget(widget);
    ui->stack->setVisible(true);
    QList<QString> keys = hash_btn.keys();
    int count = keys.count();
    for ( int i = 0 ; i < count; ++i)
    {
        TabButton   *btn = (TabButton*)hash_btn[ keys[i] ];
        if ( keys[i] != txt )
            btn->setButtonDown(false);
        else
            btn->setButtonDown(true);

    }
}

void MainDialog::tabCloseClick(QString txt)
{
    QWidget *widget = hash_tabwin[txt];
    TabButton *btn = (TabButton*)hash_btn[txt];

    settray(widget);
    btn->setVisible(false);


    QHash<QString,QWidget*>::iterator iter = hash_btn.find( txt );


    ui->stack->removeWidget(widget);
    ui->tablay->removeWidget(btn);

    iter = hash_tabwin.find(txt);
    if ( iter != hash_tabwin.end())
        hash_tabwin.erase(iter);
    iter = hash_btn.find(txt);
    if ( iter != hash_btn.find(txt))
        hash_btn.erase(iter);
}

void MainDialog::addwindow(QWidget *window, QString jid,QString nick)
{

    //如果已存在，则不需要重复添加
    if ( hash_tabwin.find(nick) != hash_tabwin.end())
    {
        //ui->stack->setCurrentWidget(window);
        ClickTabButton( nick );
        return;
    }

    TabButton *tab = new TabButton(this);
    tab->SetButtonText(nick);
    hash_btn[nick] = tab;

    connect(tab,SIGNAL(tabButtonClick_sig(QString)),this,SLOT(tabButtonClick(QString)));
    connect(tab,SIGNAL(tabCloseClick_sig(QString)),this,SLOT(tabCloseClick(QString)));
    ui->tablay->insertWidget( ui->tablay->count()-1,tab);
    ui->stack->addWidget(window);
    ui->stack->setCurrentWidget(window);
    if ( hash_tabwin.find( nick ) == hash_tabwin.end() )
        hash_tabwin[nick] = window;
    ClickTabButton( nick );

}

void MainDialog::addwindow(QWidget * childwindow,QString lable,int type,QString jid)
{

    if ( hash_tabwin.find(lable) != hash_tabwin.end())
    {
        ClickTabButton( lable );
        return;
    }

    TabButton *tab = new TabButton(this);
    tab->SetButtonText(lable);
    hash_btn[lable] = tab;

    connect(tab,SIGNAL(tabButtonClick_sig(QString)),this,SLOT(tabButtonClick(QString)));
    connect(tab,SIGNAL(tabCloseClick_sig(QString)),this,SLOT(tabCloseClick(QString)));
    ui->tablay->insertWidget( ui->tablay->count()-1,tab);
    ui->stack->addWidget(childwindow);
    ui->stack->setCurrentWidget(childwindow);
    if ( hash_tabwin.find( lable ) == hash_tabwin.end() )
        hash_tabwin[lable] = childwindow;
    ClickTabButton( lable );
    hash_windowtype.insert(childwindow,type);
}
void MainDialog::slotclosechildwindow(int index)
{
    QWidget* w = ui->tabWidget->widget(index);
    settray(w);
    ui->tabWidget->removeTab(index);
    ui->tabWidget->repaint();
    if(ui->tabWidget->count() == 0)
    {
        m_listwindow->getUI()->stackedWidget->setVisible(true);
        m_listwindow->getUI()->session_Widget->setVisible(false);
        this->hide();
    }
}
int MainDialog::tabcount()
{
    return ui->tabWidget->count();
}
void MainDialog::closeEvent(QCloseEvent *e)
{
    if(ui->tabWidget->count() == 1)
    {
        int index = ui->tabWidget->currentIndex();
        slotclosechildwindow(index);
        return;
    }
    setstate* s = new setstate(this);
    s->exec();

    if(1 == closestate)
    {
        int index = ui->tabWidget->currentIndex();
        slotclosechildwindow(index);
        e->ignore();
        closestate = 0;
        return;
    }
    if(2 == closestate)
    {
        while(ui->tabWidget->count() != 0)
        {
            int index = ui->tabWidget->currentIndex();
            slotclosechildwindow(index);
            closestate = 0;
        }
        return;
    }
    e->ignore();
}
void MainDialog::setclosestate(int state)
{
    closestate = state;
}
void MainDialog::settray(QWidget *w)
{
    if(hash_windowtype.find(w) == hash_windowtype.end())
        return;
    if(hash_windowtype.value(w) == 1)
    {
        static_cast<Chatwindow*>(w)->slotclosed();
    }
    else if(hash_windowtype.value(w) == 2)
    {
        static_cast<RoomChat*>(w)->slotclosed();
    }
    else
        return;
}
void MainDialog::recvchat(QString jid, QString body)
{
    if(hash_jidwindow.find(jid) == hash_jidwindow.end())
        return;
    QWidget* w = hash_jidwindow.value(jid);
    int index = ui->tabWidget->indexOf(w);

    if(index < 0)
        return;

    if(ui->tabWidget->currentWidget() == w)
        return;

    QString title = ui->tabWidget->tabText(index);
    if(title.contains("(") && title.contains(")"))
    {
        QString number = title.split("(").at(1);
        number = number.split(")").at(0);

        int num = number.toInt();
        ++num;

        char buff[10];
        sprintf(buff,"%d",num);

        QString newtitle = title.split("(").at(0) + "(" + buff + ")";
        ui->tabWidget->setTabText(index,newtitle);
    }
    else
    {
        QString newtitle = title + "(1)";
        ui->tabWidget->setTabText(index,newtitle);
    }
}
void MainDialog::recvgroup(QString strwindow, QString, QString)
{
    if(hash_jidwindow.find(strwindow) == hash_jidwindow.end())
        return;
    QWidget* w = hash_jidwindow.value(strwindow);
    int index = ui->tabWidget->indexOf(w);

    if(index < 0)
        return;

    if(ui->tabWidget->currentWidget() == w)
        return;

    QString title = ui->tabWidget->tabText(index);
    if(title.contains("(") && title.contains(")"))
    {
        QString number = title.split("(").at(1);
        number = number.split(")").at(0);

        int num = number.toInt();
        ++num;

        char buff[10];
        sprintf(buff,"%d",num);

        QString newtitle = title.split("(").at(0) + "(" + buff + ")";
        ui->tabWidget->setTabText(index,newtitle);
    }
    else
    {
        QString newtitle = title + "(1)";
        ui->tabWidget->setTabText(index,newtitle);
    }
}

void MainDialog::recvmuc(QString str, QString)
{
    if(hash_jidwindow.find(str) == hash_jidwindow.end())
        return;
    QWidget* w = hash_jidwindow.value(str);
    int index = ui->tabWidget->indexOf(w);

    if(index < 0)
        return;

    if(ui->tabWidget->currentWidget() == w)
        return;

    QString title = ui->tabWidget->tabText(index);
    if(title.contains("(") && title.contains(")"))
    {
        QString number = title.split("(").at(1);
        number = number.split(")").at(0);

        int num = number.toInt();
        ++num;

        char buff[10];
        sprintf(buff,"%d",num);

        QString newtitle = title.split("(").at(0) + "(" + buff + ")";
        ui->tabWidget->setTabText(index,newtitle);
    }
    else
    {
        QString newtitle = title + "(1)";
        ui->tabWidget->setTabText(index,newtitle);
    }
}

void MainDialog::tabchanged(int index)
{
    if(ui->tabWidget->count() == 0)
        return;
    QString title = ui->tabWidget->tabText(index);

    if(title.contains("(") && title.contains(")"))
    {
        title = title.split("(").at(0);
        ui->tabWidget->setTabText(index,title);
    }
    //setMinimumHeight(m_listwindow->height() - m_listwindow->getUI()->pushButton_2->height());
}
