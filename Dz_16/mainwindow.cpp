#include "mainwindow.h"
#include <QHeaderView>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_userCount(0)
{
    setWindowTitle("Лабораторная работа №12: Регулярные выражения в Qt");
    setMinimumSize(1000, 750);
    setupUI();

    // Добавляем тестовых пользователей
    UserData testUser1 = {"admin", "admin123", "admin@test.ru", "+7(999)111-22-33"};
    UserData testUser2 = {"user", "user123", "user@test.ru", "+7(999)444-55-66"};
    addUser(testUser1);
    addUser(testUser2);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Создаем вкладки
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->addTab(createAuthTab(), "🔐 Авторизация");
    tabWidget->addTab(createReplaceTab(), "🔄 Замена чисел");

    mainLayout->addWidget(tabWidget);
}

// ==================== ВКЛАДКА 1: АВТОРИЗАЦИЯ ====================

QWidget* MainWindow::createAuthTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);

    // Заголовок
    QLabel *title = new QLabel("🔐 Система авторизации с регулярными выражениями");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2C3E50; padding: 10px;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    // Правила ввода
    QGroupBox *rulesBox = new QGroupBox("📋 Правила ввода");
    QVBoxLayout *rulesLayout = new QVBoxLayout;
    rulesLayout->addWidget(new QLabel("🔹 Логин: только латинские буквы и цифры, 3-20 символов"));
    rulesLayout->addWidget(new QLabel("🔹 Пароль: минимум 6 символов (буквы и цифры)"));
    rulesLayout->addWidget(new QLabel("🔹 Email: стандартный формат email"));
    rulesLayout->addWidget(new QLabel("🔹 Телефон: формат +7(XXX)XXX-XX-XX"));
    rulesBox->setLayout(rulesLayout);
    mainLayout->addWidget(rulesBox);

    // Форма регистрации
    QGroupBox *formBox = new QGroupBox("📝 Регистрация нового пользователя");
    QGridLayout *formLayout = new QGridLayout;
    formLayout->setVerticalSpacing(10);

    // Логин
    QLabel *labelLogin = new QLabel("Логин:", this);
    labelLogin->setStyleSheet("font-weight: bold;");
    formLayout->addWidget(labelLogin, 0, 0);

    lineEditLogin = new QLineEdit(this);
    lineEditLogin->setPlaceholderText("Введите логин (3-20 символов)");
    lineEditLogin->setStyleSheet("padding: 5px;");
    // Регулярное выражение для логина: латинские буквы и цифры, 3-20 символов
    QRegularExpression loginRegex("^[A-Za-z0-9]{3,20}$");
    lineEditLogin->setValidator(new QRegularExpressionValidator(loginRegex, this));
    formLayout->addWidget(lineEditLogin, 0, 1);

    // Пароль
    QLabel *labelPassword = new QLabel("Пароль:", this);
    labelPassword->setStyleSheet("font-weight: bold;");
    formLayout->addWidget(labelPassword, 1, 0);

    lineEditPassword = new QLineEdit(this);
    lineEditPassword->setPlaceholderText("Введите пароль (минимум 6 символов)");
    lineEditPassword->setEchoMode(QLineEdit::Password);
    lineEditPassword->setStyleSheet("padding: 5px;");
    // Регулярное выражение для пароля: буквы и цифры, минимум 6 символов
    QRegularExpression passwordRegex("^[A-Za-z0-9]{6,}$");
    lineEditPassword->setValidator(new QRegularExpressionValidator(passwordRegex, this));
    formLayout->addWidget(lineEditPassword, 1, 1);

    // Email
    QLabel *labelEmail = new QLabel("Email:", this);
    labelEmail->setStyleSheet("font-weight: bold;");
    formLayout->addWidget(labelEmail, 2, 0);

    lineEditEmail = new QLineEdit(this);
    lineEditEmail->setPlaceholderText("Введите email");
    lineEditEmail->setStyleSheet("padding: 5px;");
    // Регулярное выражение для email
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    lineEditEmail->setValidator(new QRegularExpressionValidator(emailRegex, this));
    formLayout->addWidget(lineEditEmail, 2, 1);

    // Телефон
    QLabel *labelPhone = new QLabel("Телефон:", this);
    labelPhone->setStyleSheet("font-weight: bold;");
    formLayout->addWidget(labelPhone, 3, 0);

    lineEditPhone = new QLineEdit(this);
    lineEditPhone->setPlaceholderText("+7(XXX)XXX-XX-XX");
    lineEditPhone->setStyleSheet("padding: 5px;");
    // Регулярное выражение для телефона
    QRegularExpression phoneRegex("^\\+7\\([0-9]{3}\\)[0-9]{3}-[0-9]{2}-[0-9]{2}$");
    lineEditPhone->setValidator(new QRegularExpressionValidator(phoneRegex, this));
    formLayout->addWidget(lineEditPhone, 3, 1);

    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    btnRegister = new QPushButton("✅ Зарегистрировать", this);
    btnRegister->setStyleSheet("padding: 8px 20px; background-color: #4CAF50; color: white; border-radius: 5px; font-weight: bold;");
    btnRegister->setEnabled(false);
    buttonLayout->addWidget(btnRegister);

    btnLogin = new QPushButton("🔑 Войти", this);
    btnLogin->setStyleSheet("padding: 8px 20px; background-color: #2196F3; color: white; border-radius: 5px; font-weight: bold;");
    btnLogin->setEnabled(false);
    buttonLayout->addWidget(btnLogin);

    btnClear = new QPushButton("🗑️ Очистить", this);
    btnClear->setStyleSheet("padding: 8px 20px; background-color: #f44336; color: white; border-radius: 5px; font-weight: bold;");
    buttonLayout->addWidget(btnClear);

    buttonLayout->addStretch();
    formLayout->addLayout(buttonLayout, 4, 0, 1, 2);

    formBox->setLayout(formLayout);
    mainLayout->addWidget(formBox);

    // Статус
    labelStatus = new QLabel("ℹ️ Введите данные для регистрации", this);
    labelStatus->setStyleSheet("padding: 10px; background-color: #e3f2fd; border-radius: 5px;");
    labelStatus->setWordWrap(true);
    mainLayout->addWidget(labelStatus);

    // Таблица пользователей
    QGroupBox *tableBox = new QGroupBox("👥 Список зарегистрированных пользователей");
    QVBoxLayout *tableLayout = new QVBoxLayout;

    tableUsers = new QTableWidget(this);
    tableUsers->setColumnCount(4);
    QStringList headers = {"Логин", "Email", "Телефон", "Пароль"};
    tableUsers->setHorizontalHeaderLabels(headers);
    tableUsers->horizontalHeader()->setStretchLastSection(true);
    tableUsers->setAlternatingRowColors(true);
    tableUsers->setEditTriggers(QTableWidget::NoEditTriggers);
    tableUsers->setStyleSheet("font-size: 12px;");
    tableLayout->addWidget(tableUsers);

    tableBox->setLayout(tableLayout);
    mainLayout->addWidget(tableBox);

    // ========== Подключение сигналов ==========
    connect(lineEditLogin, &QLineEdit::textChanged, this, &MainWindow::onLoginTextChanged);
    connect(lineEditPassword, &QLineEdit::textChanged, this, &MainWindow::onPasswordTextChanged);
    connect(lineEditEmail, &QLineEdit::textChanged, this, &MainWindow::onEmailTextChanged);
    connect(lineEditPhone, &QLineEdit::textChanged, this, &MainWindow::onPhoneTextChanged);
    connect(btnRegister, &QPushButton::clicked, this, &MainWindow::onRegisterClicked);
    connect(btnLogin, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);

    return widget;
}

