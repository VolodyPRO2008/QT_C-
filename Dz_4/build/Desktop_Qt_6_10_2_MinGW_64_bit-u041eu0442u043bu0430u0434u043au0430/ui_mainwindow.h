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
#include <QtWidgets/QGroupBox>
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
    QGroupBox *groupBoxStack;
    QPushButton *buttonStack;
    QTextEdit *textEditStack;
    QGroupBox *groupBoxQueue;
    QPushButton *buttonQueue;
    QTextEdit *textEditQueue;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBoxStack = new QGroupBox(centralwidget);
        groupBoxStack->setObjectName("groupBoxStack");
        groupBoxStack->setGeometry(QRect(90, 170, 291, 181));
        buttonStack = new QPushButton(groupBoxStack);
        buttonStack->setObjectName("buttonStack");
        buttonStack->setGeometry(QRect(10, 50, 191, 24));
        textEditStack = new QTextEdit(groupBoxStack);
        textEditStack->setObjectName("textEditStack");
        textEditStack->setGeometry(QRect(10, 100, 251, 81));
        groupBoxQueue = new QGroupBox(centralwidget);
        groupBoxQueue->setObjectName("groupBoxQueue");
        groupBoxQueue->setGeometry(QRect(420, 180, 301, 171));
        buttonQueue = new QPushButton(groupBoxQueue);
        buttonQueue->setObjectName("buttonQueue");
        buttonQueue->setGeometry(QRect(0, 40, 191, 24));
        textEditQueue = new QTextEdit(groupBoxQueue);
        textEditQueue->setObjectName("textEditQueue");
        textEditQueue->setGeometry(QRect(0, 80, 241, 81));
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
        groupBoxStack->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\242\320\225\320\232 (\320\227\320\260\320\264\320\260\320\275\320\270\320\265 1)", nullptr));
        buttonStack->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\320\275\321\217\321\202\321\214 \320\274\320\265\321\201\321\202\320\260\320\274\320\270 min \320\270 max", nullptr));
        groupBoxQueue->setTitle(QCoreApplication::translate("MainWindow", "\320\236\320\247\320\225\320\240\320\225\320\224\320\254 (\320\227\320\260\320\264\320\260\320\275\320\270\320\265 2)", nullptr));
        buttonQueue->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214 \321\207\320\265\321\202\320\275\321\213\320\265 \320\275\320\260 \321\201\321\200\320\265\320\264\320\275\320\265\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
