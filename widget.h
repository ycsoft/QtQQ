#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QUrl>
#include <QtWebKit>
#include <QWebView>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMap>

namespace Ui {
class Widget;
}



class Downloader:public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0,QString filename = "");
    ~Downloader();

    void start();
public slots:
    void finished();
    void readyRead();
private:
    QNetworkAccessManager   m_nam;
    QString                 m_fname;
    QFile                   *m_file;
    QNetworkReply           *m_reply;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void download(QString file);
    void loadURL(QUrl &url);

    void setGroup(QString group)
    {
        m_groupname = group;
    }

    Ui::Widget *ui;
public slots:
    void urlChange(const QUrl&);

    void finished();
    void readyRead();


private:


    QMap<QString,QFile*>     m_filemap;
    QNetworkAccessManager   m_nam;

    QString                 m_groupname;
};

#endif // WIDGET_H
