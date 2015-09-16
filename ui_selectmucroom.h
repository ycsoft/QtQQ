/********************************************************************************
** Form generated from reading UI file 'selectmucroom.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMUCROOM_H
#define UI_SELECTMUCROOM_H

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

class Ui_SelectMucroom
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *text_roomname;
    QPushButton *Btt_confirm;

    void setupUi(QDialog *SelectMucroom)
    {
        if (SelectMucroom->objectName().isEmpty())
            SelectMucroom->setObjectName(QString::fromUtf8("SelectMucroom"));
        SelectMucroom->resize(223, 81);
        SelectMucroom->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        verticalLayout_2 = new QVBoxLayout(SelectMucroom);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(SelectMucroom);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 75 14pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";\n"
"background:transparent;"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        text_roomname = new QLineEdit(SelectMucroom);
        text_roomname->setObjectName(QString::fromUtf8("text_roomname"));
        text_roomname->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(text_roomname);

        Btt_confirm = new QPushButton(SelectMucroom);
        Btt_confirm->setObjectName(QString::fromUtf8("Btt_confirm"));
        Btt_confirm->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";"));

        horizontalLayout->addWidget(Btt_confirm);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SelectMucroom);

        QMetaObject::connectSlotsByName(SelectMucroom);
    } // setupUi

    void retranslateUi(QDialog *SelectMucroom)
    {
        SelectMucroom->setWindowTitle(QApplication::translate("SelectMucroom", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SelectMucroom", "       \350\257\267\350\276\223\345\205\245\350\201\212\345\244\251\345\256\244JID\357\274\232", 0, QApplication::UnicodeUTF8));
        Btt_confirm->setText(QApplication::translate("SelectMucroom", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectMucroom: public Ui_SelectMucroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMUCROOM_H
