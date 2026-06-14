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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxArray;
    QVBoxLayout *verticalLayout;
    QLabel *labelArrayDesc;
    QLineEdit *lineEditArray;
    QPushButton *buttonArray;
    QLabel *labelArrayResult;
    QTextEdit *textEditArray;
    QGroupBox *groupBoxMatrix;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelMatrixDesc;
    QTextEdit *textEditMatrix;
    QLabel *labelMatrixInfo;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *buttonMatrix;
    QPushButton *buttonClear;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBoxArray = new QGroupBox(centralwidget);
        groupBoxArray->setObjectName("groupBoxArray");
        verticalLayout = new QVBoxLayout(groupBoxArray);
        verticalLayout->setObjectName("verticalLayout");
        labelArrayDesc = new QLabel(groupBoxArray);
        labelArrayDesc->setObjectName("labelArrayDesc");

        verticalLayout->addWidget(labelArrayDesc);

        lineEditArray = new QLineEdit(groupBoxArray);
        lineEditArray->setObjectName("lineEditArray");

        verticalLayout->addWidget(lineEditArray);

        buttonArray = new QPushButton(groupBoxArray);
        buttonArray->setObjectName("buttonArray");

        verticalLayout->addWidget(buttonArray);

        labelArrayResult = new QLabel(groupBoxArray);
        labelArrayResult->setObjectName("labelArrayResult");

        verticalLayout->addWidget(labelArrayResult);

        textEditArray = new QTextEdit(groupBoxArray);
        textEditArray->setObjectName("textEditArray");

        verticalLayout->addWidget(textEditArray);


        horizontalLayout->addWidget(groupBoxArray);

        groupBoxMatrix = new QGroupBox(centralwidget);
        groupBoxMatrix->setObjectName("groupBoxMatrix");
        verticalLayout_2 = new QVBoxLayout(groupBoxMatrix);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelMatrixDesc = new QLabel(groupBoxMatrix);
        labelMatrixDesc->setObjectName("labelMatrixDesc");

        verticalLayout_2->addWidget(labelMatrixDesc);

        textEditMatrix = new QTextEdit(groupBoxMatrix);
        textEditMatrix->setObjectName("textEditMatrix");

        verticalLayout_2->addWidget(textEditMatrix);

        labelMatrixInfo = new QLabel(groupBoxMatrix);
        labelMatrixInfo->setObjectName("labelMatrixInfo");

        verticalLayout_2->addWidget(labelMatrixInfo);

        horizontalLayoutButtons = new QHBoxLayout();
        horizontalLayoutButtons->setObjectName("horizontalLayoutButtons");
        buttonMatrix = new QPushButton(groupBoxMatrix);
        buttonMatrix->setObjectName("buttonMatrix");

        horizontalLayoutButtons->addWidget(buttonMatrix);

        buttonClear = new QPushButton(groupBoxMatrix);
        buttonClear->setObjectName("buttonClear");

        horizontalLayoutButtons->addWidget(buttonClear);


        verticalLayout_2->addLayout(horizontalLayoutButtons);


        horizontalLayout->addWidget(groupBoxMatrix);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\222\320\260\321\200\320\270\320\260\320\275\321\202 2.5 - Qt \320\232\320\276\320\275\321\202\320\265\320\271\320\275\320\265\321\200\321\213", nullptr));
        groupBoxArray->setTitle(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\321\214 1: \320\236\320\264\320\275\320\276\320\274\320\265\321\200\320\275\321\213\320\271 \320\274\320\260\321\201\321\201\320\270\320\262", nullptr));
        labelArrayDesc->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\206\320\265\320\273\321\213\320\265 \321\207\320\270\321\201\320\273\320\260 \321\207\320\265\321\200\320\265\320\267 \320\277\321\200\320\276\320\261\320\265\320\273:", nullptr));
        buttonArray->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270 \321\207\320\265\321\202\320\275\321\213\320\265 - \320\275\320\265\321\207\320\265\321\202\320\275\321\213\320\265", nullptr));
        labelArrayResult->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202:", nullptr));
        groupBoxMatrix->setTitle(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\321\214 2: \320\234\320\260\321\202\321\200\320\270\321\206\320\260", nullptr));
        labelMatrixDesc->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 4x5 \321\201\320\276 \321\201\320\273\321\203\321\207\320\260\320\271\320\275\321\213\320\274\320\270 \321\207\320\270\321\201\320\273\320\260\320\274\320\270 (0-99)", nullptr));
        labelMatrixInfo->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 4 x 5", nullptr));
        buttonMatrix->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\265\320\275\321\217\321\202\321\214 \320\274\320\265\321\201\321\202\320\260\320\274\320\270 min \320\270 max", nullptr));
        buttonClear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 / \320\235\320\276\320\262\320\260\321\217 \320\274\320\260\321\202\321\200\320\270\321\206\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
