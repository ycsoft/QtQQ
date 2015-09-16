/********************************************************************************
** Form generated from reading UI file 'setstate.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSTATE_H
#define UI_SETSTATE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_setstate
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QLabel *label;
    QSplitter *splitter;
    QPushButton *bt_closecurrent;
    QPushButton *bt_closeall;

    void setupUi(QDialog *setstate)
    {
        if (setstate->objectName().isEmpty())
            setstate->setObjectName(QString::fromUtf8("setstate"));
        setstate->resize(238, 58);
        gridLayout = new QGridLayout(setstate);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_2 = new QSplitter(setstate);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        label = new QLabel(splitter_2);
        label->setObjectName(QString::fromUtf8("label"));
        splitter_2->addWidget(label);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        bt_closecurrent = new QPushButton(splitter);
        bt_closecurrent->setObjectName(QString::fromUtf8("bt_closecurrent"));
        splitter->addWidget(bt_closecurrent);
        bt_closeall = new QPushButton(splitter);
        bt_closeall->setObjectName(QString::fromUtf8("bt_closeall"));
        splitter->addWidget(bt_closeall);
        splitter_2->addWidget(splitter);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);


        retranslateUi(setstate);

        QMetaObject::connectSlotsByName(setstate);
    } // setupUi

    void retranslateUi(QDialog *setstate)
    {
        setstate->setWindowTitle(QApplication::translate("setstate", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("setstate", "\345\205\263\351\227\255\346\211\200\346\234\211\344\274\232\350\257\235\347\252\227\345\217\243\357\274\214\350\277\230\346\230\257\344\273\205\345\205\263\351\227\255\345\275\223\345\211\215\357\274\237", 0, QApplication::UnicodeUTF8));
        bt_closecurrent->setText(QApplication::translate("setstate", "\345\205\263\351\227\255\345\275\223\345\211\215", 0, QApplication::UnicodeUTF8));
        bt_closeall->setText(QApplication::translate("setstate", "\345\205\263\351\227\255\346\211\200\346\234\211", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class setstate: public Ui_setstate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSTATE_H
