/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Loginwindow
{
public:
    QLineEdit *usernameLine;
    QLineEdit *passwordLine;
    QWidget *widget;
    QPushButton *loginBtt;
    QWidget *widget_2;
    QPushButton *pushButton;

    void setupUi(QDialog *Loginwindow)
    {
        if (Loginwindow->objectName().isEmpty())
            Loginwindow->setObjectName(QString::fromUtf8("Loginwindow"));
        Loginwindow->resize(322, 266);
        Loginwindow->setStyleSheet(QString::fromUtf8("background-image: url(:/Icon_login.png);"));
        usernameLine = new QLineEdit(Loginwindow);
        usernameLine->setObjectName(QString::fromUtf8("usernameLine"));
        usernameLine->setGeometry(QRect(90, 110, 211, 31));
        usernameLine->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background:transparent\n"
""));
        passwordLine = new QLineEdit(Loginwindow);
        passwordLine->setObjectName(QString::fromUtf8("passwordLine"));
        passwordLine->setGeometry(QRect(90, 150, 211, 31));
        passwordLine->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background:transparent"));
        widget = new QWidget(Loginwindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 110, 71, 71));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/Icon_head.png);"));
        loginBtt = new QPushButton(Loginwindow);
        loginBtt->setObjectName(QString::fromUtf8("loginBtt"));
        loginBtt->setGeometry(QRect(91, 210, 151, 31));
        loginBtt->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";\n"
""));
        widget_2 = new QWidget(Loginwindow);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 321, 111));
        widget_2->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(Loginwindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(274, 184, 27, 27));
        pushButton->setStyleSheet(QString::fromUtf8("background-image: url(:/Icon_setting.png);"));

        retranslateUi(Loginwindow);

        QMetaObject::connectSlotsByName(Loginwindow);
    } // setupUi

    void retranslateUi(QDialog *Loginwindow)
    {
        Loginwindow->setWindowTitle(QApplication::translate("Loginwindow", "Dialog", 0, QApplication::UnicodeUTF8));
        usernameLine->setText(QString());
        usernameLine->setPlaceholderText(QApplication::translate("Loginwindow", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
        passwordLine->setText(QString());
        passwordLine->setPlaceholderText(QApplication::translate("Loginwindow", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        loginBtt->setText(QApplication::translate("Loginwindow", "\347\231\273       \351\231\206", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Loginwindow: public Ui_Loginwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
