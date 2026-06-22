#include "loginwidget.h"
#include "databasemanager.h"

LoginWidget::LoginWidget(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Вход в систему ИСУП");
    setFixedSize(350, 200);

    auto* layout = new QVBoxLayout(this);

    auto* titleLabel = new QLabel("Информационная система учёта посещаемости");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* loginLayout = new QHBoxLayout();
    loginLayout->addWidget(new QLabel("Логин:"));
    m_usernameEdit = new QLineEdit;
    m_usernameEdit->setText("admin");
    loginLayout->addWidget(m_usernameEdit);
    layout->addLayout(loginLayout);

    auto* passLayout = new QHBoxLayout();
    passLayout->addWidget(new QLabel("Пароль:"));
    m_passwordEdit = new QLineEdit;
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setText("admin123");
    passLayout->addWidget(m_passwordEdit);
    layout->addLayout(passLayout);

    m_statusLabel = new QLabel;
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_statusLabel->setStyleSheet("color: red;");
    layout->addWidget(m_statusLabel);

    auto* buttonLayout = new QHBoxLayout();
    m_loginButton = new QPushButton("Вход");
    m_exitButton = new QPushButton("Выход");
    buttonLayout->addWidget(m_loginButton);
    buttonLayout->addWidget(m_exitButton);
    layout->addLayout(buttonLayout);

    connect(m_loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
    connect(m_exitButton, &QPushButton::clicked, this, &LoginWidget::onExitClicked);
    connect(m_usernameEdit, &QLineEdit::returnPressed, this, &LoginWidget::onLoginClicked);
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &LoginWidget::onLoginClicked);
}

void LoginWidget::onLoginClicked()
{
    QString username = m_usernameEdit->text();
    QString password = m_passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        m_statusLabel->setText("Введите логин и пароль!");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = ? AND password = ?");
    query.bindValue(0, username);
    query.bindValue(1, password);

    if (query.exec() && query.next()) {
        m_statusLabel->setText("Успешный вход!");
        m_statusLabel->setStyleSheet("color: green;");
        emit loginSuccess(username);
    } else {
        m_statusLabel->setText("Неверный логин или пароль!");
        m_statusLabel->setStyleSheet("color: red;");
    }
}

void LoginWidget::onExitClicked()
{
    close();
}