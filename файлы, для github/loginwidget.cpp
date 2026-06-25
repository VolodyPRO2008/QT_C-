#include "loginwidget.h"

LoginWidget::LoginWidget(QWidget* parent)
    : QWidget(parent)  // Убираем m_dragging(false)
{
    // Оставляем стандартный заголовок окна
    setFixedSize(480, 350);

    setStyleSheet(R"(
        QWidget {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #2c3e50, stop:1 #1a252f);
            font-family: 'Segoe UI', Arial, sans-serif;
        }
        QLabel {
            color: #ecf0f1;
        }
        QLabel#mainTitle {
            font-size: 22px;
            font-weight: bold;
            color: #3498db;
            padding: 0 0 5px 0;
        }
        QLabel#subtitle {
            font-size: 13px;
            color: #bdc3c7;
            padding-bottom: 15px;
        }
        QLineEdit {
            padding: 10px 14px;
            border: 2px solid #34495e;
            border-radius: 8px;
            background: #34495e;
            color: #ecf0f1;
            font-size: 15px;
            min-height: 30px;
            max-height: 38px;
        }
        QLineEdit:focus {
            border: 2px solid #3498db;
            background: #2c3e50;
        }
        QPushButton {
            padding: 10px 0;
            border: none;
            border-radius: 8px;
            font-size: 15px;
            font-weight: bold;
            min-width: 120px;
            min-height: 36px;
            max-height: 40px;
        }
        QPushButton#loginBtn {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #3498db, stop:1 #2980b9);
            color: white;
        }
        QPushButton#loginBtn:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #5dade2, stop:1 #3498db);
        }
        QPushButton#exitBtn {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #e74c3c, stop:1 #c0392b);
            color: white;
        }
        QPushButton#exitBtn:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #ec7063, stop:1 #e74c3c);
        }
        QLabel#status {
            color: #e74c3c;
            font-size: 14px;
            padding: 5px;
            min-height: 28px;
        }
        QLabel#status.success {
            color: #2ecc71;
        }
        QLabel#nameLabel {
            font-size: 15px;
            font-weight: bold;
            color: #ecf0f1;
            min-width: 50px;
        }
    )");

    // ОСНОВНОЙ МАКЕТ
    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(40, 30, 40, 30);

    // ЗАГОЛОВОК "Вход в систему ИСУПС"
    auto* mainTitle = new QLabel("Вход в систему ИСУПС");
    mainTitle->setObjectName("mainTitle");
    mainTitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(mainTitle);

    // Подзаголовок
    auto* subtitleLabel = new QLabel("Информационная система учёта посещаемости");
    subtitleLabel->setObjectName("subtitle");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(subtitleLabel);

    // Разделитель
    auto* line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("background: #34495e; max-height: 1px; margin: 5px 0;");
    layout->addWidget(line);

    // Поле ввода ФИО
    auto* nameLayout = new QHBoxLayout();
    nameLayout->setSpacing(10);

    auto* nameLabel = new QLabel("ФИО:");
    nameLabel->setObjectName("nameLabel");
    nameLayout->addWidget(nameLabel);

    m_fullNameEdit = new QLineEdit;
    m_fullNameEdit->setPlaceholderText("Введите ваше имя");
    m_fullNameEdit->setText("Иванов Иван Иванович");
    m_fullNameEdit->setMinimumHeight(35);
    nameLayout->addWidget(m_fullNameEdit);

    layout->addLayout(nameLayout);

    // Статус (скрыт по умолчанию)
    m_statusLabel = new QLabel;
    m_statusLabel->setObjectName("status");
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_statusLabel->setMinimumHeight(30);
    m_statusLabel->setVisible(false);
    layout->addWidget(m_statusLabel);

    // КНОПКИ: "Войти" слева, "Выйти" справа
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    buttonLayout->setAlignment(Qt::AlignCenter);

    m_loginButton = new QPushButton("Войти");
    m_loginButton->setObjectName("loginBtn");
    m_loginButton->setFixedWidth(130);

    m_exitButton = new QPushButton("Выход");
    m_exitButton->setObjectName("exitBtn");
    m_exitButton->setFixedWidth(130);

    buttonLayout->addWidget(m_loginButton);
    buttonLayout->addWidget(m_exitButton);

    layout->addLayout(buttonLayout);

    // ===== СИГНАЛЫ =====
    connect(m_loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
    connect(m_exitButton, &QPushButton::clicked, this, &LoginWidget::onExitClicked);
    connect(m_fullNameEdit, &QLineEdit::returnPressed, this, &LoginWidget::onLoginClicked);
}

void LoginWidget::onLoginClicked()
{
    QString fullName = m_fullNameEdit->text().trimmed();

    if (fullName.isEmpty()) {
        m_statusLabel->setText("⚠️ Введите ваше ФИО!");
        m_statusLabel->setStyleSheet("color: #e74c3c; font-size: 14px;");
        m_statusLabel->setVisible(true);
        return;
    }

    UserInfo user = DatabaseManager::instance().authenticateUser(fullName);

    if (user.id == -1) {
        m_statusLabel->setText("❌ Пользователь с таким ФИО не найден!");
        m_statusLabel->setStyleSheet("color: #e74c3c; font-size: 14px;");
        m_statusLabel->setVisible(true);
        return;
    }

    QString roleName;
    switch (user.role) {
    case UserRole::Student: roleName = "Ученик"; break;
    case UserRole::Teacher: roleName = "Преподаватель"; break;
    case UserRole::Administrator: roleName = "Администратор"; break;
    }

    m_statusLabel->setText(QString("✅ Успешный вход! Роль: %1").arg(roleName));
    m_statusLabel->setStyleSheet("color: #2ecc71; font-size: 14px;");
    m_statusLabel->setVisible(true);

    emit loginSuccess(user);
}

void LoginWidget::onExitClicked()
{
    close();
}