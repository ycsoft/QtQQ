#ifndef SEARCHDLG_H
#define SEARCHDLG_H

#include <QDialog>
#include <QStandardItemModel>

class QStandardItemModel;

namespace Ui {
class SearchDlg;
}

class searchData
{
public:
    searchData()
    {
        name = QString("");
        email = QString("");
        usrname = QString("");
        jid = QString("");
    }
    QString name;
    QString email;
    QString usrname;
    QString jid;
};
class SearchDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDlg(QWidget *parent = 0);
    ~SearchDlg();

    QString createSearchIQ(QString search,QString srv);
    enum Type{AddContact,UserSearch};
    void setType( int tp);
    int  getType(){
        return type_;
    }
    QString                 getJid(){
        return addJid_;
    }
 void addFriend();
signals:
 void addnewfreind(QString);

public slots:
    void                    btnSearchClick();
    void                    addContactClick();
    void                    handleSearch(QString s);
    void                    treeClick(QModelIndex index);
    //void                    slotchangeID();
    //void                    slotchangeName();
private:

    Ui::SearchDlg *ui;
    QStandardItemModel      *itemModel_;
    QString                 addJid_;
    int                     type_;
   // int                     flag_search;
};

#endif // SEARCHDLG_H
