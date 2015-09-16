/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>
#include <QSplitter>

#include "skin/iconbutton.h"

QT_BEGIN_NAMESPACE

class Ui_Chatwindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3; //发送文件等按钮布局
    QLabel *label;
    IconButton *call_btt;
    IconButton *send_btt;
    IconButton *send_stop;
    QWebView *webView;
    QTextEdit *textEdit_2;  //输入框
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    IconButton *bt_chats;
    IconButton *pushButton_2;
    IconButton *FindBtt;
    QSplitter* sp;



    void setupUi(QDialog *Chatwindow)
    {
        if (Chatwindow->objectName().isEmpty())
            Chatwindow->setObjectName(QString::fromUtf8("Chatwindow"));
        Chatwindow->resize(578, 451);

        FindBtt = new IconButton(Chatwindow,":/ui/Icon_find.png",
                                 ":/ui/Icon_find_high.png",
                                 ":/ui/Icon_find.png");
        FindBtt->setObjectName(QString::fromUtf8("FindBtt"));
        FindBtt->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_2 = new QVBoxLayout(Chatwindow);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(Chatwindow);
        widget->setObjectName(QString::fromUtf8("widget"));

        //widget->setStyleSheet("background-color: rgb(238, 237, 255);");

        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        //verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0,0,0,0);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSpacing(5);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 12pt;\n"
"background:transparent;"));

        horizontalLayout_3->addWidget(label);

        call_btt = new IconButton(widget,":/ui/Icon_send.png",
                                  ":/ui/Icon_send_high.png",
                                  ":/ui/Icon_send.png");
        call_btt->setObjectName(QString::fromUtf8("call_btt"));
        call_btt->setMaximumSize(QSize(35, 60));


        horizontalLayout_3->addWidget(FindBtt);

        horizontalLayout_3->addWidget(call_btt);

        send_btt = new IconButton(widget,":/ui/Icon_call.png",
                                  ":/ui/Icon_call_high.png",
                                  ":/ui/Icon_call.png");
        send_btt->setObjectName(QString::fromUtf8("send_btt"));
        send_btt->setMaximumSize(QSize(35, 60));

        horizontalLayout_3->addWidget(send_btt);

        send_stop = new IconButton(widget,":/ui/Icon_call_stop.png",
                                   ":/ui/Icon_call_stop_high.png",
                                   ":/ui/Icon_call.png");
        send_stop->setObjectName(QString::fromUtf8("send_stop"));
        send_stop->setMaximumSize(QSize(35, 60));

        horizontalLayout_3->addWidget(send_stop);
        horizontalLayout_3->addStretch();

        //按钮位置换到历史区与输入区中间
//        verticalLayout->addLayout(horizontalLayout_3);

        webView = new QWebView(widget);
        webView->setObjectName(QString::fromUtf8("webView"));

        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy);
        webView->setContextMenuPolicy(Qt::CustomContextMenu);
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));
        webView->setRenderHints(QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
        //

        verticalLayout->addWidget(webView);
        //verticalLayout->addItem(horizontalLayout_3);

        QWidget *inputw = new QWidget(widget);
        //inputw->setStyleSheet("background-color: rgb(238, 237, 255);");
        QVBoxLayout *vbinputlay = new QVBoxLayout();
        vbinputlay->setSpacing(0);
        vbinputlay->setContentsMargins(0,0,0,0);

        textEdit_2 = new QTextEdit(widget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setEnabled(true);
        textEdit_2->setMaximumSize(QSize(16777215, 16777215));
        textEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 237, 255);"));

        vbinputlay->addItem(horizontalLayout_3);
        vbinputlay->addWidget(textEdit_2);

        inputw->setLayout(vbinputlay);
        //添加输入框
        //verticalLayout->addWidget(textEdit_2);
        verticalLayout->addWidget(inputw);

        sp = new QSplitter(Qt::Vertical,Chatwindow);
        sp->setContentsMargins(0,0,0,0);
        sp->addWidget(webView);
        sp->addWidget(inputw);

        verticalLayout->addWidget(sp);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        bt_chats = new IconButton(widget_2,":/ui/navbutton_normal.png",
                                  ":/ui/navbutton_high.png",
                                  ":/ui/navbutton_down.png");
        bt_chats->setObjectName(QString::fromUtf8("bt_chats"));

        horizontalLayout->addWidget(bt_chats);

        pushButton_2 = new IconButton(widget_2,":/ui/navbutton_normal.png",
                                      ":/ui/navbutton_high.png",
                                      ":/ui/navbutton_down.png");
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(widget_2);


        verticalLayout_2->addWidget(widget);


        retranslateUi(Chatwindow);

        QMetaObject::connectSlotsByName(Chatwindow);
    } // setupUi

    void retranslateUi(QDialog *Chatwindow)
    {
        Chatwindow->setWindowTitle(QApplication::translate("Chatwindow", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Chatwindow", "  NickName", 0, QApplication::UnicodeUTF8));
        call_btt->setText(QString());
        send_btt->setText(QString());
        send_stop->setText(QString());
        bt_chats->setText(QApplication::translate("Chatwindow", "\350\201\212\345\244\251\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Chatwindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Chatwindow: public Ui_Chatwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
