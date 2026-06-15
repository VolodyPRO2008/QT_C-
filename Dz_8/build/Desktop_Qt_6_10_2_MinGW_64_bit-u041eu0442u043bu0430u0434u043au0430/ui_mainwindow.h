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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionPrint;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCut;
    QAction *actionDelete;
    QAction *actionInsertDate;
    QAction *actionFont;
    QAction *actionAlign;
    QAction *actionAlignLeft;
    QAction *actionAlignCenter;
    QAction *actionAlignRight;
    QAction *actionFind;
    QAction *actionAbout;
    QAction *actionGoToLine;
    QAction *action_21;
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_6;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName("actionSaveAs");
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName("actionPrint");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
        actionInsertDate = new QAction(MainWindow);
        actionInsertDate->setObjectName("actionInsertDate");
        actionFont = new QAction(MainWindow);
        actionFont->setObjectName("actionFont");
        actionAlign = new QAction(MainWindow);
        actionAlign->setObjectName("actionAlign");
        actionAlignLeft = new QAction(MainWindow);
        actionAlignLeft->setObjectName("actionAlignLeft");
        actionAlignCenter = new QAction(MainWindow);
        actionAlignCenter->setObjectName("actionAlignCenter");
        actionAlignRight = new QAction(MainWindow);
        actionAlignRight->setObjectName("actionAlignRight");
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName("actionFind");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionGoToLine = new QAction(MainWindow);
        actionGoToLine->setObjectName("actionGoToLine");
        action_21 = new QAction(MainWindow);
        action_21->setObjectName("action_21");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 0, 801, 571));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName("menu_4");
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName("menu_5");
        menu_6 = new QMenu(menubar);
        menu_6->setObjectName("menu_6");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menubar->addAction(menu_6->menuAction());
        menu->addAction(actionNew);
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionSaveAs);
        menu->addAction(actionPrint);
        menu->addAction(actionExit);
        menu_2->addAction(actionUndo);
        menu_2->addAction(actionCopy);
        menu_2->addAction(actionPaste);
        menu_2->addAction(actionCut);
        menu_2->addAction(actionDelete);
        menu_2->addAction(actionInsertDate);
        menu_3->addAction(actionFont);
        menu_3->addAction(actionAlign);
        menu_4->addAction(actionAlignLeft);
        menu_4->addAction(actionAlignCenter);
        menu_4->addAction(actionAlignRight);
        menu_5->addAction(actionFind);
        menu_5->addAction(actionAbout);
        menu_5->addAction(actionGoToLine);
        menu_6->addAction(action_21);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        actionSaveAs->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\207\320\260\321\202\321\214", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\200\320\265\320\267\320\260\321\202\321\214", nullptr));
        actionDelete->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        actionInsertDate->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        actionFont->setText(QCoreApplication::translate("MainWindow", "\320\250\321\200\320\270\321\204\321\202", nullptr));
        actionAlign->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\200\320\260\320\262\320\275\320\270\320\262\320\260\320\275\320\270\320\265 ", nullptr));
        actionAlignLeft->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\265\320\262\320\260", nullptr));
        actionAlignCenter->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276 \321\206\320\265\320\275\321\202\321\200\321\203\n"
"\n"
"", nullptr));
        actionAlignRight->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\260", nullptr));
        actionFind->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        actionGoToLine->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270 \320\272 \321\201\321\202\321\200\320\276\320\272\320\265", nullptr));
        action_21->setText(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\320\272\320\260", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\200\320\260\320\262\320\275\320\270\320\262\320\260\320\275\320\270\320\265", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        menu_6->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
