#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Variant 3.5 - Qt Containers");

    doTask1();
    doTask2();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::listToStringQList(const QList<int>& list)
{
    QString result;
    for (int i = 0; i < list.size(); i++) {
        result += QString::number(list[i]) + " ";
    }
    return result;
}

QString MainWindow::listToStringStdList(const std::list<int>& list)
{
    QString result;
    for (int value : list) {
        result += QString::number(value) + " ";
    }
    return result;
}


void MainWindow::doTask1()
{
    list1.clear();
    list2.clear();


    for (int i = 0; i < 10; i++) {
        int value = QRandomGenerator::global()->bounded(-50, 51);
        list1.append(value);
    }


    for (int i = 0; i < 10; i++) {
        int value = QRandomGenerator::global()->bounded(-50, 51);
        list2.append(value);
    }


    if (list2.isEmpty()) {
        QMessageBox::warning(this, "Error", "Второй список пуст!!");
        return;
    }

    int minValue = list2[0];
    for (int i = 1; i < list2.size(); i++) {
        if (list2[i] < minValue) {
            minValue = list2[i];
        }
    }

    // Replace all positive elements of first list with minValue
    for (int i = 0; i < list1.size(); i++) {
        if (list1[i] > 0) {
            list1[i] = minValue;
        }
    }

    // Show result
    QString output;
    output += "Второй список (исходный):\n";
    output += listToStringQList(list2) + "\n\n";
    output += "Минимальный элемент во втором списке: " + QString::number(minValue) + "\n\n";
    output += "Первый список (после замены):\n";
    output += listToStringQList(list1) + "\n";

    ui->textEditTask1->setText(output);
}


void MainWindow::doTask2()
{
    linkedList.clear();

    for (int i = 0; i < 15; i++) {
        int value = QRandomGenerator::global()->bounded(1, 120);
        linkedList.push_back(value);
    }


    int k = ui->lineEditK->text().toInt();
    if (k <= 0) {
        k = 2;
        ui->lineEditK->setText("2");
    }


    std::list<int> originalList = linkedList;

    auto it = linkedList.begin();
    while (it != linkedList.end()) {
        int digits = QString::number(*it).length();
        if (digits > k) {
            it = linkedList.erase(it);
        } else {
            ++it;
        }
    }


    QString output;

    output += "Порог k: " + QString::number(k) + "\n";
    output += "удалить числа с количеством цифр > k)\n\n";
    output += "Исходный связанный список:\n";
    output += listToStringStdList(originalList) + "\n\n";
    output += "Список после удаления (цифры  <= " + QString::number(k) + "):\n";
    output += listToStringStdList(linkedList);

    ui->textEditTask2->setText(output);
}


void MainWindow::on_buttonClear_clicked()
{
    {
        ui->textEditTask1->clear();
        ui->textEditTask2->clear();
        ui->lineEditK->clear();
    }
}


void MainWindow::on_ButtonPart2_clicked()
{

        doTask2();
}


void MainWindow::on_ButtonPart1_clicked()
{

        doTask1();
}

