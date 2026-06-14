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
    QPushButton *ButtonPart1;
    QPushButton *ButtonPart2;
    QTextEdit *textEditTask2;
    QLineEdit *lineEditK;
    QTextEdit *textEditTask1;
    QPushButton *buttonClear;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        ButtonPart1 = new QPushButton(centralwidget);
        ButtonPart1->setObjectName("ButtonPart1");
        ButtonPart1->setGeometry(QRect(20, 230, 231, 24));
        ButtonPart2 = new QPushButton(centralwidget);
        ButtonPart2->setObjectName("ButtonPart2");
        ButtonPart2->setGeometry(QRect(450, 230, 211, 24));
        textEditTask2 = new QTextEdit(centralwidget);
        textEditTask2->setObjectName("textEditTask2");
        textEditTask2->setGeometry(QRect(460, 260, 171, 111));
        lineEditK = new QLineEdit(centralwidget);
        lineEditK->setObjectName("lineEditK");
        lineEditK->setGeometry(QRect(500, 400, 131, 41));
        textEditTask1 = new QTextEdit(centralwidget);
        textEditTask1->setObjectName("textEditTask1");
        textEditTask1->setGeometry(QRect(40, 260, 191, 121));
        buttonClear = new QPushButton(centralwidget);
        buttonClear->setObjectName("buttonClear");
        buttonClear->setGeometry(QRect(300, 300, 75, 24));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 110, 411, 91));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 110, 281, 91));
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
        ButtonPart1->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\266\320\274\320\270\321\202\320\265 \320\264\320\273\321\217 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217 1 \320\267\320\260\320\264\320\260\320\275\320\270\320\265", nullptr));
        ButtonPart2->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\266\320\274\320\270\321\202\320\265 \320\264\320\273\321\217 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217 2 \320\267\320\260\320\264\320\260\320\275\320\270\320\265", nullptr));
        lineEditK->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\207\320\270\321\201\320\273\320\276 : ", nullptr));
        buttonClear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200 \321\201\320\276\320\267\320\264\320\260\321\221\321\202 \321\201\320\262\321\217\320\267\320\275\321\213\320\271 \321\201\320\277\320\270\321\201\320\276\320\272 \320\270\320\267 15 \321\201\320\273\321\203\321\207\320\260\320\271\320\275\321\213\321\205 \321\207\320\270\321\201\320\265\320\273 (\320\276\321\202 1 \320\264\320\276 99)\n"
"\n"
"\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214 \320\262\320\262\320\276\320\264\320\270\321\202 \321\207\320\270\321\201\320\273\320\276 k (\320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200, 2)\n"
"\n"
"\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260 \321\203\320\264\320\260\320\273\321\217\320\265\321\202 \320\262\321\201\320\265 \321\207\320\270\321\201\320\273\320\260, \321\203 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320"
                        "\276 \321\206\320\270\321\204\321\200 \320\261\320\276\320\273\321\214\321\210\320\265 k", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200 \321\201\320\260\320\274 \321\201\320\276\320\267\320\264\320\260\321\221\321\202 2 \321\201\320\277\320\270\321\201\320\272\320\260 \321\201\320\273\321\203\321\207\320\260\320\271\320\275\321\213\321\205 \321\207\320\270\321\201\320\265\320\273 (\320\277\320\276 10 \321\207\320\270\321\201\320\265\320\273 \320\262 \320\272\320\260\320\266\320\264\320\276\320\274)\n"
"\n"
"\320\222\320\276 \320\262\321\202\320\276\321\200\320\276\320\274 \321\201\320\277\320\270\321\201\320\272\320\265 \320\275\320\260\321\205\320\276\320\264\320\270\321\202 \321\201\320\260\320\274\320\276\320\265 \320\274\320\260\320\273\320\265\320\275\321\214\320\272\320\276\320\265 \321\207\320\270\321\201\320\273\320\276\n"
"\n"
"\320\222 \320\277\320\265\321\200\320\262\320\276\320\274 \321\201\320\277\320\270\321\201\320\272\320\265 \320\267\320\260\320\274\320\265\320\275\321\217\320\265\321\202 \320\262\321\201\320\265 \320\277\320\276\320\273\320\276\320\266\320"
                        "\270\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \321\207\320\270\321\201\320\273\320\260 (\320\261\320\276\320\273\321\214\321\210\320\265 \320\275\321\203\320\273\321\217) \320\275\320\260 \321\215\321\202\320\276 \320\274\320\260\320\273\320\265\320\275\321\214\320\272\320\276\320\265 \321\207\320\270\321\201\320\273\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
