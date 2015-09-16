#include "session.h"
#include <QSettings>

Session::Session(QObject *parent) :
    QObject(parent)
{
}

Session* Session::m_instance = NULL;

Session* Session::Instance()
{
    if (m_instance == NULL)
        m_instance = new Session();
    return m_instance;
}

Session::~Session()
{
    if (m_instance)
        delete m_instance;
    m_instance = NULL;
}

QString Session::getURL()
{
    QSettings set("http.ini",QSettings::IniFormat);
    QString url = set.value("base_url","").toString();
    return url;
}
