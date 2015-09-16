/********************************************************************************
** Form generated from reading UI file 'findfriend.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDFRIEND_H
#define UI_FINDFRIEND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindFriend
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *FindFriend)
    {
        if (FindFriend->objectName().isEmpty())
            FindFriend->setObjectName(QString::fromUtf8("FindFriend"));
        FindFriend->resize(212, 76);
        FindFriend->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        verticalLayout_2 = new QVBoxLayout(FindFriend);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FindFriend);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background:transparent"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(FindFriend);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        pushButton = new QPushButton(FindFriend);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(FindFriend);

        QMetaObject::connectSlotsByName(FindFriend);
    } // setupUi

    void retranslateUi(QDialog *FindFriend)
    {
        FindFriend->setWindowTitle(QApplication::translate("FindFriend", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FindFriend", "\345\245\275\345\217\213\350\264\246\345\217\267", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("FindFriend", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FindFriend: public Ui_FindFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDFRIEND_H
