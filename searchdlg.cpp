#include "searchdlg.h"
#include "ui_searchdlg.h"
#include "loginwindow.h"
#include "qfiletrans.h"
#include "listwindow.h"
#include "setdlg.h"
#include "listwindow.h"

#include <QtXml>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
#include <QCryptographicHash>


SearchDlg::SearchDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDlg)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
        flags |=Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint;
        setWindowFlags(flags);
    this->setWindowTitle(LOCAL("查找用户"));
    itemModel_ = new QStandardItemModel(0,4,this);
    itemModel_->setHeaderData(0,Qt::Horizontal,LOCAL("财政通行证账号"));
    itemModel_->setHeaderData(1,Qt::Horizontal,LOCAL("姓名"));
    itemModel_->setHeaderData(2,Qt::Horizontal,LOCAL("用户名"));
    itemModel_->setHeaderData(3,Qt::Horizontal,tr("Email"));
    ui->treeView->setColumnWidth(0,250);
    ui->treeView->setColumnWidth(1,100);
    ui->treeView->setColumnWidth(2,100);
    ui->treeView->setColumnWidth(3,200);
    ui->treeView->setModel(itemModel_);
    ui->pushButton_AddContact->setEnabled(false);
    //flag_search = 0;
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(treeClick(QModelIndex)));
    connect(ui->pushButton_find,SIGNAL(clicked()),this,SLOT(btnSearchClick()));
    connect(ui->pushButton_AddContact,SIGNAL(clicked()),this,SLOT(addContactClick()));
    //connect(ui->radioButton_id, SIGNAL(clicked(bool)), this, SLOT(slotchangeID()));
    //connect(ui->radioButton_name, SIGNAL(clicked(bool)), this, SLOT(slotchangeName()));
    bool check;
  check= connect(Listwindow::Instance(),SIGNAL(handleSearch(QString)),this,SLOT(handleSearch(QString)));
  check = connect(this, SIGNAL(addnewfreind(QString)), Listwindow::Instance(), SLOT(slotaddnew(QString)));
   Q_ASSERT(check);
    type_ = AddContact;
}

void SearchDlg::setType(int tp)
{
    type_ = tp;
    if ( tp == UserSearch )
    {
        ui->pushButton_AddContact->setText(LOCAL("选择"));
    }
}

void SearchDlg::btnSearchClick()
{
    ui->pushButton_find->setEnabled(false);
    QString  search = ui->lineEdit->text();
    if(ui->radioButton_id->isChecked())
    {
        QString  search_md5;
        if(search == "*")
        {
            search_md5 = "*";
        }
        else
        {
            QByteArray bb;
            bb = QCryptographicHash::hash(search.toLocal8Bit(), QCryptographicHash::Md5);
            search_md5.append(bb.toHex());
        }
        QString  str=SetDlg::Instance()->getsvr();
        QString  srv = "search.";
        srv += str;
        QString  iq = createSearchIQ(search_md5,srv);
        int      rc = itemModel_->rowCount();
        itemModel_->removeRows(0,rc);
        Loginwindow::getclient()->sendData(iq.toLocal8Bit());
    }
    else if(ui->radioButton_name->isChecked())
    {
        QString str = SetDlg::Instance()->getsvr();
        QString srv = "search.";
        srv += str;
        QString iq = createSearchIQ(search, srv);
        int     rc = itemModel_->rowCount();
        itemModel_->removeRows(0, rc);
        Loginwindow::getclient()->sendData(iq.toLocal8Bit());
    }
}

void SearchDlg::addContactClick()
{
    if (type_ == AddContact){
        if (addJid_.isEmpty())
            return;
    addFriend();
    }else if (type_ == UserSearch){
        QDialog::accept();
    }
}

void SearchDlg::treeClick(QModelIndex index)
{
    int row = index.row(); //row number
    QStandardItem  *item = itemModel_->item(row);
    QString jid = item->text();
    addJid_ = jid;
    ui->pushButton_AddContact->setEnabled(true);
}