// ==================== ВКЛАДКА 2: ЗАМЕНА ЧИСЕЛ ====================

QWidget* MainWindow::createReplaceTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);

    // Заголовок
    QLabel *title = new QLabel("🔄 Замена чисел на текстовые строки");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2C3E50; padding: 10px;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    // Описание
    QLabel *desc = new QLabel(
        "Введите текст с числами (1-9). Программа найдет все числа и заменит их на текстовые эквиваленты.\n"
        "Например: '2 + 2 = 4' → 'два + два = четыре'"
        );
    desc->setStyleSheet("padding: 10px; background-color: #f0f8ff; border-radius: 5px;");
    desc->setWordWrap(true);
    mainLayout->addWidget(desc);

    // Входной текст
    QGroupBox *inputBox = new QGroupBox("📝 Входной текст");
    QVBoxLayout *inputLayout = new QVBoxLayout;

    textEditInput = new QTextEdit(this);
    textEditInput->setPlaceholderText("Введите текст с числами (1-9) для замены...");
    textEditInput->setStyleSheet("font-size: 14px; font-family: monospace; padding: 10px;");
    textEditInput->setMinimumHeight(120);
    inputLayout->addWidget(textEditInput);

    // Кнопки
    QHBoxLayout *btnLayout = new QHBoxLayout;

    btnReplace = new QPushButton("🔄 Заменить числа", this);
    btnReplace->setStyleSheet("padding: 8px 20px; background-color: #4CAF50; color: white; border-radius: 5px; font-weight: bold;");
    btnLayout->addWidget(btnReplace);

    btnClearText = new QPushButton("🗑️ Очистить", this);
    btnClearText->setStyleSheet("padding: 8px 20px; background-color: #f44336; color: white; border-radius: 5px; font-weight: bold;");
    btnLayout->addWidget(btnClearText);

    btnLayout->addStretch();
    inputLayout->addLayout(btnLayout);

    inputBox->setLayout(inputLayout);
    mainLayout->addWidget(inputBox);

    // Выходной текст
    QGroupBox *outputBox = new QGroupBox("📄 Результат");
    QVBoxLayout *outputLayout = new QVBoxLayout;

    textEditOutput = new QTextEdit(this);
    textEditOutput->setReadOnly(true);
    textEditOutput->setStyleSheet("font-size: 14px; font-family: monospace; padding: 10px; background-color: #f8f9fa;");
    textEditOutput->setMinimumHeight(120);
    outputLayout->addWidget(textEditOutput);

    outputBox->setLayout(outputLayout);
    mainLayout->addWidget(outputBox);

    // Статус
    labelReplaceStatus = new QLabel("ℹ️ Введите текст и нажмите 'Заменить числа'", this);
    labelReplaceStatus->setStyleSheet("padding: 10px; background-color: #e3f2fd; border-radius: 5px;");
    labelReplaceStatus->setWordWrap(true);
    mainLayout->addWidget(labelReplaceStatus);

    // ========== Подключение сигналов ==========
    connect(btnReplace, &QPushButton::clicked, this, &MainWindow::onReplaceClicked);
    connect(btnClearText, &QPushButton::clicked, this, &MainWindow::onClearTextClicked);

    return widget;
}

