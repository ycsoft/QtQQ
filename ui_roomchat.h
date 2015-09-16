/********************************************************************************
** Form generated from reading UI file 'roomchat.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMCHAT_H
#define UI_ROOMCHAT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

#include "skin/iconbutton.h"
#include "widget.h"


#define LOCAL(x) QString::fromLocal8Bit(x)

QT_BEGIN_NAMESPACE

class Ui_RoomChat
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QWebView *webView;
    QListWidget *listWidget;
    QTextEdit *textEdit_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;

    //聊天记录
    IconButton *bt_chats;
    //发送
    IconButton *pushButton;

    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_2;
    QWidget *tab_5;
    QGridLayout *gridLayout_4;
    QTreeWidget *file_list;
    QWidget *tab_6;
    QGridLayout *gridLayout_5;
    QTreeWidget *version_list;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter_2;
    QPushButton *bt_pull;
    QPushButton *bt_push;
    QPushButton *bt_add;
    QSplitter* sp_v;
    QSplitter* sp_h;
    QSplitter* sp_a;

    Widget      *file_wid;
    QWidget     *file_tab;

    void setupUi(QDialog *RoomChat)
    {
        if (RoomChat->objectName().isEmpty())
            RoomChat->setObjectName(QString::fromUtf8("RoomChat"));
        RoomChat->resize(651, 503);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RoomChat->sizePolicy().hasHeightForWidth());
        RoomChat->setSizePolicy(sizePolicy);
        RoomChat->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 237, 255);"));

        gridLayout = new QGridLayout(RoomChat);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0,0,0,0);

        tabWidget = new QTabWidget(RoomChat);
        tabWidget->setDocumentMode(true);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(0,0,0,0);

        webView = new QWebView(tab);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setMinimumSize(QSize(0, 0));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));
        webView->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 237, 255);"));

        gridLayout_2->addWidget(webView, 0, 0, 1, 1);

        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setEnabled(true);
        listWidget->setMinimumSize(QSize(0, 0));
        listWidget->setMaximumSize(QSize(16777215, 16777215));
        listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        //listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(listWidget, 0, 1, 2, 1);

        textEdit_2 = new QTextEdit(tab);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setMaximumSize(QSize(16777215, 16777215));
        textEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 237, 255);"));

        //gridLayout_2->addWidget(textEdit_2, 1, 0, 1, 1);

        //添加发送按钮
        QWidget *btnw = new QWidget(tab);
        horizontalLayout_2 = new QHBoxLayout(btnw);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->addStretch();
        horizontalLayout_2->addStretch();

        bt_chats = new IconButton(btnw,":/ui/navbutton_normal.png",
                                  ":/ui/navbutton_high.png",
                                  ":/ui/navbutton_down.png");//new QPushButton(tab);
        bt_chats->setObjectName(QString::fromUtf8("bt_chats"));
        //bt_chats->SetButtonText(LOCAL("发送"));

        horizontalLayout_2->addWidget(bt_chats);

        pushButton = new IconButton(btnw,":/ui/navbutton_normal.png",
                                    ":/ui/navbutton_high.png",
                                    ":/ui/navbutton_down.png");
        //new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);
        horizontalLayout_2->addStretch();
        btnw->setLayout(horizontalLayout_2);

        QWidget *workw = new QWidget(tab);
        QVBoxLayout *worklay = new QVBoxLayout();
        worklay->setSpacing(5);
        worklay->setContentsMargins(0,0,0,0);
        worklay->addWidget(textEdit_2);
        worklay->addWidget(btnw);
        workw->setLayout(worklay);
        gridLayout_2->addWidget(workw, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        //gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        file_tab = new QWidget(RoomChat);
        file_wid = new Widget(file_tab);
        QVBoxLayout *vb = new QVBoxLayout(file_tab);
        vb->setContentsMargins(0,0,0,0);
        vb->addWidget(file_wid);

        tabWidget->addTab(file_tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);
        sp_v = new QSplitter(Qt::Vertical,tab);
        sp_v->addWidget(webView);
        sp_v->addWidget(workw);

        sp_h = new QSplitter(Qt::Horizontal,tab);
        sp_h->addWidget(sp_v);
        sp_h->addWidget(listWidget);

//        sp_a = new QSplitter(Qt::Vertical,tab);
//        sp_a->addWidget(sp_h);

        gridLayout_2->addWidget(sp_h,0,0,1,1);

        retranslateUi(RoomChat);

        tabWidget->setCurrentIndex(0);
        //tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RoomChat);
    } // setupUi

    void retranslateUi(QDialog *RoomChat)
    {
        RoomChat->setWindowTitle(QApplication::translate("RoomChat", "Dialog", 0, QApplication::UnicodeUTF8));
        bt_chats->setText(QApplication::translate("RoomChat", "\350\201\212\345\244\251\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("RoomChat", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("RoomChat", "\350\201\212\345\244\251", 0, QApplication::UnicodeUTF8));
//        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("RoomChat", "\346\226\207\344\273\266\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
//        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("RoomChat", "\347\211\210\346\234\254\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
//        bt_pull->setText(QApplication::translate("RoomChat", "\346\233\264\346\226\260", 0, QApplication::UnicodeUTF8));
//        bt_push->setText(QApplication::translate("RoomChat", "\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
//        bt_add->setText(QApplication::translate("RoomChat", "\346\267\273\345\212\240\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(file_tab), QApplication::translate("RoomChat", "\347\276\244\345\205\261\344\272\253", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RoomChat: public Ui_RoomChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMCHAT_H
