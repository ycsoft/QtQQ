#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QHash>
namespace Ui {
class MainDialog;
}


class Listwindow;
class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    void closeEvent(QCloseEvent *e);
    void setListWindow( Listwindow *win)
    {
        m_listwindow = win;
    }

    static MainDialog* getInstance()
    {
        if(Instance==NULL)
            Instance = new MainDialog(0);
        return Instance;
    }

    void ClickTabButton( QString txt );

public slots:
    void slotclosechildwindow(int);
    void recvgroup(QString,QString,QString);
    void recvchat(QString,QString);
    void recvmuc(QString,QString);
    void tabchanged(int);

    void tabButtonClick(QString txt);
    void tabCloseClick( QString txt );
signals:
    void closed();
public:
    void setclosestate(int);
    void addwindow(QWidget*,QString,int,QString);
    void addwindow( QWidget *, QString jid,QString nick);

    int tabcount();

    QTabWidget  *tabwidget;
    Ui::MainDialog  *GetUI()    { return ui;}
private:

    Ui::MainDialog *ui;
    static MainDialog* Instance;
    int closestate;
    QHash<QWidget*,int> hash_windowtype;
    void settray(QWidget*);
    QHash<QString,QWidget*> hash_jidwindow;
    Listwindow              *m_listwindow;

    QHash<QString , QWidget*>  hash_tabwin;
    QHash<QString , QWidget*>  hash_btn;
};

#endif // MAINDIALOG_H
