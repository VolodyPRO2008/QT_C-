/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btnAdd;
    QPushButton *btnSubtract;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btnMultiply;
    QPushButton *btnDivide;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btnSign;
    QPushButton *btn0;
    QPushButton *btnDecimal;
    QPushButton *btnClear;
    QPushButton *btnEquals;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(553, 359);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btn1 = new QPushButton(centralwidget);
        btn1->setObjectName("btn1");
        btn1->setGeometry(QRect(260, 150, 31, 31));
        btn2 = new QPushButton(centralwidget);
        btn2->setObjectName("btn2");
        btn2->setGeometry(QRect(310, 150, 31, 31));
        btn3 = new QPushButton(centralwidget);
        btn3->setObjectName("btn3");
        btn3->setGeometry(QRect(360, 150, 31, 31));
        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(410, 150, 31, 31));
        btnSubtract = new QPushButton(centralwidget);
        btnSubtract->setObjectName("btnSubtract");
        btnSubtract->setGeometry(QRect(460, 150, 31, 31));
        btn4 = new QPushButton(centralwidget);
        btn4->setObjectName("btn4");
        btn4->setGeometry(QRect(260, 190, 31, 31));
        btn5 = new QPushButton(centralwidget);
        btn5->setObjectName("btn5");
        btn5->setGeometry(QRect(310, 190, 31, 31));
        btn6 = new QPushButton(centralwidget);
        btn6->setObjectName("btn6");
        btn6->setGeometry(QRect(360, 190, 31, 31));
        btnMultiply = new QPushButton(centralwidget);
        btnMultiply->setObjectName("btnMultiply");
        btnMultiply->setGeometry(QRect(410, 190, 31, 31));
        btnDivide = new QPushButton(centralwidget);
        btnDivide->setObjectName("btnDivide");
        btnDivide->setGeometry(QRect(460, 190, 31, 31));
        btn7 = new QPushButton(centralwidget);
        btn7->setObjectName("btn7");
        btn7->setGeometry(QRect(260, 230, 31, 31));
        btn8 = new QPushButton(centralwidget);
        btn8->setObjectName("btn8");
        btn8->setGeometry(QRect(310, 230, 31, 31));
        btn9 = new QPushButton(centralwidget);
        btn9->setObjectName("btn9");
        btn9->setGeometry(QRect(360, 230, 31, 31));
        btnSign = new QPushButton(centralwidget);
        btnSign->setObjectName("btnSign");
        btnSign->setGeometry(QRect(410, 230, 31, 31));
        btn0 = new QPushButton(centralwidget);
        btn0->setObjectName("btn0");
        btn0->setGeometry(QRect(260, 270, 81, 31));
        btnDecimal = new QPushButton(centralwidget);
        btnDecimal->setObjectName("btnDecimal");
        btnDecimal->setGeometry(QRect(360, 270, 31, 31));
        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");
        btnClear->setGeometry(QRect(410, 270, 31, 31));
        btnEquals = new QPushButton(centralwidget);
        btnEquals->setObjectName("btnEquals");
        btnEquals->setGeometry(QRect(460, 230, 31, 71));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(260, 110, 231, 22));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(260, 70, 231, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 553, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btn2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btn3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnSubtract->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btn4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btn5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btn6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btnMultiply->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        btnDivide->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        btn7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btn8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btn9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btnSign->setText(QCoreApplication::translate("MainWindow", "+/-", nullptr));
        btn0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnDecimal->setText(QCoreApplication::translate("MainWindow", ",", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        btnEquals->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