// ==================== МЕТОДЫ АВТОРИЗАЦИИ ====================

bool MainWindow::validateLogin(const QString &login)
{
    QRegularExpression regex("^[A-Za-z0-9]{3,20}$");
    return regex.match(login).hasMatch();
}

bool MainWindow::validatePassword(const QString &password)
{
    QRegularExpression regex("^[A-Za-z0-9]{6,}$");
    return regex.match(password).hasMatch();
}

bool MainWindow::validateEmail(const QString &email)
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool MainWindow::validatePhone(const QString &phone)
{
    QRegularExpression regex("^\\+7\\([0-9]{3}\\)[0-9]{3}-[0-9]{2}-[0-9]{2}$");
    return regex.match(phone).hasMatch();
}

bool MainWindow::isUserExists(const QString &login)
{
    for (const UserData &user : m_users) {
        if (user.login == login) {
            return true;
        }
    }
    return false;
}

bool MainWindow::authenticateUser(const QString &login, const QString &password)
{
    for (const UserData &user : m_users) {
        if (user.login == login && user.password == password) {
            return true;
        }
    }
    return false;
}

void MainWindow::addUser(const UserData &user)
{
    if (m_userCount < 10 && !isUserExists(user.login)) {
        m_users.append(user);
        m_userCount++;

        // Обновляем таблицу
        int row = tableUsers->rowCount();
        tableUsers->insertRow(row);
        tableUsers->setItem(row, 0, new QTableWidgetItem(user.login));
        tableUsers->setItem(row, 1, new QTableWidgetItem(user.email));
        tableUsers->setItem(row, 2, new QTableWidgetItem(user.phone));
        tableUsers->setItem(row, 3, new QTableWidgetItem("********"));
    }
}

// ==================== СЛОТЫ АВТОРИЗАЦИИ ====================

void MainWindow::onLoginTextChanged(const QString &text)
{
    Q_UNUSED(text);
    checkFormValidity();
}

void MainWindow::onPasswordTextChanged(const QString &text)
{
    Q_UNUSED(text);
    checkFormValidity();
}

void MainWindow::onEmailTextChanged(const QString &text)
{
    Q_UNUSED(text);
    checkFormValidity();
}

void MainWindow::onPhoneTextChanged(const QString &text)
{
    Q_UNUSED(text);
    checkFormValidity();
}

void MainWindow::checkFormValidity()
{
    bool valid = validateLogin(lineEditLogin->text()) &&
                 validatePassword(lineEditPassword->text()) &&
                 validateEmail(lineEditEmail->text()) &&
                 validatePhone(lineEditPhone->text());

    btnRegister->setEnabled(valid && m_userCount < 10);
    btnLogin->setEnabled(validateLogin(lineEditLogin->text()) &&
                         validatePassword(lineEditPassword->text()));

    if (m_userCount >= 10) {
        labelStatus->setText("⚠️ Достигнут лимит пользователей (10)");
        labelStatus->setStyleSheet("padding: 10px; background-color: #fff3cd; border-radius: 5px;");
    } else if (valid) {
        labelStatus->setText("✅ Все поля заполнены корректно");
        labelStatus->setStyleSheet("padding: 10px; background-color: #d4edda; border-radius: 5px;");
    } else {
        labelStatus->setText("ℹ️ Заполните все поля корректно");
        labelStatus->setStyleSheet("padding: 10px; background-color: #e3f2fd; border-radius: 5px;");
    }
}

