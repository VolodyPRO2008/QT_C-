#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Калькулятор");

    // Подключаем цифры
    connect(ui->btn0, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn7, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn3, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn4, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn5, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn6, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn8, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn9, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(ui->btnSubtract, &QPushButton::clicked, this, &MainWindow::onSubtractClicked);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &MainWindow::onMultiplyClicked);
    connect(ui->btnDivide, &QPushButton::clicked, this, &MainWindow::onDivideClicked);
    connect(ui->btnEquals, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btnDecimal, &QPushButton::clicked, this, &MainWindow::onDecimalClicked);
    connect(ui->btnSign, &QPushButton::clicked, this, &MainWindow::onSignClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDigitClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        ui->lineEdit->insert(btn->text());
    }
}

void MainWindow::onAddClicked()
{
    calculate("+");
}

void MainWindow::onSubtractClicked()
{
    calculate("-");
}

void MainWindow::onMultiplyClicked()
{
    calculate("*");
}

void MainWindow::onDivideClicked()
{
    calculate("/");
}

void MainWindow::calculate(const QString& sgn)
{
    if (ui->lineEdit->text().isEmpty()) return;

    if (stack.size() >= 2) {
        double val2 = ui->lineEdit->text().toDouble();
        QString sign = stack.pop();
        double val1 = stack.pop().toDouble();

        if (sign == "+") {
            stack.push(QString::number(val1 + val2));
        } else if (sign == "-") {
            stack.push(QString::number(val1 - val2));
        } else if (sign == "*") {
            stack.push(QString::number(val1 * val2));
        } else if (sign == "/") {
            if (val2 != 0) {
                stack.push(QString::number(val1 / val2));
            } else {
                stack.push(QString::number(val1));
            }
        }
        stack.push(sgn);
    } else {
        stack.push(ui->lineEdit->text());
        stack.push(sgn);
    }

    ui->lineEdit->clear();
    ui->lineEdit_2->setText(stack.toList().join(" "));
}

void MainWindow::onEqualsClicked()
{
    if (ui->lineEdit->text().isEmpty() || stack.size() < 2) return;

    double val2 = ui->lineEdit->text().toDouble();
    QString sign = stack.pop();
    double val1 = stack.pop().toDouble();

    if (sign == "+") {
        stack.push(QString::number(val1 + val2));
    } else if (sign == "-") {
        stack.push(QString::number(val1 - val2));
    } else if (sign == "*") {
        stack.push(QString::number(val1 * val2));
    } else if (sign == "/") {
        if (val2 != 0) {
            stack.push(QString::number(val1 / val2));
        } else {
            stack.push(QString::number(val1));
        }
    }

    ui->lineEdit->setText(stack.pop());
    ui->lineEdit_2->clear();
    stack.clear();
}

void MainWindow::onClearClicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    stack.clear();
}

void MainWindow::onDecimalClicked()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty()) {
        ui->lineEdit->setText("0.");
        return;
    }
    if (text.contains('.')) return;
    ui->lineEdit->setText(text + ".");
}

void MainWindow::onSignClicked()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty()) return;

    if (text.startsWith('-')) {
        ui->lineEdit->setText(text.remove(0, 1));
    } else {
        ui->lineEdit->setText("-" + text);
    }
}