#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , rows(4)
    , cols(5)
{
    ui->setupUi(this);
    setWindowTitle("Вариант 2.5 - Qt Контейнеры");

    generateMatrix();
    displayMatrix();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processArray()
{
    QString inputText = ui->lineEditArray->text();

    if (inputText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите числа через пробел!");
        return;
    }

    QStringList numbersList = inputText.split(" ", Qt::SkipEmptyParts);
    QVector<int> array;
    bool ok;

    for (const QString& numStr : numbersList) {
        int num = numStr.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Введите только целые числа!");
            return;
        }
        array.append(num);
    }

    QVector<int> evenNumbers;
    QVector<int> oddNumbers;

    for (int i = 0; i < array.size(); i++) {
        if (array[i] % 2 == 0) {
            evenNumbers.append(array[i]);
        } else {
            oddNumbers.append(array[i]);
        }
    }

    QString result;
    result += "Четные элементы:\n";
    if (evenNumbers.isEmpty()) {
        result += "(нет четных чисел)\n";
    } else {
        for (int i = 0; i < evenNumbers.size(); i++) {
            result += QString::number(evenNumbers[i]) + " ";
        }
        result += "\n";
    }

    result += "\nНечетные элементы:\n";
    if (oddNumbers.isEmpty()) {
        result += "(нет нечетных чисел)\n";
    } else {
        for (int i = 0; i < oddNumbers.size(); i++) {
            result += QString::number(oddNumbers[i]) + " ";
        }
        result += "\n";
    }

    result += "\nИсходный массив:\n";
    for (int i = 0; i < array.size(); i++) {
        result += QString::number(array[i]) + " ";
    }

    ui->textEditArray->setText(result);
}

void MainWindow::generateMatrix()
{
    matrix.clear();

    for (int i = 0; i < rows; i++) {
        QVector<int> row;
        for (int j = 0; j < cols; j++) {
            int value = QRandomGenerator::global()->bounded(100);
            row.append(value);
        }
        matrix.append(row);
    }
}

void MainWindow::displayMatrix()
{
    ui->textEditMatrix->clear();

    for (int i = 0; i < matrix.size(); i++) {
        QString line = "";
        for (int j = 0; j < matrix[i].size(); j++) {
            line += QString("%1").arg(matrix[i][j], 3);
            line += "  ";
        }
        ui->textEditMatrix->append(line);
    }

    ui->labelMatrixInfo->setText(
        QString("Матрица %1 x %2").arg(rows).arg(cols)
        );
}

void MainWindow::transformMatrixMinMax()
{
    for (int i = 0; i < matrix.size(); i++) {
        int minIndex = 0;
        int maxIndex = 0;

        for (int j = 1; j < matrix[i].size(); j++) {
            if (matrix[i][j] < matrix[i][minIndex]) {
                minIndex = j;
            }
            if (matrix[i][j] > matrix[i][maxIndex]) {
                maxIndex = j;
            }
        }

        int temp = matrix[i][minIndex];
        matrix[i][minIndex] = matrix[i][maxIndex];
        matrix[i][maxIndex] = temp;
    }
}

void MainWindow::on_buttonArray_clicked()
{
    processArray();
}

void MainWindow::on_buttonMatrix_clicked()
{
    transformMatrixMinMax();
    displayMatrix();
    QMessageBox::information(this, "Готово", "Min и Max поменяны местами в каждой строке!");
}

void MainWindow::on_buttonClear_clicked()
{
    ui->lineEditArray->clear();
    ui->textEditArray->clear();
    generateMatrix();
    displayMatrix();
}