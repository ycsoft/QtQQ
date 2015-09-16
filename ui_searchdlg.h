/********************************************************************************
** Form generated from reading UI file 'searchdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDLG_H
#define UI_SEARCHDLG_H

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
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SearchDlg
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_id;
    QRadioButton *radioButton_name;
    QPushButton *pushButton_find;
    QFrame *line;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QTreeView *treeView;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_AddContact;

    void setupUi(QDialog *SearchDlg)
    {
        if (SearchDlg->objectName().isEmpty())
            SearchDlg->setObjectName(QString::fromUtf8("SearchDlg"));
        SearchDlg->resize(718, 354);
        SearchDlg->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(191, 255, 186, 255), stop:1 rgba(255, 255, 255, 255));"));
        gridLayout = new QGridLayout(SearchDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(SearchDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(200, 0));
        frame->setMaximumSize(QSize(200, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(174, 91));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setFrameShape(QFrame::StyledPanel);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(lineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setStyleSheet(QString::fromUtf8(""));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        radioButton_id = new QRadioButton(frame_4);
        radioButton_id->setObjectName(QString::fromUtf8("radioButton_id"));
        radioButton_id->setEnabled(true);
        radioButton_id->setChecked(true);

        verticalLayout_3->addWidget(radioButton_id);

        radioButton_name = new QRadioButton(frame_4);
        radioButton_name->setObjectName(QString::fromUtf8("radioButton_name"));

        verticalLayout_3->addWidget(radioButton_name);


        horizontalLayout_3->addLayout(verticalLayout_3);

        pushButton_find = new QPushButton(frame_4);
        pushButton_find->setObjectName(QString::fromUtf8("pushButton_find"));
        pushButton_find->setMinimumSize(QSize(75, 23));
        pushButton_find->setMaximumSize(QSize(75, 23));
        pushButton_find->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(pushButton_find);


        verticalLayout->addWidget(frame_4);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        line = new QFrame(SearchDlg);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 1, 1, 1);

        frame_2 = new QFrame(SearchDlg);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        treeView = new QTreeView(frame_2);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_2->addWidget(treeView);

        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setStyleSheet(QString::fromUtf8(""));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(363, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_AddContact = new QPushButton(frame_3);
        pushButton_AddContact->setObjectName(QString::fromUtf8("pushButton_AddContact"));
        pushButton_AddContact->setMinimumSize(QSize(75, 23));
        pushButton_AddContact->setMaximumSize(QSize(75, 23));
        pushButton_AddContact->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButton_AddContact);


        verticalLayout_2->addWidget(frame_3);


        gridLayout->addWidget(frame_2, 0, 2, 1, 1);


        retranslateUi(SearchDlg);

        QMetaObject::connectSlotsByName(SearchDlg);
    } // setupUi

    void retranslateUi(QDialog *SearchDlg)
    {
        SearchDlg->setWindowTitle(QApplication::translate("SearchDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SearchDlg", "<html><head/><body><p>\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\350\272\253\344\273\275\350\257\201\345\217\267\346\210\226\345\247\223\345\220\215</p><p>\350\277\233\350\241\214\346\237\245\346\211\276\357\274\214\350\272\253\344\273\275\350\257\201\346\237\245\346\211\276\346\226\271\345\274\217</p><p>\351\234\200\350\276\223\345\205\245\345\256\214\346\225\264\344\277\241\346\201\257\343\200\202\345\247\223\345\220\215\346\237\245\346\211\276</p><p>\346\226\271\345\274\217\346\224\257<span style=\" font-size:9pt;\">\346\214\201\346\250\241\347\263\212\346\237\245\350\257\242\343\200\202\344\271\237\345\217\257\350\276\223\345\205\245</span></p><p><span style=\" font-size:9pt;\">(*),\346\237\245\350\257\242\346\211\200\346\234\211\346\263\250\345\206\214\347\224\250\346\210\267\343\200\202<br/></span></p></body></html>", 0, QApplication::UnicodeUTF8));
        radioButton_id->setText(QApplication::translate("SearchDlg", "\350\272\253\344\273\275\350\257\201", 0, QApplication::UnicodeUTF8));
        radioButton_name->setText(QApplication::translate("SearchDlg", "\345\247\223\345\220\215", 0, QApplication::UnicodeUTF8));
        pushButton_find->setText(QApplication::translate("SearchDlg", "\346\237\245\346\211\276", 0, QApplication::UnicodeUTF8));
        pushButton_AddContact->setText(QApplication::translate("SearchDlg", "\346\267\273\345\212\240\345\245\275\345\217\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SearchDlg: public Ui_SearchDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDLG_H
