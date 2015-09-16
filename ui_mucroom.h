/********************************************************************************
** Form generated from reading UI file 'mucroom.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUCROOM_H
#define UI_MUCROOM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
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

QT_BEGIN_NAMESPACE

class Ui_Mucroom
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QWebView *webView;
    QListWidget *list_chatroom;
    QFrame *frame;
    QTextEdit *textEdit_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    IconButton *bt_chat;
    IconButton *pushButton_2;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout;
    //文件列表
    QTabWidget *tabWidget_2;
    QWidget *tab_5;
    QGridLayout *gridLayout_4;
    QTreeWidget *file_list;
    QWidget *tab_6;
    QGridLayout *gridLayout_5;
    QTreeWidget *version_list;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QSplitter *splitter_2;
    QPushButton *bt_pull;
    QPushButton *bt_push;
    QPushButton *bt_add;
    QSplitter* sp_v;
    QSplitter* sp_h;
    QSplitter* sp_a;
    Widget  *file_wid;
    QWidget *file_tab;

    void setupUi(QDialog *Mucroom)
    {
        if (Mucroom->objectName().isEmpty())
            Mucroom->setObjectName(QString::fromUtf8("Mucroom"));
        Mucroom->resize(651, 503);
        Mucroom->setObjectName("Mucroom");
        Mucroom->setStyleSheet(QString::fromUtf8("QDialog#Mucroom{background-color: rgb(238, 237, 255);}"));
        //Mucroom->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        gridLayout_2 = new QGridLayout(Mucroom);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(0,0,0,0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget = new QWidget(Mucroom);
        widget->setObjectName(QString::fromUtf8("widget"));
        //widget->setStyleSheet(QString::fromUtf8("background:transparent;"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0,0,0,0);
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setDocumentMode(true);
        //聊天窗口布局
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(0,0,0,0);
        webView = new QWebView(tab);
        webView->setObjectName(QString::fromUtf8("webView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy);
        webView->setContextMenuPolicy(Qt::CustomContextMenu);
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));
        webView->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 237, 255);"));

        gridLayout_3->addWidget(webView, 0, 0, 1, 1);
        //聊天室成员列表
        list_chatroom = new QListWidget(tab);
        list_chatroom->setObjectName(QString::fromUtf8("list_chatroom"));
        list_chatroom->setMaximumSize(QSize(140, 16777215));
        //list_chatroom->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));

        gridLayout_3->addWidget(list_chatroom, 0, 1, 3, 1);

        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        //frame->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout_3->addWidget(frame, 1, 0, 1, 1);

        textEdit_2 = new QTextEdit(tab);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 237, 255);"));

        //gridLayout_3->addWidget(textEdit_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSpacing(5);
        horizontalLayout->addStretch();
        bt_chat =  new IconButton(tab,":/ui/navbutton_normal.png",
                                  ":/ui/navbutton_high.png",
                                  ":/ui/navbutton_down.png");//new QPushButton(tab);
        bt_chat->setObjectName(QString::fromUtf8("bt_chat"));

        horizontalLayout->addWidget(bt_chat);

        pushButton_2 =  new IconButton(tab,":/ui/navbutton_normal.png",
                                       ":/ui/navbutton_high.png",
                                       ":/ui/navbutton_down.png");//new QPushButton(tab);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);
        horizontalLayout->addStretch();
        QWidget *workw = new QWidget(tab);
        QVBoxLayout *workb = new QVBoxLayout();
        workb->setSpacing(0);
        workb->setContentsMargins(0,0,0,0);
        workb->addWidget(textEdit_2);
        QWidget *btnw = new QWidget(tab);
        btnw->setLayout(horizontalLayout);
        workb->addWidget(btnw);
        workw->setLayout(workb);
        gridLayout_3->addWidget(workw, 2, 0, 1, 1);

        //gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 2);

        tabWidget->addTab(tab, QString());

        file_tab = new QWidget(Mucroom);
        file_wid = new Widget(file_tab);
        QVBoxLayout *vb = new QVBoxLayout(file_tab);
        vb->setContentsMargins(0,0,0,0);
        vb->addWidget(file_wid);

        tabWidget->addTab(file_tab, QString::fromLocal8Bit("共享文件"));


//        tab_2 = new QWidget();
//        tab_2->setObjectName(QString::fromUtf8("tab_2"));
//        gridLayout_6 = new QGridLayout(tab_2);
//        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
//        verticalLayout = new QVBoxLayout();
//        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
//        tabWidget_2 = new QTabWidget(tab_2);
//        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
//        tabWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
//        tabWidget_2->setDocumentMode(true);
//        tab_5 = new QWidget();
//        tab_5->setObjectName(QString::fromUtf8("tab_5"));
//        gridLayout_4 = new QGridLayout(tab_5);
//        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
//        file_list = new QTreeWidget(tab_5);
//        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
//        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
//        file_list->setHeaderItem(__qtreewidgetitem);
//        file_list->setObjectName(QString::fromUtf8("file_list"));
//        file_list->setContextMenuPolicy(Qt::CustomContextMenu);
//        file_list->setFrameShadow(QFrame::Raised);

//        gridLayout_4->addWidget(file_list, 0, 0, 1, 1);

//        tabWidget_2->addTab(tab_5, QString());
//        tab_6 = new QWidget();
//        tab_6->setObjectName(QString::fromUtf8("tab_6"));
//        gridLayout_5 = new QGridLayout(tab_6);
//        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
//        version_list = new QTreeWidget(tab_6);
//        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
//        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
//        version_list->setHeaderItem(__qtreewidgetitem1);
//        version_list->setObjectName(QString::fromUtf8("version_list"));
//        version_list->setContextMenuPolicy(Qt::CustomContextMenu);
//        version_list->setFrameShadow(QFrame::Raised);

//        gridLayout_5->addWidget(version_list, 0, 0, 1, 1);

//        tabWidget_2->addTab(tab_6, QString());

//        verticalLayout->addWidget(tabWidget_2);

//        horizontalLayout_2 = new QHBoxLayout();
//        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
//        horizontalSpacer_2 = new QSpacerItem(240, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

//        horizontalLayout_2->addItem(horizontalSpacer_2);

//        splitter_2 = new QSplitter(tab_2);
//        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
//        splitter_2->setOrientation(Qt::Horizontal);
//        bt_pull = new QPushButton(splitter_2);
//        bt_pull->setObjectName(QString::fromUtf8("bt_pull"));
//        bt_pull->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
//"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
//        splitter_2->addWidget(bt_pull);
//        bt_push = new QPushButton(splitter_2);
//        bt_push->setObjectName(QString::fromUtf8("bt_push"));
//        bt_push->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
//"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
//        splitter_2->addWidget(bt_push);
//        bt_add = new QPushButton(splitter_2);
//        bt_add->setObjectName(QString::fromUtf8("bt_add"));
//        bt_add->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
//"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
//        splitter_2->addWidget(bt_add);

//        horizontalLayout_2->addWidget(splitter_2);


//        verticalLayout->addLayout(horizontalLayout_2);


//        gridLayout_6->addLayout(verticalLayout, 0, 0, 1, 1);

//        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);

        sp_v = new QSplitter(Qt::Vertical,tab);
        sp_v->addWidget(webView);
        sp_v->addWidget(workw);

        sp_h = new QSplitter(Qt::Horizontal,tab);
        sp_h->addWidget(sp_v);
        sp_h->addWidget(list_chatroom);

        gridLayout_3->addWidget(sp_h,0,0,1,1);


        retranslateUi(Mucroom);

        tabWidget->setCurrentIndex(0);
//        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Mucroom);
    } // setupUi

    void retranslateUi(QDialog *Mucroom)
    {
        Mucroom->setWindowTitle(QApplication::translate("Mucroom", "Dialog", 0, QApplication::UnicodeUTF8));
        bt_chat->setText(QApplication::translate("Mucroom", "\350\201\212\345\244\251\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Mucroom", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Mucroom", "\350\201\212\345\244\251", 0, QApplication::UnicodeUTF8));
//        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("Mucroom", "\346\226\207\344\273\266\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
//        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("Mucroom", "\347\211\210\346\234\254\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
//        bt_pull->setText(QApplication::translate("Mucroom", "\346\233\264\346\226\260", 0, QApplication::UnicodeUTF8));
//        bt_push->setText(QApplication::translate("Mucroom", "\345\220\214\346\255\245", 0, QApplication::UnicodeUTF8));
//        bt_add->setText(QApplication::translate("Mucroom", "\346\267\273\345\212\240\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Mucroom", "\346\226\207\344\273\266\345\205\261\344\272\253", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Mucroom: public Ui_Mucroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUCROOM_H
