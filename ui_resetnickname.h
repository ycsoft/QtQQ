/********************************************************************************
** Form generated from reading UI file 'resetnickname.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETNICKNAME_H
#define UI_RESETNICKNAME_H

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

class Ui_ResetNickname
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *text_newNickname;
    QPushButton *Btt_confirm;

    void setupUi(QDialog *ResetNickname)
    {
        if (ResetNickname->objectName().isEmpty())
            ResetNickname->setObjectName(QString::fromUtf8("ResetNickname"));
        ResetNickname->resize(220, 80);
        ResetNickname->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        verticalLayout_2 = new QVBoxLayout(ResetNickname);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(ResetNickname);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 75 14pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";\n"
"background:transparent;"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        text_newNickname = new QLineEdit(ResetNickname);
        text_newNickname->setObjectName(QString::fromUtf8("text_newNickname"));
        text_newNickname->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(text_newNickname);

        Btt_confirm = new QPushButton(ResetNickname);
        Btt_confirm->setObjectName(QString::fromUtf8("Btt_confirm"));
        Btt_confirm->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";"));

        horizontalLayout->addWidget(Btt_confirm);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ResetNickname);

        QMetaObject::connectSlotsByName(ResetNickname);
    } // setupUi

    void retranslateUi(QDialog *ResetNickname)
    {
        ResetNickname->setWindowTitle(QApplication::translate("ResetNickname", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ResetNickname", "\350\257\267\350\276\223\345\205\245\346\226\260\346\230\265\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        Btt_confirm->setText(QApplication::translate("ResetNickname", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ResetNickname: public Ui_ResetNickname {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETNICKNAME_H
