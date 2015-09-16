/********************************************************************************
** Form generated from reading UI file 'addfiles.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFILES_H
#define UI_ADDFILES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addfiles
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *line_path;
    QPushButton *bt_select;
    QPushButton *bt_cofirm;

    void setupUi(QDialog *addfiles)
    {
        if (addfiles->objectName().isEmpty())
            addfiles->setObjectName(QString::fromUtf8("addfiles"));
        addfiles->resize(254, 81);
        gridLayout_2 = new QGridLayout(addfiles);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        line_path = new QLineEdit(addfiles);
        line_path->setObjectName(QString::fromUtf8("line_path"));

        horizontalLayout->addWidget(line_path);

        bt_select = new QPushButton(addfiles);
        bt_select->setObjectName(QString::fromUtf8("bt_select"));

        horizontalLayout->addWidget(bt_select);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        bt_cofirm = new QPushButton(addfiles);
        bt_cofirm->setObjectName(QString::fromUtf8("bt_cofirm"));

        gridLayout->addWidget(bt_cofirm, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(addfiles);

        QMetaObject::connectSlotsByName(addfiles);
    } // setupUi

    void retranslateUi(QDialog *addfiles)
    {
        addfiles->setWindowTitle(QApplication::translate("addfiles", "Dialog", 0, QApplication::UnicodeUTF8));
        bt_select->setText(QApplication::translate("addfiles", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", 0, QApplication::UnicodeUTF8));
        bt_cofirm->setText(QApplication::translate("addfiles", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class addfiles: public Ui_addfiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFILES_H
