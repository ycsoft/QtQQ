/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>


#define LOCAL(x) QString::fromLocal8Bit(x)

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:

    QTabWidget      *tabWidget;
    QWidget         *contents;
    QStackedWidget  *stack;
    QHBoxLayout     *tablay;
    QWidget         *tw;

    void setupUi(QDialog *MainDialog)
    {

        contents = new QWidget();



        stack = new QStackedWidget(MainDialog);

        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        //MainDialog->resize(441, 509);

        retranslateUi(MainDialog);
        QVBoxLayout     *lay = new QVBoxLayout(contents);

        lay->setContentsMargins(0,0,0,0);
        lay->setSpacing(0);

        contents->setLayout(lay);
        /*
        tabWidget = new QTabWidget(contents);
        lay->addWidget(tabWidget);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabPosition(QTabWidget::South);
        */
        lay->addWidget(stack);

        tw = new QWidget(contents);
        tablay = new QHBoxLayout(tw);
        tablay->setSpacing(0);
        tablay->setContentsMargins(0,0,0,0);
        tablay->addStretch();
        lay->addWidget(tw,0,Qt::AlignBottom);

        QHBoxLayout *mainLay = new QHBoxLayout(MainDialog);
        mainLay->setContentsMargins(0,0,0,0);


        mainLay->addWidget(contents);
        MainDialog->setLayout(mainLay);
        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
