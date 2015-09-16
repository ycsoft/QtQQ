/********************************************************************************
** Form generated from reading UI file 'filereceivedlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILERECEIVEDLG_H
#define UI_FILERECEIVEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FileReceiveDlg
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_FileName;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditSender;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEditSize;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *bt_selectpath;
    QPushButton *pushButtonAccept;
    QPushButton *pushButtonReject;

    void setupUi(QDialog *FileReceiveDlg)
    {
        if (FileReceiveDlg->objectName().isEmpty())
            FileReceiveDlg->setObjectName(QString::fromUtf8("FileReceiveDlg"));
        FileReceiveDlg->resize(306, 235);
        FileReceiveDlg->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        gridLayout = new QGridLayout(FileReceiveDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(FileReceiveDlg);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setStyleSheet(QString::fromUtf8("background:transparent"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_FileName = new QLineEdit(frame_2);
        lineEdit_FileName->setObjectName(QString::fromUtf8("lineEdit_FileName"));
        lineEdit_FileName->setEnabled(false);
        lineEdit_FileName->setFrame(false);
        lineEdit_FileName->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lineEdit_FileName);


        verticalLayout->addWidget(frame_2);

        frame = new QFrame(FileReceiveDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background:transparent"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditSender = new QLineEdit(frame);
        lineEditSender->setObjectName(QString::fromUtf8("lineEditSender"));
        lineEditSender->setEnabled(false);
        lineEditSender->setFrame(false);
        lineEditSender->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEditSender);


        verticalLayout->addWidget(frame);

        frame_3 = new QFrame(FileReceiveDlg);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setStyleSheet(QString::fromUtf8("background:transparent"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEditSize = new QLineEdit(frame_3);
        lineEditSize->setObjectName(QString::fromUtf8("lineEditSize"));
        lineEditSize->setEnabled(false);
        lineEditSize->setFrame(false);
        lineEditSize->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lineEditSize);


        verticalLayout->addWidget(frame_3);

        progressBar = new QProgressBar(FileReceiveDlg);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        bt_selectpath = new QPushButton(FileReceiveDlg);
        bt_selectpath->setObjectName(QString::fromUtf8("bt_selectpath"));

        horizontalLayout_4->addWidget(bt_selectpath);

        pushButtonAccept = new QPushButton(FileReceiveDlg);
        pushButtonAccept->setObjectName(QString::fromUtf8("pushButtonAccept"));

        horizontalLayout_4->addWidget(pushButtonAccept);

        pushButtonReject = new QPushButton(FileReceiveDlg);
        pushButtonReject->setObjectName(QString::fromUtf8("pushButtonReject"));

        horizontalLayout_4->addWidget(pushButtonReject);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(FileReceiveDlg);

        QMetaObject::connectSlotsByName(FileReceiveDlg);
    } // setupUi

    void retranslateUi(QDialog *FileReceiveDlg)
    {
        FileReceiveDlg->setWindowTitle(QApplication::translate("FileReceiveDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FileReceiveDlg", "\346\226\207\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FileReceiveDlg", "\345\217\221\351\200\201\350\200\205", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FileReceiveDlg", "\345\244\247  \345\260\217", 0, QApplication::UnicodeUTF8));
        bt_selectpath->setText(QApplication::translate("FileReceiveDlg", "\351\200\211\346\213\251\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        pushButtonAccept->setText(QApplication::translate("FileReceiveDlg", "\346\216\245\346\224\266", 0, QApplication::UnicodeUTF8));
        pushButtonReject->setText(QApplication::translate("FileReceiveDlg", "\346\213\222\346\224\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FileReceiveDlg: public Ui_FileReceiveDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILERECEIVEDLG_H
