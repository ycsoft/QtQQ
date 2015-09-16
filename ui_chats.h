/********************************************************************************
** Form generated from reading UI file 'chats.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATS_H
#define UI_CHATS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_chats
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEdit;

    void setupUi(QDialog *chats)
    {
        if (chats->objectName().isEmpty())
            chats->setObjectName(QString::fromUtf8("chats"));
        chats->resize(401, 348);
        gridLayout = new QGridLayout(chats);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEdit = new QTextEdit(chats);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(true);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);


        retranslateUi(chats);

        QMetaObject::connectSlotsByName(chats);
    } // setupUi

    void retranslateUi(QDialog *chats)
    {
        chats->setWindowTitle(QApplication::translate("chats", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class chats: public Ui_chats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATS_H
