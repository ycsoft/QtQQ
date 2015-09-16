/********************************************************************************
** Form generated from reading UI file 'passworddlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDDLG_H
#define UI_PASSWORDDLG_H

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
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_passworddlg
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *password;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *repassword;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *bt_ok;
    QPushButton *bk_cancle;

    void setupUi(QDialog *passworddlg)
    {
        if (passworddlg->objectName().isEmpty())
            passworddlg->setObjectName(QString::fromUtf8("passworddlg"));
        passworddlg->resize(272, 103);
        gridLayout = new QGridLayout(passworddlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(passworddlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        password = new QLineEdit(passworddlg);
        password->setObjectName(QString::fromUtf8("password"));

        horizontalLayout->addWidget(password);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(passworddlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        repassword = new QLineEdit(passworddlg);
        repassword->setObjectName(QString::fromUtf8("repassword"));

        horizontalLayout_2->addWidget(repassword);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        bt_ok = new QPushButton(passworddlg);
        bt_ok->setObjectName(QString::fromUtf8("bt_ok"));

        horizontalLayout_3->addWidget(bt_ok);

        bk_cancle = new QPushButton(passworddlg);
        bk_cancle->setObjectName(QString::fromUtf8("bk_cancle"));

        horizontalLayout_3->addWidget(bk_cancle);


        verticalLayout_2->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(passworddlg);

        QMetaObject::connectSlotsByName(passworddlg);
    } // setupUi

    void retranslateUi(QDialog *passworddlg)
    {
        passworddlg->setWindowTitle(QApplication::translate("passworddlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("passworddlg", "\346\226\260\345\257\206\347\240\201\357\274\232  ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("passworddlg", "\351\207\215\345\244\215\350\276\223\345\205\245\357\274\232", 0, QApplication::UnicodeUTF8));
        bt_ok->setText(QApplication::translate("passworddlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        bk_cancle->setText(QApplication::translate("passworddlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class passworddlg: public Ui_passworddlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDDLG_H
