/********************************************************************************
** Form generated from reading UI file 'setdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDLG_H
#define UI_SETDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetDlg
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_3;
    QLabel *label_3;
    QLineEdit *line_fileshare;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditname;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditip;
    QPushButton *pushButton;

    void setupUi(QDialog *SetDlg)
    {
        if (SetDlg->objectName().isEmpty())
            SetDlg->setObjectName(QString::fromUtf8("SetDlg"));
        SetDlg->resize(302, 95);
        SetDlg->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        gridLayout = new QGridLayout(SetDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter_3 = new QSplitter(SetDlg);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(80, 16777215));
        splitter_3->addWidget(label_3);
        line_fileshare = new QLineEdit(splitter_3);
        line_fileshare->setObjectName(QString::fromUtf8("line_fileshare"));
        splitter_3->addWidget(line_fileshare);

        verticalLayout->addWidget(splitter_3);

        splitter_2 = new QSplitter(SetDlg);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditname = new QLineEdit(layoutWidget);
        lineEditname->setObjectName(QString::fromUtf8("lineEditname"));
        lineEditname->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEditname);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        lineEditip = new QLineEdit(layoutWidget1);
        lineEditip->setObjectName(QString::fromUtf8("lineEditip"));
        lineEditip->setMaximumSize(QSize(133, 16777215));
        lineEditip->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(lineEditip);

        splitter->addWidget(layoutWidget1);
        splitter_2->addWidget(splitter);
        pushButton = new QPushButton(splitter_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        splitter_2->addWidget(pushButton);

        verticalLayout->addWidget(splitter_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(SetDlg);

        QMetaObject::connectSlotsByName(SetDlg);
    } // setupUi

    void retranslateUi(QDialog *SetDlg)
    {
        SetDlg->setWindowTitle(QApplication::translate("SetDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SetDlg", "\346\226\207\344\273\266\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        line_fileshare->setText(QApplication::translate("SetDlg", "git://192.168.1.114/test", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetDlg", "\346\234\215\345\212\241\345\231\250\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        lineEditname->setText(QString());
        lineEditname->setPlaceholderText(QApplication::translate("SetDlg", "\346\234\215\345\212\241\345\231\250\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SetDlg", "\346\234\215\345\212\241\345\231\250IP", 0, QApplication::UnicodeUTF8));
        lineEditip->setPlaceholderText(QApplication::translate("SetDlg", "\346\234\215\345\212\241\345\231\250IP", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SetDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetDlg: public Ui_SetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDLG_H
