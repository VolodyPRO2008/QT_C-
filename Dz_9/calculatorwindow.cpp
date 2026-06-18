#include "calculatorwindow.h"

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Калькулятор");
    setFixedSize(450, 400);

    // Создаем виджеты
    QLabel *labelNum1 = new QLabel("Первое число:", this);
    lineEditNum1 = new QLineEdit(this);
    lineEditNum1->setPlaceholderText("Введите число");
    lineEditNum1->setStyleSheet("padding: 8px; font-size: 14px;");

    QLabel *labelNum2 = new QLabel("Второе число:", this);
    lineEditNum2 = new QLineEdit(this);
    lineEditNum2->setPlaceholderText("Введите число");
    lineEditNum2->setStyleSheet("padding: 8px; font-size: 14px;");

    QLabel *labelOp = new QLabel("Операция:", this);
    comboBoxOperation = new QComboBox(this);
    comboBoxOperation->addItems({"+", "-", "×", "÷", "^"});
    comboBoxOperation->setStyleSheet("padding: 8px; font-size: 14px;");

    pushButtonCalc = new QPushButton("🧮 Вычислить", this);
    pushButtonCalc->setStyleSheet("padding: 10px; font-size: 16px; background-color: #4CAF50; color: white;");

    labelResult = new QLabel("Результат: ", this);
    labelResult->setStyleSheet("font-size: 16px; padding: 15px; border: 2px solid #4CAF50; border-radius: 5px; background-color: #f0f8f0;");
    labelResult->setMinimumHeight(60);
    labelResult->setAlignment(Qt::AlignCenter);

    // Верстка
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Первое число
    QHBoxLayout *row1 = new QHBoxLayout;
    row1->addWidget(labelNum1);
    row1->addWidget(lineEditNum1, 1);
    mainLayout->addLayout(row1);

    // Второе число
    QHBoxLayout *row2 = new QHBoxLayout;
    row2->addWidget(labelNum2);
    row2->addWidget(lineEditNum2, 1);
    mainLayout->addLayout(row2);

    // Операция
    QHBoxLayout *row3 = new QHBoxLayout;
    row3->addWidget(labelOp);
    row3->addWidget(comboBoxOperation, 1);
    mainLayout->addLayout(row3);

    // Кнопка
    mainLayout->addWidget(pushButtonCalc);

    // Результат
    mainLayout->addWidget(new QLabel("Результат:", this));
    mainLayout->addWidget(labelResult);

    // Подключение
    connect(pushButtonCalc, &QPushButton::clicked, this, &CalculatorWindow::onCalculateClicked);
}

CalculatorWindow::~CalculatorWindow() {}

void CalculatorWindow::onCalculateClicked()
{
    bool ok1, ok2;
    double a = lineEditNum1->text().trimmed().toDouble(&ok1);
    double b = lineEditNum2->text().trimmed().toDouble(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числа!");
        return;
    }

    QString op = comboBoxOperation->currentText();

    // Проверка деления на ноль
    if (op == "÷" && qFuzzyIsNull(b)) {
        QMessageBox::warning(this, "Ошибка", "Деление на ноль невозможно!");
        return;
    }

    double result = calculate(a, b, op);
    labelResult->setText(QString("%1 %2 %3 = %4")
                             .arg(a)
                             .arg(op)
                             .arg(b)
                             .arg(result));
}

double CalculatorWindow::calculate(double a, double b, const QString &op)
{
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "×") return a * b;
    if (op == "÷") return a / b;
    if (op == "^") {
        int exp = static_cast<int>(b);
        return power(a, exp);
    }
    return 0;
}

double CalculatorWindow::power(double base, int exp)
{
    if (exp == 0) return 1;
    if (exp < 0) return 1.0 / power(base, -exp);

    double result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}