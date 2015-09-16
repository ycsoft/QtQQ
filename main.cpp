
#include "loginwindow.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("HF-Soft");
    QCoreApplication::setOrganizationDomain("hf.com");
    QCoreApplication::setApplicationName("desk");


    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    QApplication::setOrganizationName("hf");
    QApplication::setQuitOnLastWindowClosed(false);


    Loginwindow w;
    w.show();
    return a.exec();
}
