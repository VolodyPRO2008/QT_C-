#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Variant 6.5 - Split Even and Odd Numbers");

    ui->textEditSource->clear();
    ui->textEditEven->clear();
    ui->textEditOdd->clear();

    sourceFilePath = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonSelectFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Выберите исходный файл f",
        QDir::homePath(),
        "Текстовые файлы (*.txt);;Все файлы (*.*)"
        );

    if (filePath.isEmpty()) {
        return;
    }

    sourceFilePath = filePath;
    ui->lineEditFilePath->setText(sourceFilePath);

    QFile file(sourceFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения");
        return;
    }

    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();

    ui->textEditSource->setPlainText(content);
    ui->textEditEven->clear();
    ui->textEditOdd->clear();

    QMessageBox::information(this, "Готово", "Файл f успешно загружен");
}

void MainWindow::on_buttonProcess_clicked()
{
    if (sourceFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите исходный файл f");
        return;
    }

    QFile fileF(sourceFilePath);
    if (!fileF.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл f для чтения");
        return;
    }

    QTextStream streamF(&fileF);
    QString content = streamF.readAll();
    fileF.close();


    QStringList numbersList = content.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    QStringList evenNumbers;
    QStringList oddNumbers;

    for (const QString& numStr : numbersList) {
        bool ok;
        int num = numStr.toInt(&ok);
        if (ok) {
            if (num % 2 == 0) {
                evenNumbers.append(numStr);
            } else {
                oddNumbers.append(numStr);
            }
        }
    }

    QString evenFilePath = QFileInfo(sourceFilePath).absolutePath() + "/g.txt";
    QFile fileG(evenFilePath);
    if (!fileG.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл g для записи");
        return;
    }

    QTextStream streamG(&fileG);
    for (const QString& num : evenNumbers) {
        streamG << num << " ";
    }
    fileG.close();

    QString oddFilePath = QFileInfo(sourceFilePath).absolutePath() + "/h.txt";
    QFile fileH(oddFilePath);
    if (!fileH.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл h для записи");
        return;
    }

    QTextStream streamH(&fileH);
    for (const QString& num : oddNumbers) {
        streamH << num << " ";
    }
    fileH.close();

    ui->textEditEven->setPlainText(evenNumbers.join(" "));
    ui->textEditOdd->setPlainText(oddNumbers.join(" "));

    QString resultMessage = QString("Файл g (чётные) сохранён: %1\nФайл h (нечётные) сохранён: %2")
                                .arg(evenFilePath)
                                .arg(oddFilePath);

    QMessageBox::information(this, "Готово", resultMessage);
}


