/********************************************************************************
** Form generated from reading UI file 'sendfiles.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFILES_H
#define UI_SENDFILES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SendFiles
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *choose;
    QPushButton *send;

    void setupUi(QDialog *SendFiles)
    {
        if (SendFiles->objectName().isEmpty())
            SendFiles->setObjectName(QString::fromUtf8("SendFiles"));
        SendFiles->resize(238, 85);
        SendFiles->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        verticalLayout_2 = new QVBoxLayout(SendFiles);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(SendFiles);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit);

        choose = new QPushButton(SendFiles);
        choose->setObjectName(QString::fromUtf8("choose"));

        horizontalLayout->addWidget(choose);


        verticalLayout->addLayout(horizontalLayout);

        send = new QPushButton(SendFiles);
        send->setObjectName(QString::fromUtf8("send"));

        verticalLayout->addWidget(send);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SendFiles);

        QMetaObject::connectSlotsByName(SendFiles);
    } // setupUi

    void retranslateUi(QDialog *SendFiles)
    {
        SendFiles->setWindowTitle(QApplication::translate("SendFiles", "Dialog", 0, QApplication::UnicodeUTF8));
        choose->setText(QApplication::translate("SendFiles", "\351\200\211\346\213\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        send->setText(QApplication::translate("SendFiles", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SendFiles: public Ui_SendFiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFILES_H