void MainWindow::onRegisterClicked()
{
    QString login = lineEditLogin->text();
    QString password = lineEditPassword->text();
    QString email = lineEditEmail->text();
    QString phone = lineEditPhone->text();

    if (isUserExists(login)) {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует!");
        return;
    }

    if (m_userCount >= 10) {
        QMessageBox::warning(this, "Ошибка", "Достигнут лимит пользователей (10)");
        return;
    }

    UserData newUser = {login, password, email, phone};
    addUser(newUser);

    QMessageBox::information(this, "Успех", "Пользователь успешно зарегистрирован!");

    labelStatus->setText("✅ Пользователь " + login + " зарегистрирован!");
    labelStatus->setStyleSheet("padding: 10px; background-color: #d4edda; border-radius: 5px;");

    // Очищаем поля
    lineEditLogin->clear();
    lineEditPassword->clear();
    lineEditEmail->clear();
    lineEditPhone->clear();
    btnRegister->setEnabled(false);
    btnLogin->setEnabled(false);
}

void MainWindow::onLoginClicked()
{
    QString login = lineEditLogin->text();
    QString password = lineEditPassword->text();

    if (authenticateUser(login, password)) {
        QMessageBox::information(this, "Успех", "Добро пожаловать, " + login + "!");
        labelStatus->setText("✅ Авторизация успешна! Добро пожаловать, " + login);
        labelStatus->setStyleSheet("padding: 10px; background-color: #d4edda; border-radius: 5px;");
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
        labelStatus->setText("❌ Ошибка авторизации: неверный логин или пароль");
        labelStatus->setStyleSheet("padding: 10px; background-color: #f8d7da; border-radius: 5px;");
    }
}

void MainWindow::onClearClicked()
{
    lineEditLogin->clear();
    lineEditPassword->clear();
    lineEditEmail->clear();
    lineEditPhone->clear();
    btnRegister->setEnabled(false);
    btnLogin->setEnabled(false);
    labelStatus->setText("ℹ️ Поля очищены");
    labelStatus->setStyleSheet("padding: 10px; background-color: #e3f2fd; border-radius: 5px;");
}

// ==================== МЕТОДЫ ЗАМЕНЫ ЧИСЕЛ ====================

QString MainWindow::numberToWord(int num)
{
    switch (num) {
    case 1: return "один";
    case 2: return "два";
    case 3: return "три";
    case 4: return "четыре";
    case 5: return "пять";
    case 6: return "шесть";
    case 7: return "семь";
    case 8: return "восемь";
    case 9: return "девять";
    default: return QString::number(num);
    }
}

QString MainWindow::replaceNumbersWithWords(const QString &text)
{
    QString result = text;

    // Используем регулярное выражение для поиска чисел 1-9
    QRegularExpression regex("\\b([1-9])\\b");
    QRegularExpressionMatchIterator it = regex.globalMatch(text);

    // Собираем замены (проходим в обратном порядке, чтобы не сбивать позиции)
    QList<QPair<int, int>> positions; // позиция, длина
    QList<QString> replacements;

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        int num = match.captured(1).toInt();
        positions.append(qMakePair(match.capturedStart(), match.capturedLength()));
        replacements.append(numberToWord(num));
    }

    // Заменяем в обратном порядке
    for (int i = positions.size() - 1; i >= 0; --i) {
        int pos = positions[i].first;
        int len = positions[i].second;
        result.replace(pos, len, replacements[i]);
    }

    return result;
}

// ==================== СЛОТЫ ЗАМЕНЫ ====================

void MainWindow::onReplaceClicked()
{
    QString input = textEditInput->toPlainText();

    if (input.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите текст для замены!");
        return;
    }

    QString output = replaceNumbersWithWords(input);
    textEditOutput->setText(output);

    int count = 0;
    QRegularExpression regex("\\b([1-9])\\b");
    QRegularExpressionMatchIterator it = regex.globalMatch(input);
    while (it.hasNext()) {
        it.next();
        count++;
    }

    labelReplaceStatus->setText("✅ Найдено и заменено чисел: " + QString::number(count));
    labelReplaceStatus->setStyleSheet("padding: 10px; background-color: #d4edda; border-radius: 5px;");
}

void MainWindow::onClearTextClicked()
{
    textEditInput->clear();
    textEditOutput->clear();
    labelReplaceStatus->setText("ℹ️ Текст очищен");
    labelReplaceStatus->setStyleSheet("padding: 10px; background-color: #e3f2fd; border-radius: 5px;");
}