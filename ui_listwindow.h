/********************************************************************************
** Form generated from reading UI file 'listwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTWINDOW_H
#define UI_LISTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QSplitter>

#include "skin/iconbutton.h"
#include "skin/framelesswin.h"


QT_BEGIN_NAMESPACE

class Ui_Listwindow
{
public:
    QGridLayout *gridLayout_5;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    //QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    //QFrame *LoggerIcon;
    QLabel *label_jid;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    IconButton *pushButton;
    IconButton *pushButton_2;
    IconButton *pushButton_3;
    QStackedWidget *stackedWidget;
    QWidget *friend_page;
    QGridLayout *gridLayout;
    QListWidget *NameList;
    QWidget *group_page;
    QGridLayout *gridLayout_2;
    QTreeView *fr_;
    QWidget *mucroom_page;
    QGridLayout *gridLayout_3;
    QTreeView *muc_;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QSplitter   *spliter;
    QLabel      *tip_lb;
    QLabel      *lb_logo;
    //QPushButton *FindBtt;

    QWidget     *session_Widget;
//    QTabWidget  *session_tabs;
    QHBoxLayout *session_lay;
    //QPushButton *session_button;


    void setupUi(FramelessWin *Listwindow)
    {
        if (Listwindow->objectName().isEmpty())
            Listwindow->setObjectName(QString::fromUtf8("Listwindow"));

        //session_button = new QPushButton(Listwindow);
        //session_button ->setText(LOCAL("会话"));



        Listwindow->resize(281, 516);

        gridLayout_5 = new QGridLayout(Listwindow);

        //标题栏
        QWidget *tipw = new QWidget(Listwindow);
        tipw->setObjectName("tipw");
        tipw->setStyleSheet("border-image: url(:/ui/tip.png);");
        QHBoxLayout *tiplay = new QHBoxLayout(tipw);

        tiplay->setContentsMargins(0,5,0,5);

        tip_lb = new QLabel(tipw);
        tip_lb->setObjectName("tiplb");
        tip_lb->setStyleSheet("font: 75 14pt 'Times New Roman';color: rgb(85, 255, 255);");
        lb_logo = new QLabel(tipw);
        QPixmap logo(":/ui/qq.png");
        lb_logo->setPixmap(logo);


        IconButton *closeb = new IconButton(Listwindow,":/ui/btn_close_normal.png",":/ui/btn_close_highlight.png",":/ui/btn_close_down.png");

        QObject::connect(closeb,SIGNAL(clicked()),Listwindow,SLOT(close()));

        //tiplay->addStretch();
        tiplay->addWidget(lb_logo);
        tiplay->addWidget(tip_lb);
        tiplay->addStretch();
        tiplay->addWidget(closeb,0,Qt::AlignTop | Qt::AlignRight);

        //tip_lb->setText("Hello");


        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        //gridLayout_5->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(Listwindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 237, 255);"));
        //frame->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        /*
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(200, 80));
        label->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";\n"
"border-image: url(:/Icon_list_head.png);\n"
"color: rgb(0, 0, 0);\n"
""));

        verticalLayout_2->addWidget(label);
        label->setVisible(false);

        */
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        /*
        LoggerIcon = new QFrame(frame);
        LoggerIcon->setObjectName(QString::fromUtf8("LoggerIcon"));
        LoggerIcon->setStyleSheet(QString::fromUtf8("border-image: url(:/Icon_logger.png);"));

        horizontalLayout_3->addWidget(LoggerIcon);
        */
        label_jid = new QLabel(frame);
        label_jid->setObjectName(QString::fromUtf8("label_jid"));
        label_jid->setText("");
        label_jid->setVisible(false);

        /*label_jid->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";\n"
"background:transparent;"));
*/
  //      horizontalLayout_3->addWidget(label_jid);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSpacing(0);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton = new IconButton(Listwindow,":/ui/navbutton_normal.png",
                                    ":/ui/navbutton_high.png",
                                    ":/ui/navbutton_down.png");
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new IconButton(Listwindow,":/ui/navbutton_normal.png",
                                      ":/ui/navbutton_high.png",
                                      ":/ui/navbutton_down.png");
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new IconButton(Listwindow,":/ui/navbutton_normal.png",
                                      ":/ui/navbutton_high.png",
                                      ":/ui/navbutton_down.png");
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(pushButton_3);

        verticalLayout->addWidget(tipw);


        verticalLayout->addLayout(horizontalLayout_2);

        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        friend_page = new QWidget();
        friend_page->setObjectName(QString::fromUtf8("friend_page"));
        gridLayout = new QGridLayout(friend_page);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        NameList = new QListWidget(friend_page);
        NameList->setObjectName(QString::fromUtf8("NameList"));
        NameList->setContextMenuPolicy(Qt::CustomContextMenu);
        NameList->setStyleSheet(QString::fromUtf8("border: none;\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(NameList, 0, 0, 1, 1);

        stackedWidget->addWidget(friend_page);
        group_page = new QWidget();
        group_page->setObjectName(QString::fromUtf8("group_page"));
        gridLayout_2 = new QGridLayout(group_page);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        fr_ = new QTreeView(group_page);
        fr_->setObjectName(QString::fromUtf8("fr_"));
        fr_->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(fr_, 0, 0, 1, 1);

        stackedWidget->addWidget(group_page);
        mucroom_page = new QWidget();
        mucroom_page->setObjectName(QString::fromUtf8("mucroom_page"));
        gridLayout_3 = new QGridLayout(mucroom_page);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        muc_ = new QTreeView(mucroom_page);
        muc_->setObjectName(QString::fromUtf8("muc_"));
        muc_->setFrameShadow(QFrame::Raised);

        gridLayout_3->addWidget(muc_, 0, 0, 1, 1);

        stackedWidget->addWidget(mucroom_page);


        //verticalLayout->addWidget(stackedWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(168, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        /*
        horizontalLayout->addItem(horizontalSpacer);


        FindBtt = new QPushButton(frame);
        FindBtt->setObjectName(QString::fromUtf8("FindBtt"));
        FindBtt->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(FindBtt);
        */

        verticalLayout->addLayout(horizontalLayout);
        //添加会话窗口
        session_Widget = new QWidget(frame);
        session_lay = new QHBoxLayout(session_Widget);
        session_lay->setContentsMargins(0,0,0,0);
        session_Widget->setLayout(session_lay);

        //session_tabs = new QTabWidget(frame);
        //sessionlay->addWidget(session_tabs);

        //QWidget *tab = new QWidget(session_tabs);
        //session_tabs->setVisible(false);
        session_Widget->setVisible(false);
        //session_button->setVisible(false);

        //verticalLayout->addWidget(session_button);


        //verticalLayout->addWidget(session_Widget);

        //QVBoxLayout *splitlay = new QVBoxLayout(frame);
        //spliter->setLayout(splitlay);
        //spliter->setLayoutDirection(Qt::LayoutDirection);
        spliter = new QSplitter(Qt::Vertical, frame);
        spliter->addWidget(stackedWidget);
        spliter->addWidget(session_Widget);
        verticalLayout->addWidget(spliter);



        verticalLayout_2->addLayout(verticalLayout);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_5->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(Listwindow);

        stackedWidget->setCurrentIndex(0);

        QMetaObject::connectSlotsByName(Listwindow);
    } // setupUi

    void retranslateUi(QDialog *Listwindow)
    {
        Listwindow->setWindowTitle(QApplication::translate("Listwindow", "Dialog", 0, QApplication::UnicodeUTF8));
        //label->setText(QString());
        label_jid->setText(QApplication::translate("Listwindow", "      TextLabel", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Listwindow", "\345\245\275\345\217\213", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Listwindow", "\347\276\244\347\273\204", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("Listwindow", "\346\212\200\346\234\257\346\224\257\346\214\201", 0, QApplication::UnicodeUTF8));
        //FindBtt->setText(QApplication::translate("Listwindow", "\346\237\245\346\211\276\345\245\275\345\217\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Listwindow: public Ui_Listwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTWINDOW_H
