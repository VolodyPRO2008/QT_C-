#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Variant 4.5 - Stack & Queue");

    doStackTask();
    doQueueTask();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::stackToString(QStack<int> stack)
{
    QString result;

    for (int i = 0; i < stack.size(); i++) {
        result += QString::number(stack[i]) + " ";
    }
    return result;
}


QString MainWindow::queueToString(QQueue<int> queue)
{
    QString result;
    for (int i = 0; i < queue.size(); i++) {
        result += QString::number(queue[i]) + " ";
    }
    return result;
}

void MainWindow::doStackTask()
{
    myStack.clear();

    // Заполняем стек 5 случайными числами от 0 до 99
    for (int i = 0; i < 5; i++) {
        int value = QRandomGenerator::global()->bounded(0, 100);
        myStack.push(value);
    }

    // Находим индексы минимального и максимального элементов
    int minIndex = 0;
    int maxIndex = 0;

    for (int i = 1; i < myStack.size(); i++) {
        if (myStack[i] < myStack[minIndex]) {
            minIndex = i;
        }
        if (myStack[i] > myStack[maxIndex]) {
            maxIndex = i;
        }
    }

    // Меняем местами минимальный и максимальный
    int temp = myStack[minIndex];
    myStack[minIndex] = myStack[maxIndex];
    myStack[maxIndex] = temp;

    // Выводим результат в textEdit
    QString output;;
    output += "Стек после замены min и max:\n";
    output += stackToString(myStack) + "\n\n";
    output += "Минимальный элемент был: " + QString::number(myStack[maxIndex]) + "\n";
    output += "Максимальный элемент был: " + QString::number(myStack[minIndex]) + "\n";
    output += "(они поменялись местами)";

    ui->textEditStack->setText(output);
}


void MainWindow::doQueueTask()
{
    myQueue.clear();

    // Заполняем очередь 8 случайными числами от 0 до 50
    for (int i = 0; i < 8; i++) {
        int value = QRandomGenerator::global()->bounded(0, 51);
        myQueue.enqueue(value);
    }

    // Сохраняем исходную очередь для вывода
    QQueue<int> originalQueue = myQueue;

    // Находим среднее арифметическое всех четных чисел
    int sumEven = 0;
    int countEven = 0;

    for (int i = 0; i < myQueue.size(); i++) {
        if (myQueue[i] % 2 == 0) {
            sumEven += myQueue[i];
            countEven++;
        }
    }

    int averageEven = 0;
    if (countEven > 0) {
        averageEven = sumEven / countEven;  // целочисленное деление
    }

    // Заменяем все четные числа на среднее арифметическое
    for (int i = 0; i < myQueue.size(); i++) {
        if (myQueue[i] % 2 == 0) {
            myQueue[i] = averageEven;
        }
    }

    // Выводим результат
    QString output;
    output += "Исходная очередь:\n";
    output += queueToString(originalQueue) + "\n\n";
    output += "Четные числа: ";

    for (int i = 0; i < originalQueue.size(); i++) {
        if (originalQueue[i] % 2 == 0) {
            output += QString::number(originalQueue[i]) + " ";
        }
    }
    output += "\n";
    output += "Среднее арифметическое четных чисел: " + QString::number(averageEven) + "\n\n";
    output += "Очередь после замены (четные заменены на среднее):\n";
    output += queueToString(myQueue);

    ui->textEditQueue->setText(output);
}


void MainWindow::on_buttonStack_clicked()
{
    doStackTask();
}


void MainWindow::on_buttonQueue_clicked()
{
    doQueueTask();
}

