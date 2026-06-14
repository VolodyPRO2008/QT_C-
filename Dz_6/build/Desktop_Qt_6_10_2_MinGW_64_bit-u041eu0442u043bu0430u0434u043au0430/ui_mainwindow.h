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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelSource;
    QLabel *labelEven;
    QLabel *labelOdd;
    QLabel *labelFilePath;
    QTextEdit *textEditSource;
    QTextEdit *textEditEven;
    QTextEdit *textEditOdd;
    QLineEdit *lineEditFilePath;
    QPushButton *buttonSelectFile;
    QPushButton *buttonProcess;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        labelSource = new QLabel(centralwidget);
        labelSource->setObjectName("labelSource");
        labelSource->setGeometry(QRect(130, 350, 121, 16));
        labelEven = new QLabel(centralwidget);
        labelEven->setObjectName("labelEven");
        labelEven->setGeometry(QRect(50, 130, 161, 20));
        labelOdd = new QLabel(centralwidget);
        labelOdd->setObjectName("labelOdd");
        labelOdd->setGeometry(QRect(510, 130, 161, 20));
        labelFilePath = new QLabel(centralwidget);
        labelFilePath->setObjectName("labelFilePath");
        labelFilePath->setGeometry(QRect(240, 200, 81, 16));
        textEditSource = new QTextEdit(centralwidget);
        textEditSource->setObjectName("textEditSource");
        textEditSource->setGeometry(QRect(270, 310, 131, 91));
        textEditEven = new QTextEdit(centralwidget);
        textEditEven->setObjectName("textEditEven");
        textEditEven->setGeometry(QRect(60, 170, 131, 91));
        textEditOdd = new QTextEdit(centralwidget);
        textEditOdd->setObjectName("textEditOdd");
        textEditOdd->setGeometry(QRect(520, 170, 131, 91));
        lineEditFilePath = new QLineEdit(centralwidget);
        lineEditFilePath->setObjectName("lineEditFilePath");
        lineEditFilePath->setGeometry(QRect(340, 200, 121, 22));
        buttonSelectFile = new QPushButton(centralwidget);
        buttonSelectFile->setObjectName("buttonSelectFile");
        buttonSelectFile->setGeometry(QRect(250, 250, 161, 24));
        buttonProcess = new QPushButton(centralwidget);
        buttonProcess->setObjectName("buttonProcess");
        buttonProcess->setGeometry(QRect(440, 340, 221, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
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
        labelSource->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\271 \321\204\320\260\320\271\320\273 f:", nullptr));
        labelEven->setText(QCoreApplication::translate("MainWindow", "\320\247\321\221\321\202\320\275\321\213\320\265 \321\207\320\270\321\201\320\273\320\260 (\321\204\320\260\320\271\320\273 g):", nullptr));
        labelOdd->setText(QCoreApplication::translate("MainWindow", "\320\235\320\265\321\207\321\221\321\202\320\275\321\213\320\265 \321\207\320\270\321\201\320\273\320\260 (\321\204\320\260\320\271\320\273 h):", nullptr));
        labelFilePath->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203:", nullptr));
        buttonSelectFile->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273 f", nullptr));
        buttonProcess->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\264\320\265\320\273\320\270\321\202\321\214 \320\275\320\260 \321\207\321\221\321\202\320\275\321\213\320\265 \320\270 \320\275\320\265\321\207\321\221\321\202\320\275\321\213\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
