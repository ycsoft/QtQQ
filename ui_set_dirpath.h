/********************************************************************************
** Form generated from reading UI file 'set_dirpath.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_DIRPATH_H
#define UI_SET_DIRPATH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Set_dirpath
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *Bt_select;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Bt_ok;
    QPushButton *Bt_cancel;

    void setupUi(QDialog *Set_dirpath)
    {
        if (Set_dirpath->objectName().isEmpty())
            Set_dirpath->setObjectName(QString::fromUtf8("Set_dirpath"));
        Set_dirpath->resize(332, 72);
        gridLayout = new QGridLayout(Set_dirpath);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_2 = new QSplitter(Set_dirpath);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        Bt_select = new QPushButton(layoutWidget);
        Bt_select->setObjectName(QString::fromUtf8("Bt_select"));

        horizontalLayout->addWidget(Bt_select);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox = new QComboBox(layoutWidget1);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEditable(true);

        horizontalLayout_2->addWidget(comboBox);

        splitter->addWidget(layoutWidget1);
        splitter_2->addWidget(splitter);
        layoutWidget2 = new QWidget(splitter_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Bt_ok = new QPushButton(layoutWidget2);
        Bt_ok->setObjectName(QString::fromUtf8("Bt_ok"));

        verticalLayout_2->addWidget(Bt_ok);

        Bt_cancel = new QPushButton(layoutWidget2);
        Bt_cancel->setObjectName(QString::fromUtf8("Bt_cancel"));

        verticalLayout_2->addWidget(Bt_cancel);

        splitter_2->addWidget(layoutWidget2);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);


        retranslateUi(Set_dirpath);

        QMetaObject::connectSlotsByName(Set_dirpath);
    } // setupUi

    void retranslateUi(QDialog *Set_dirpath)
    {
        Set_dirpath->setWindowTitle(QApplication::translate("Set_dirpath", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Set_dirpath", "\346\234\254\345\234\260\350\267\257\345\276\204  ", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("Set_dirpath", "D:/01/", 0, QApplication::UnicodeUTF8));
        Bt_select->setText(QString());
        label_2->setText(QApplication::translate("Set_dirpath", "\346\234\215\345\212\241\345\231\250URL", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Set_dirpath", "git://192.168.1.114/test", 0, QApplication::UnicodeUTF8)
        );
        Bt_ok->setText(QApplication::translate("Set_dirpath", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        Bt_cancel->setText(QApplication::translate("Set_dirpath", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Set_dirpath: public Ui_Set_dirpath {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_DIRPATH_H