void SearchDlg::handleSearch(QString s)
{  
    QDomDocument  dom;
    QDomElement   elem;
    QVector<searchData>  vecData;
    int row = 0;

   if (!dom.setContent(s))
   {
       ui->pushButton_find->setEnabled(true);
       return;
   }
    elem = dom.firstChildElement("iq").firstChildElement("query").firstChildElement("x").firstChildElement("item");
    if (elem.isNull())
    {
        ui->pushButton_find->setEnabled(true);
        return;
    }
    while (!elem.isNull())
    {
        QDomElement  field = elem.firstChildElement("field");
        searchData   data;
        while (!field.isNull())
        {
            QString attr = field.attribute("var");
            if(attr == "Name")
                data.name = field.firstChildElement("value").lastChild().nodeValue();
            if (attr == "Email")
                data.email = field.firstChildElement("value").lastChild().nodeValue();
            if (attr == "Username")
                data.usrname = field.firstChildElement("value").lastChild().nodeValue();
            if (attr == "jid")
                data.jid = field.firstChildElement("value").lastChild().nodeValue();
            field = field.nextSiblingElement();
        }
        vecData.append(data);
        QStandardItem *it1 = new QStandardItem(data.jid);
        QStandardItem *it2 = new QStandardItem(data.name);
        QStandardItem *it3 = new QStandardItem(data.usrname);
        QStandardItem *it4 = new QStandardItem(data.email);
        itemModel_->setItem(row,0,it1);
        itemModel_->setItem(row,1,it2);
        itemModel_->setItem(row,2,it3);
        itemModel_->setItem(row,3,it4);
        ++row;
        elem = elem.nextSiblingElement();
        ui->pushButton_find->setEnabled(true);
    }
}

SearchDlg::~SearchDlg()
{
    delete ui;
}

 QString SearchDlg::createSearchIQ(QString search,QString srv)
{
  QDomDocument  dom;
  QDomElement   elem;
  int           i = 0;
 // id_           =  createID();
  elem = dom.createElement("iq");
  elem.setAttribute("type","set");
  elem.setAttribute("to",srv);
  elem.setAttribute("id","");

  QDomElement   query = dom.createElement("query");
  query.setAttribute("xmlns","jabber:iq:search");
  elem.appendChild(query);

  QDomElement   x  = dom.createElement("x");
  x.setAttribute("xmlns","jabber:x:data");
  x.setAttribute("type","submit");
  query.appendChild(x);

  QDomElement   field1  = dom.createElement("field");
  field1.setAttribute("type","hidden");
  field1.setAttribute("var","FORM_TYPE");
  QDomElement   value = dom.createElement("value");
  QDomText      dt = dom.createTextNode("jabber:iq:search");
  value.appendChild(dt);
  field1.appendChild(value);
  x.appendChild(field1);

  QDomElement   field[3];
  QStringList   varlist;
  varlist.append("Username");
  varlist.append("Name");
  varlist.append("Email");
  for ( i = 0 ; i < 3; ++i)
  {
      field[i]= dom.createElement("field");
      field[i].setAttribute("type","boolean");
      field[i].setAttribute("var",varlist[i]);
      QDomElement value = dom.createElement("value");
      QDomText    t = dom.createTextNode("1");
      value.appendChild(t);
      field[i].appendChild(value);
      x.appendChild(field[i]);
  }
  /*
   * "<iq type="set" to="search.test.xmpp60" id="">
       <query xmlns="jabber:iq:search">
        <x xmlns="jabber:x:data" type="submit">
         <field type="hidden" var="FORM_TYPE">
          <value>jabber:iq:search</value>
         </field>
         <field type="boolean" var="Username">
          <value>1</value>
         </field>
         <field type="boolean" var="Name">
          <value>1</value>
         </field>
         <field type="boolean" var="Email">
          <value>1</value>
         </field>
         <field type="text-single" var="search">
          <value>*</value>
         </field>
        </x>
       </query>
      </iq>
  */

  QDomElement  fields = dom.createElement("field");
  fields.setAttribute("type","text-single");
  fields.setAttribute("var","search");
  QDomElement  values = dom.createElement("value");
  QDomText      txt = dom.createTextNode(search);
  values.appendChild(txt);
  fields.appendChild(values);
  x.appendChild(fields);
  dom.appendChild(elem);
  QString xmls = dom.toString();

  return xmls;
}

 void SearchDlg::addFriend()
 {
     QString str = "<presence from=\"\" to=\"";
        str += addJid_;
       str += "\" type=\"subscribe\"> </presence>";
     Loginwindow::getclient()->sendData(str.toLocal8Bit());
        emit addnewfreind(addJid_);
 }
