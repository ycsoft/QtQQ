/********************************************************************************
** Form generated from reading UI file 'commitdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMITDLG_H
#define UI_COMMITDLG_H

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

class Ui_commitdlg
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *edit_commitor;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *edit_msg;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *bt_confirm;
    QPushButton *bt_cancle;

    void setupUi(QDialog *commitdlg)
    {
        if (commitdlg->objectName().isEmpty())
            commitdlg->setObjectName(QString::fromUtf8("commitdlg"));
        commitdlg->resize(359, 119);
        gridLayout = new QGridLayout(commitdlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(commitdlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        edit_commitor = new QLineEdit(commitdlg);
        edit_commitor->setObjectName(QString::fromUtf8("edit_commitor"));

        horizontalLayout->addWidget(edit_commitor);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(commitdlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        edit_msg = new QLineEdit(commitdlg);
        edit_msg->setObjectName(QString::fromUtf8("edit_msg"));

        horizontalLayout_2->addWidget(edit_msg);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        bt_confirm = new QPushButton(commitdlg);
        bt_confirm->setObjectName(QString::fromUtf8("bt_confirm"));

        horizontalLayout_3->addWidget(bt_confirm);

        bt_cancle = new QPushButton(commitdlg);
        bt_cancle->setObjectName(QString::fromUtf8("bt_cancle"));

        horizontalLayout_3->addWidget(bt_cancle);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(commitdlg);

        QMetaObject::connectSlotsByName(commitdlg);
    } // setupUi

    void retranslateUi(QDialog *commitdlg)
    {
        commitdlg->setWindowTitle(QApplication::translate("commitdlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("commitdlg", "\346\217\220\344\272\244\350\200\205  ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("commitdlg", "\346\217\220\344\272\244\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        bt_confirm->setText(QApplication::translate("commitdlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        bt_cancle->setText(QApplication::translate("commitdlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class commitdlg: public Ui_commitdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMITDLG_H
