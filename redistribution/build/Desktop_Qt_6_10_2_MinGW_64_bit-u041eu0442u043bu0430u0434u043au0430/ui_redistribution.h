/********************************************************************************
** Form generated from reading UI file 'redistribution.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REDISTRIBUTION_H
#define UI_REDISTRIBUTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_redistribution
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *redistribution)
    {
        if (redistribution->objectName().isEmpty())
            redistribution->setObjectName("redistribution");
        redistribution->resize(800, 600);
        redistribution->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 222, 222)"));
        centralwidget = new QWidget(redistribution);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(80, 130, 251, 24));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 30, 131, 16));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(150, 200, 131, 16));
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(120, 370, 75, 24));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(80, 80, 266, 24));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit);

        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit_2);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(100, 260, 118, 80));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_3 = new QLineEdit(widget1);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(lineEdit_3);

        lineEdit_4 = new QLineEdit(widget1);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(widget1);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(lineEdit_5);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(80, 260, 16, 81));
        verticalLayout_2 = new QVBoxLayout(widget2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(widget2);
        label_7->setObjectName("label_7");

        verticalLayout_2->addWidget(label_7);

        label_6 = new QLabel(widget2);
        label_6->setObjectName("label_6");

        verticalLayout_2->addWidget(label_6);

        label_5 = new QLabel(widget2);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        redistribution->setCentralWidget(centralwidget);
        menubar = new QMenuBar(redistribution);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        redistribution->setMenuBar(menubar);
        statusbar = new QStatusBar(redistribution);
        statusbar->setObjectName("statusbar");
        redistribution->setStatusBar(statusbar);

        retranslateUi(redistribution);

        QMetaObject::connectSlotsByName(redistribution);
    } // setupUi

    void retranslateUi(QMainWindow *redistribution)
    {
        redistribution->setWindowTitle(QCoreApplication::translate("redistribution", "redistribution", nullptr));
        pushButton->setText(QCoreApplication::translate("redistribution", "\320\235\320\260\320\266\320\260\321\202\321\214 \320\265\321\201\320\273\320\270 X, \320\261\320\276\320\273\321\214\321\210\320\265 \321\207\320\265\320\274 Y", nullptr));
        label_3->setText(QCoreApplication::translate("redistribution", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 1", nullptr));
        label_4->setText(QCoreApplication::translate("redistribution", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 2", nullptr));
        pushButton_2->setText(QCoreApplication::translate("redistribution", "PushButton", nullptr));
        label_2->setText(QCoreApplication::translate("redistribution", "X", nullptr));
        label->setText(QCoreApplication::translate("redistribution", "Y", nullptr));
        lineEdit_2->setText(QString());
        label_7->setText(QCoreApplication::translate("redistribution", "Z", nullptr));
        label_6->setText(QCoreApplication::translate("redistribution", "Y", nullptr));
        label_5->setText(QCoreApplication::translate("redistribution", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class redistribution: public Ui_redistribution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REDISTRIBUTION_H
